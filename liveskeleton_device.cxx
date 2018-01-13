/**	\file	liveskeleton_device.cxx
*	Definition of a simple skeleton device class.
*	Function definitions for the LiveSkeleton class.
*/

//--- Class declaration
#include "liveskeleton_device.h"

//--- Registration defines
#define LIVESKELETON_CLASS		LIVESKELETON_CLASSNAME
#define LIVESKELETON_NAME		LIVESKELETON_CLASSSTR
#define LIVESKELETON_LABEL		"Live Skeleton Device"
#define LIVESKELETON_DESC		"Live Skeleton Device"
#define LIVESKELETON_PREFIX		"SkeletonDevice"
#define LIVESKELETON_ICON		"devices_body.png"

//--- FiLMBOX implementation and registration
FBDeviceImplementation	(	LIVESKELETON_CLASS	);
FBRegisterDevice		(	LIVESKELETON_NAME,
							LIVESKELETON_CLASS,
							LIVESKELETON_LABEL,
							LIVESKELETON_DESC,
							LIVESKELETON_ICON	);

/************************************************
 *	FiLMBOX Constructor.
 ************************************************/
bool LiveSkeleton::FBCreate()
{
	// Add model templates
	mRootTemplate =  new FBModelTemplate(LIVESKELETON_PREFIX, "Reference", kFBModelTemplateRoot);
	ModelTemplate.Children.Add(mRootTemplate);
	mHasAnimationToTranspose = false;
	mPlotting = false;

	// Device communications type, we use thrift.
	CommType = kFBCommTypeOther;

	// Device sampling information
	SamplingMode = kFBHardwareTimestamp;

	// Set sampling rate to 60 Hz
	SamplingPeriod = FBTime(0, 0, 1) / 60;

	UseReferenceTransformation = true;
	FBPropertyPublish( this, UseReferenceTransformation, "UseReferenceTransformation", NULL, NULL );
	DataIsGlobal = true;
	FBPropertyPublish( this, DataIsGlobal, "Global Data Incoming", NULL, NULL );
	RotationOrder = kFBEulerZXY;  // Todo: How to publish this enum?

	FBSystem().TheOne().OnUIIdle.Add( this,(FBCallback) &LiveSkeleton::EventUIIdle );
	// These 2 have no effect at this point?
	Information.SetString("WIP LiveSkeleton Plugin");
	Status.SetString("Plugin initialized.");

	return true;
}


/************************************************
 *	FiLMBOX Destructor.
 ************************************************/
void LiveSkeleton::FBDestroy()
{
    // Propagate to parent
    ParentClass::FBDestroy();  // Todo: Do we need to close hardware first?
	FBSystem().TheOne().OnUIIdle.Remove( this,(FBCallback) &LiveSkeleton::EventUIIdle );
}

/************************************************
 *	Device operation.
 ************************************************/
bool LiveSkeleton::DeviceOperation( kDeviceOperations pOperation )
{
	// Must return the online/offline status of device.
	switch (pOperation)
	{
		case kOpInit:	return Init();
		case kOpStart:	return Start();
		case kOpAutoDetect:	break;
		case kOpStop:	return Stop();
		case kOpReset:	return Reset();
		case kOpDone:	return Done();
	}
    return ParentClass::DeviceOperation(pOperation);
}


/************************************************
 *	Initialize the device.
 ************************************************/
bool LiveSkeleton::Init()
{
    FBProgress	lProgress;

	lProgress.ProgressBegin();
    lProgress.Caption	= "Device";
	lProgress.Text		= "Initializing device...";

	mHierarchyIsDefined = false;
	lProgress.ProgressDone();
	return true;
}


/************************************************
 *	Removal of device.
 ************************************************/
bool LiveSkeleton::Done()
{
	FBProgress	lProgress;

	lProgress.ProgressBegin();
    lProgress.Caption	= "Device";
	lProgress.Text		= "Shutting down device...";

	UnBind();
	lProgress.ProgressDone();
	/*
	*	Add device removal code here.
	*/

	return true;
}

/************************************************
 *	Reset of the device.
 ************************************************/
bool LiveSkeleton::Reset()
{
    Stop();
    return Start();
}

/************************************************
 *	Device is started (online).
 ************************************************/
bool LiveSkeleton::Start()
{
	FBProgress	Progress;
	
	Progress.ProgressBegin();
	Progress.Caption	= "Setting up device.";

	// Step 1: Open device
	if(! mHardware.Open() )
	{
		Information = "Could not open device.";
		Status.SetString("Not connected.");
		Progress.ProgressDone();
		return false;
	}

	Status.SetString("Connected.");
	HardwareVersionInfo = mHardware.GetServerVersion().c_str();

	// Step 2: Ask hardware to get channel information
	Progress.Percent.SetInt(50);
	Progress.Text	= "Device found, scanning for channel information...";
	Information		= "Retrieving channel information";

	if (! mHardware.GetSetupInfo() )
	{
		Information = "Could not get channel information from device.";
		Progress.ProgressDone();
		return false;
	}
	Progress.Percent.SetInt(80);
	Progress.Text	= "Binding channels to animation nodes...";
	// Create as many channels as the hardware counterpart.
	mChannels.resize(GetChannelCount());
	Bind();
	Progress.Percent.SetInt(95);
	Progress.Text	= "Starting Data stream...";

	// Step 3: Start data stream
	Information = "Start Data stream...";
	if(! mHardware.StartDataStream() )
	{
		Information = "Could not start data stream.";
		mHardware.StopDataStream();
		Progress.ProgressDone();
		return false;
	}
	Progress.Percent.SetInt(100);
	Progress.ProgressDone();

    return true; // If true the device is online.
}

/************************************************
 *	Device is stopped (offline).
 ************************************************/
bool LiveSkeleton::Stop()
{
	FBProgress	lProgress;
	lProgress.Caption	= "Shutting down device";

	if(! mHardware.StopDataStream() )
	{
		Information = "Could not stop data stream.";
		return false;
	}

	HardwareVersionInfo = "Not connected.";

	// Step 2: Close down device
	lProgress.Text		= "Closing device communication";
	Information			= "Closing device communication";
	if(! mHardware.Close() )
	{
		Information = "Could not close device";
		return false;
	}

    return false;
}

/************************************************
 *	Define model template hierarchy.
 ************************************************/
void LiveSkeleton::DefineHierarchy()
{
	if( !mHierarchyIsDefined && GetChannelCount() > 0 )
	{
		int lParent;
		for(int i=0; i< GetChannelCount(); i++)
		{
			lParent = GetChannelParent(i);
			if(lParent == -1)  // root joint
			{
				mRootTemplate->Children.Add(mChannels[i].mModelTemplate);
			}
			else
			{
				mChannels[lParent].mModelTemplate->Children.Add(mChannels[i].mModelTemplate);
			}
		}

		mHierarchyIsDefined = true;
	}
}

/************************************************
 *	Test if characterization process can be start
 ************************************************/
bool LiveSkeleton::ReadyForCharacterize()
{
	return mHierarchyIsDefined && GetChannelCount() > 0;
}

/************************************************
* Sets rotation order for models of channels.
*************************************************/
void LiveSkeleton::SetRotationOrder()
{
	int i;
	FBModel* lModel;
	FBTrace("SetRotationOrder called.");
	for (i = 0; i < GetChannelCount(); i++)
	{
		if (mChannels[i].mModelTemplate && (lModel = mChannels[i].mModelTemplate->Model) != NULL)
		{
			//lModel->RotationOrder = RotationOrder;  // FixMe: No effect? Still XYZ?
			lModel->RotationActive.SetEnable(true);
			lModel->RotationOrder.SetInt(RotationOrder);
			FBTrace("Order for %s is %d\n", GetChannelName(i), lModel->RotationOrder);
		}
	}
}

/************************************************
 *	Process global data on template models to local.
 ************************************************/
void LiveSkeleton::ProcessGlobalToLocal()
{
	// Set AnimNode buffer to global.
	SetupLocalGlobal(true);

	int i;
	FBModelList lModels;
	FBModel* lModel;
	
	// Clear selection.
	FBGetSelectedModels(lModels);
	for(i = 0; i < lModels.GetCount(); i++)
		lModels[i]->Selected = false;

	lModels.Clear();
	// Select skeletons FBModel nodes.
	for(i = 0; i < GetChannelCount(); i++)
	{
		if(mChannels[i].mModelTemplate && (lModel = mChannels[i].mModelTemplate->Model) != NULL)
		{
			lModel->Selected = true;
			lModels.Add(lModel);
		}
	}

	mPlotting = true;
	mSystem.CurrentTake->PlotTakeOnSelected(SamplingPeriod);
	mPlotting = false;

	// Deselect again.
	for(i = 0; i < lModels.GetCount(); i++)
		lModels[i]->Selected = false;	

	// Set AnimNode buffer back to local.
	SetupLocalGlobal(false);

    bool ApplyReferenceTransformation = UseReferenceTransformation && mRootTemplate->Model;

	// Clear Translation and Rotation
	if(ApplyReferenceTransformation)
	{
		FBVector4d x;
		mRootTemplate->Model->Translation.SetData(&x);
		mRootTemplate->Model->Rotation.SetData(&x);
	}
}

void LiveSkeleton::SetupLocalGlobal(bool pGlobal)
{
	for( int i = 0; i < GetChannelCount(); i++ )
	{
		if( mChannels[i].mTAnimNode )
		{
			mChannels[i].mTAnimNode->SetBufferType(pGlobal);
		}

		if( mChannels[i].mRAnimNode )
		{
			mChannels[i].mRAnimNode->SetBufferType(pGlobal);
		}
	}
}

/************************************************
 *	Model Template unbinding notification callback
 ************************************************/
bool LiveSkeleton::ModelTemplateUnBindNotify( int pIndex, FBModelTemplate* pModelTemplate)
{
	// Reset skeleton by reevaluating a candidate because of Local/Global animation conversion

	bool ObjectInProcess = GetObjectStatus(kFBStatusCreating) || GetObjectStatus(kFBStatusDestroying) || GetObjectStatus(kFBStatusMerging);
	if(pModelTemplate->Model && pModelTemplate->Model == mRootTemplate->Model && !ObjectInProcess)
	{
		FBPlayerControl().TheOne().EvaluationPause();
		for( int i = 0; i < GetChannelCount(); i++ )
		{
			// Create new translation and rotation animation nodes if necessary
			if(mChannels[i].mTAnimNode)
			{
				mChannels[i].mModelTemplate->Model->Translation.SetAnimated(true);
				FBAnimationNode* lNode = mChannels[i].mModelTemplate->Model->Translation.GetAnimationNode();
				FBVector3d  lVector(mChannels[i].mModelTemplate->Model->Translation);
				lNode->SetCandidate(lVector.mValue);
			}

			if(mChannels[i].mRAnimNode)
			{
				mChannels[i].mModelTemplate->Model->Rotation.SetAnimated(true);
				FBAnimationNode* lNode = mChannels[i].mModelTemplate->Model->Rotation.GetAnimationNode();
				FBVector3d  lVector(mChannels[i].mModelTemplate->Model->Rotation);
				lNode->SetCandidate(lVector.mValue);
			}
		}
		FBPlayerControl().TheOne().EvaluationResume();
	}
	return true;
}

/************************************************
 *	Channel set definition.
 ************************************************/
void LiveSkeleton::Bind()
{
	// All channels: if already defined, don't touch, if new: create animation node and model template.
    for( int i = 0; i < GetChannelCount(); i++ )
	{
		// Create new translation and rotation animation nodes if necessary
		if( !mChannels[i].mTAnimNode )
		{
            // We must use a unique name for our connector.
            FBString lName( GetChannelName(i), " T" );
			mChannels[i].mTAnimNode = AnimationNodeOutCreate( 10000+i, lName, ANIMATIONNODE_TYPE_LOCAL_TRANSLATION	);
		}

		if( !mChannels[i].mRAnimNode )
		{
            // We must use a unique name for our connector.
            FBString lName( GetChannelName(i), " R" );
			mChannels[i].mRAnimNode = AnimationNodeOutCreate( 10000+i, lName, ANIMATIONNODE_TYPE_LOCAL_ROTATION	);
		}

		// Create new model templates
		if(!mChannels[i].mModelTemplate)
		{
			mChannels[i].mModelTemplate = new FBModelTemplate(LIVESKELETON_PREFIX, GetChannelName(i), kFBModelTemplateSkeleton);
			// Bind model template to T and R animation nodes
			mChannels[i].mModelTemplate->Bindings.Add(mChannels[i].mTAnimNode);
			mChannels[i].mModelTemplate->Bindings.Add(mChannels[i].mRAnimNode);

			// For default pose, root needs to be in world space, any other joints have to provide their relative offsets from parent.
			mChannels[i].mModelTemplate->DefaultTranslation = mHardware.GetDefaultT(i);
			mChannels[i].mModelTemplate->DefaultRotation = mHardware.GetDefaultR(i);
		}
    }
	//Define hierarchy if needed
	DefineHierarchy();
}

void LiveSkeleton::UnBind()
{
	int i;
	// All channels: delete animation nodes and associated model template
	for( i = 0; i < GetChannelCount(); i++ )
	{
		// Unbind model templates from T and R animation nodes
		if( mChannels[i].mTAnimNode )
		{
			if( mChannels[i].mModelTemplate )
			{
				mChannels[i].mModelTemplate->Bindings.Remove(mChannels[i].mTAnimNode);
			}
		}

		if( mChannels[i].mRAnimNode )
		{
			if( mChannels[i].mModelTemplate )
			{
				mChannels[i].mModelTemplate->Bindings.Remove(mChannels[i].mRAnimNode);
			}
		}

		// Remove as child of root template
		if( mRootTemplate->Children.Find(mChannels[i].mModelTemplate) >= 0 )
		{
			mRootTemplate->Children.Remove(mChannels[i].mModelTemplate);
		}

		// Destroy unused animation nodes
        if( mChannels[i].mTAnimNode )
		{
			AnimationNodeDestroy(mChannels[i].mTAnimNode);
		}

        if( mChannels[i].mRAnimNode )
		{
			AnimationNodeDestroy(mChannels[i].mRAnimNode);
		}

        mChannels[i].mTAnimNode = NULL;
        mChannels[i].mRAnimNode = NULL;

		if( mChannels[i].mModelTemplate )
		{
			mChannels[i].mModelTemplate->Children.RemoveAll();
		}
	}
	
    for( i = 0; i < GetChannelCount(); i++ )
	{
		// Delete model template
		delete mChannels[i].mModelTemplate;
		mChannels[i].mModelTemplate = NULL;
	}
}

/************************************************
 *	Real-time Evaluation Engine.
 *  Get data from the hardware abstraction.
 *  Write data to animation nodes.
 *  It is called asynchronously, when needed.
 ************************************************/
bool LiveSkeleton::AnimationNodeNotify(FBAnimationNode* pAnimationNode ,FBEvaluateInfo* pEvaluateInfo)
{
	kReference lReference = pAnimationNode->Reference;

	if (lReference>=10000)
	{
	    FBTVector	Pos;
	    FBRVector	Rot;
	    FBSVector	Scal;
	    FBMatrix	GlobalNodeTransformation, GlobalReferenceTransformation;
	    bool		ApplyReferenceTransformation = UseReferenceTransformation && mRootTemplate->Model;
    
	    if(ApplyReferenceTransformation)
	    {
			    mRootTemplate->Model->GetMatrix(GlobalReferenceTransformation,kModelTransformation,true,pEvaluateInfo);
	    }
    
        for(int i=0;i<GetChannelCount();i++)
	    {
		    if(mChannels[i].mTAnimNode && mChannels[i].mRAnimNode)
		    {
			    bool lDontWrite = false;
			    if ((!pAnimationNode->Live || mPlotting) && mChannels[i].mModelTemplate->Model)
			    {
				    mChannels[i].mModelTemplate->Model->Translation.GetAnimationNode()->Evaluate(Pos.mValue,pEvaluateInfo->GetLocalTime(),false);
				    mChannels[i].mModelTemplate->Model->Rotation.GetAnimationNode()->Evaluate(Rot.mValue,pEvaluateInfo->GetLocalTime(),false);
			    } else if (pAnimationNode->Live)
			    {
				    Pos[0] = mHardware.GetDataTX(i);
				    Pos[1] = mHardware.GetDataTY(i);
				    Pos[2] = mHardware.GetDataTZ(i);
				    Rot[0] = mHardware.GetDataRX(i);
				    Rot[1] = mHardware.GetDataRY(i);
				    Rot[2] = mHardware.GetDataRZ(i);
			    } else
			    {
				    lDontWrite = true; // Nothing to do 
			    }
    
			    if(ApplyReferenceTransformation)
			    {
				    FBTRSToMatrix(GlobalNodeTransformation,Pos,Rot,Scal);  // Warning: Rotation is in EulerXYZ! BVH usually has ZXY!
				    FBGetGlobalMatrix(GlobalNodeTransformation,GlobalReferenceTransformation,GlobalNodeTransformation);
				    FBMatrixToTranslation(Pos,GlobalNodeTransformation);
				    FBMatrixToRotation(Rot,GlobalNodeTransformation);  // ToDo: Can take rotationOrder as parameter.
			    }
    
			    if(!lDontWrite)
			    {
				    if (!pAnimationNode->Live || mPlotting)
				    {
			            mChannels[i].mRAnimNode->WriteData( Rot.mValue, pEvaluateInfo);
			            mChannels[i].mTAnimNode->WriteData( Pos.mValue, pEvaluateInfo);
			        }  else
			        {
						if (DataIsGlobal)
						{
				        mChannels[i].mRAnimNode->WriteGlobalData( Rot.mValue, pEvaluateInfo );
				        mChannels[i].mTAnimNode->WriteGlobalData( Pos.mValue, pEvaluateInfo );
						}
						else
						{
			            mChannels[i].mRAnimNode->WriteData( Rot.mValue, pEvaluateInfo);
			            mChannels[i].mTAnimNode->WriteData( Pos.mValue, pEvaluateInfo);
						}
				    }
			    }
			}
		}
	}
	return ParentClass::AnimationNodeNotify( pAnimationNode , pEvaluateInfo);
}

/************************************************
 *	Transport notication.
 *	Useful to compute time offset between Hardware time and System time
 *  PreparePlay is called just before play
 ************************************************/
void LiveSkeleton::DeviceTransportNotify( kTransportMode pMode, FBTime pTime, FBTime pSystem )
{
	if(pMode==kPreparePlay)
	{
		mHardware.ResetPacketTimeOffset(pTime);
	}
}

/************************************************
 *	Real-Time Synchronous Device IO. Is called at the SamplingPeriod.
 ************************************************/
void LiveSkeleton::DeviceIONotify( kDeviceIOs pAction,FBDeviceNotifyInfo &pDeviceNotifyInfo)
{
    switch (pAction)
	{
		case kIOPlayModeWrite:
		case kIOStopModeWrite:
		{
			// Output devices
		}
		break;

		case kIOStopModeRead:
		case kIOPlayModeRead:
		{
			// Skeleton devices
	        FBTime		lEvalTime;
        
	        lEvalTime = pDeviceNotifyInfo.GetLocalTime();
	        
			if (mHardware.FetchDataPacket(lEvalTime))
			{
				DeviceRecordFrame(lEvalTime,pDeviceNotifyInfo);
				AckOneSampleReceived();
			}
			else
			{
				AckOneBadSampleReceived();
			}
		}
		break;
	}
}

/************************************************
*  Called by motion builder when recording of an animation is completed.
*************************************************/
void LiveSkeleton::RecordingDoneAnimation( FBAnimationNode* pAnimationNode )
{
	// Parent call
	FBDevice::RecordingDoneAnimation( pAnimationNode );
	mHasAnimationToTranspose = true;
}

/************************************************
 *	Record a frame of the device (recording).
 ************************************************/
void LiveSkeleton::DeviceRecordFrame(FBTime &pTime,FBDeviceNotifyInfo &pDeviceNotifyInfo)
{
	if( mPlayerControl.GetTransportMode() == kFBTransportPlay )
	{
		int i;
		FBAnimationNode* Data;

		FBTVector	Pos;
		FBRVector	Rot;
		bool		ApplyReferenceTransformation = UseReferenceTransformation && mRootTemplate->Model;
		
		FBMatrix	GlobalReferenceTransformation;
		if(ApplyReferenceTransformation)
			mRootTemplate->Model->GetMatrix(GlobalReferenceTransformation,kModelTransformation,true);

		for (i=0; i<GetChannelCount(); i++)
		{
			// Translation information.
			if (mChannels[i].mTAnimNode)
			{
				Data = mChannels[i].mTAnimNode->GetAnimationToRecord();
				if (Data)
				{
					Pos[0] = mHardware.GetDataTX(i);
					Pos[1] = mHardware.GetDataTY(i);
					Pos[2] = mHardware.GetDataTZ(i);

					if(ApplyReferenceTransformation)
						FBVectorMatrixMult(Pos,GlobalReferenceTransformation,Pos);

					Data->KeyAdd(pTime, Pos);
				}
			}

			// Rotation information.
			if (mChannels[i].mRAnimNode)
			{
				Data = mChannels[i].mRAnimNode->GetAnimationToRecord();
				if (Data)
				{
					Rot[0] = mHardware.GetDataRX(i);
					Rot[1] = mHardware.GetDataRY(i);
					Rot[2] = mHardware.GetDataRZ(i);

					if(ApplyReferenceTransformation)
					{
						FBMatrix GRM;
						FBRotationToMatrix(GRM,Rot);  // Todo: set rotation order to ZXY?
						FBGetGlobalMatrix(GRM,GlobalReferenceTransformation,GRM);
						FBMatrixToRotation(Rot,GRM);
					}

					Data->KeyAdd(pTime, Rot);
				}
			}
		}
	}
}

/************************************************
 *	Store data in FBX.
 ************************************************/
bool LiveSkeleton::FbxStore(FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat)
{
	if (pStoreWhat & kAttributes)
	{
	}
	return true;
}


/************************************************
 *	Retrieve data from FBX.
 ************************************************/
bool LiveSkeleton::FbxRetrieve(FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat)
{
	if( pStoreWhat & kAttributes )
	{
	}
	return true;
}

void LiveSkeleton::EventUIIdle( HISender pSender, HKEvent pEvent )
{
	if(mHasAnimationToTranspose)  // Is true when recording is finished.
	{
		mHasAnimationToTranspose = false;

		// Put the animation back on skeleton
		if (DataIsGlobal)
		{
			ProcessGlobalToLocal();
		}
	}
}