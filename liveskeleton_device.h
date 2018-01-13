#ifndef __LIVE_SKELETON_DEVICE_H__
#define __LIVE_SKELETON_DEVICE_H__
/**	\file	liveskeleton_device.h
*	Declaration of a simple skeleton device class.
*	Class declaration of the LiveSkeleton class.
*/

//--- SDK include
#include <fbsdk/fbsdk.h>

//--- Class declaration
#include "liveskeleton_hardware.h"

//--- Registration defines
#define LIVESKELETON_CLASSNAME		LiveSkeleton
#define LIVESKELETON_CLASSSTR		"LiveSkeleton"

//! Data channel class.
class DataChannel
{
public:
	//! Constructor.
	DataChannel()
	{
		mTAnimNode		= NULL;
		mRAnimNode		= NULL;
		mModelTemplate	= NULL;
	}

	//! Destructor.
	~DataChannel()
	{
	}

public:
	FBAnimationNode*	mTAnimNode;			//!< Position animation node.
	FBAnimationNode*	mRAnimNode;			//!< Rotation animation node.
	FBModelTemplate*	mModelTemplate;		//!< Marker model template driven by the data channel.
};


//! Simple skeleton device.
class LiveSkeleton : public FBDevice
{
	//--- Declaration
	FBDeviceDeclare( LiveSkeleton, FBDevice );

public:
	virtual bool FBCreate() override;
	virtual void FBDestroy() override;

    //--- Standard device virtual functions evaluation
	virtual bool DeviceOperation	( kDeviceOperations pOperation									) override;		//!< Operate device.
	virtual bool AnimationNodeNotify( FBAnimationNode* pAnimationNode,FBEvaluateInfo* pEvaluateInfo	) override;		//!< Real-time evaluation function.
	virtual void DeviceIONotify		( kDeviceIOs  pAction, FBDeviceNotifyInfo &pDeviceNotifyInfo	) override;		//!< Hardware I/O notification.
	virtual void DeviceTransportNotify( kTransportMode pMode, FBTime pTime, FBTime pSystem ) override;				//!< Transport notification.

	//--- Recording of frame information
	virtual void	RecordingDoneAnimation( FBAnimationNode* pAnimationNode) override;
	void	DeviceRecordFrame			(FBTime &pTime,FBDeviceNotifyInfo &pDeviceNotifyInfo);

	//--- Load/Save.
	virtual bool FbxStore	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat ) override;	//!< FBX Storage.
	virtual bool FbxRetrieve( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat ) override;	//!< FBX Retrieval.

	//--- Initialisation/Shutdown
    bool	Init	();		//!< Initialize device.
    bool	Start	();		//!< Start device.
    bool	Stop	();		//!< Stop device.
    bool	Reset	();		//!< Reset device.
    bool	Done	();		//!< Device removal.

	//--- Attributes management
	void	SetNetworkAddress	(const char* pIPAddress){ mHardware.SetNetworkAddress(pIPAddress);		}
	const char*	GetNetworkAddress	()					{ return mHardware.GetNetworkAddress();			}
	void	SetNetworkPort		(int pPort)				{ mHardware.SetNetworkPort(pPort);				}
	int		GetNetworkPort		()						{ return mHardware.GetNetworkPort();			}

	//--- Get data from hardware.
	double GetDataTX(int pChannelIndex)			{	return mHardware.GetDataTX(pChannelIndex);		}
	double GetDataTY(int pChannelIndex)			{	return mHardware.GetDataTY(pChannelIndex);		}
	double GetDataTZ(int pChannelIndex)			{	return mHardware.GetDataTZ(pChannelIndex);		}
	double GetDataRX(int pChannelIndex)			{	return mHardware.GetDataRX(pChannelIndex);		}
	double GetDataRY(int pChannelIndex)			{	return mHardware.GetDataRY(pChannelIndex);		}
	double GetDataRZ(int pChannelIndex)			{	return mHardware.GetDataRZ(pChannelIndex);		}

	//--- Marker set management.
	void	DefineHierarchy				();				//!< Define model template hierarchy.
	void	Bind();										//!< Bind models
	void	UnBind();									//!< Unbind models

	//--- Channel list manipulation.
	int		GetChannelCount()					{	return mHardware.GetChannelCount();				}
	int		GetChannelParent(int pMarkerIndex)	{	return mHardware.GetChannelParent(pMarkerIndex);}
	const char*	GetChannelName(int pMarkerIndex){	return mHardware.GetChannelName(pMarkerIndex);	}

    virtual bool ModelTemplateUnBindNotify( int pIndex, FBModelTemplate* pModelTemplate );							//!< Model Template unbinding notification callback.

	bool	ReadyForCharacterize		();					//!< Test if characterization process can be start.

	//--- Stop displaying process to local message on model unbind
	void	EventUIIdle( HISender pSender, HKEvent pEvent );

	LiveSkeletonHardware		mHardware;					//!< Hardware abstraction object.
	FBModelTemplate*			mRootTemplate;				//!< Root model binding.
private:
	std::vector<DataChannel>	mChannels;					//!< Data channels.
	FBPropertyBool				UseReferenceTransformation;	//!< Apply reference transformation on incoming global data.
	FBPropertyBool				DataIsGlobal;				//!< Set this true, if incoming data is in world space.
	FBModelRotationOrder		RotationOrder;				//!< Rotation order to use.
	bool						mHierarchyIsDefined;		//!< True if the hierarchy is already defined

	FBPlayerControl				mPlayerControl;				//!< To get play mode for recording.
	FBSystem					mSystem;
	FBApplication				mApplication;
	bool						mHasAnimationToTranspose;
	bool						mPlotting;

	// Process global data on template models to local
	void		ProcessGlobalToLocal();
	void SetupLocalGlobal(bool pGlobal);
	void			SetRotationOrder();
};

#endif /* __LIVE_SKELETON_DEVICE_H__ */
