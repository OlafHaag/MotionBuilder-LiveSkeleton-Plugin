/**	\file	liveskeleton_layout.cxx
*	Definition of a layout class for a simple skeleton device.
*	Definition of the functions of the LiveSkeletonLayout class,
*	representing the layout for a simple skeleton device.
*/

//--- Class declarations
#include "liveskeleton_device.h"
#include "liveskeleton_layout.h"

#define LIVESKELETON_LAYOUT	LiveSkeletonLayout

//--- FiLMBOX implementation and registration
FBDeviceLayoutImplementation(	LIVESKELETON_LAYOUT		);
FBRegisterDeviceLayout		(	LIVESKELETON_LAYOUT,
								LIVESKELETON_CLASSSTR,
								FB_DEFAULT_SDK_ICON			);	// Icon filename (default=Open Reality icon)

/************************************************
 *	FiLMBOX constructor.
 ************************************************/
bool LiveSkeletonLayout::FBCreate()
{
	// Get a handle on the device.
	mDevice = ((LiveSkeleton *)(FBDevice *)Device);

	// Create/configure UI
	UICreate	();
	UIConfigure	();
	UIReset		();

	// Add device & system callbacks
	mDevice->OnStatusChange.Add	( this,(FBCallback)&LiveSkeletonLayout::EventDeviceStatusChange  );
	mSystem.OnUIIdle.Add		( this,(FBCallback)&LiveSkeletonLayout::EventUIIdle              );

	return true;
}


/************************************************
 *	FiLMBOX destructor.
 ************************************************/
void LiveSkeletonLayout::FBDestroy()
{
	// Remove device & system callbacks
	mSystem.OnUIIdle.Remove		( this,(FBCallback)&LiveSkeletonLayout::EventUIIdle              );
	mDevice->OnStatusChange.Remove	( this,(FBCallback)&LiveSkeletonLayout::EventDeviceStatusChange  );
}


/************************************************
 *	Create the UI.
 ************************************************/
void LiveSkeletonLayout::UICreate()
{
	int lS, lH;		// space, height
	lS = 4;
	lH = 25;

	// Create regions
	AddRegion	( "TabPanel",	"TabPanel",		0,		kFBAttachLeft,		"",			1.00,
												0,		kFBAttachTop,		"",			1.00,
												0,		kFBAttachRight,		"",			1.00,
												lH,		kFBAttachNone,		NULL,		1.00 );
	AddRegion	( "MainLayout",	"MainLayout",	lS,		kFBAttachLeft,		"TabPanel",	1.00,
												lS,		kFBAttachBottom,	"TabPanel",	1.00,
												-lS,	kFBAttachRight,		"TabPanel",	1.00,
												-lS,	kFBAttachBottom,	"",			1.00 );

	// Assign regions
	SetControl	( "TabPanel",	mTabPanel		);
	SetControl	( "MainLayout",	mLayoutJoints	);

	// Create sub layouts
	UICreateLayout0();
	UICreateLayout1();
}


/************************************************
 *	Create the markers layout.
 ************************************************/
void LiveSkeletonLayout::UICreateLayout0()
{
	// Add regions
	mLayoutJoints.AddRegion( "SpreadJoints", "SpreadJoints",
													0,		kFBAttachLeft,		"",		1.00,
													0,		kFBAttachTop,		"",		1.00,
													0,		kFBAttachRight,		"",		1.00,
													0,		kFBAttachBottom,	"",		1.00 );

	// Assign regions
	mLayoutJoints.SetControl( "SpreadJoints", mSpreadJoints );
}


/************************************************
 *	Create the setup layout.
 ************************************************/
void LiveSkeletonLayout::UICreateLayout1()
{
	int lS, lW, lH;		// space, width, height.
	lS = 4;
	lW = 250;
	lH = 18;
		
	mLayoutSetup.AddRegion ( "LabelSamplingRate",	"LabelSamplingRate",
													lS,		kFBAttachLeft,		"",		1.00,
													lS,		kFBAttachTop,		"",		1.00,
													100,	kFBAttachNone,		NULL,	1.00,
													lH,		kFBAttachNone,		NULL,	1.00 );

	mLayoutSetup.AddRegion ( "EditNumberSamplingRate",	"EditNumberSamplingRate",
													lS,		kFBAttachRight,		"LabelSamplingRate",	1.0,
													0,		kFBAttachTop,		"LabelSamplingRate",	1.0,
													50,		kFBAttachNone,		NULL,					1.0,
													lH,		kFBAttachNone,		NULL,					1.0 );

	mLayoutSetup.SetControl("LabelSamplingRate",		mLabelSamplingRate		);
	mLayoutSetup.SetControl("EditNumberSamplingRate",	mEditNumberSamplingRate	);

	lW			= 100;
	lH			= 25;
	int lHlr	= 150;
	int lWlr	= 250;
	int lSlbx	= 30;
	int lSlby	= 12;
	int lWlb	= 80;

	mLayoutSetup.AddRegion( "NetworkSetup",	"NetworkSetup",
													lS,		kFBAttachLeft,		"",						 1.00,
													15,		kFBAttachBottom,	"EditNumberSamplingRate",1.00,
													lWlr,	kFBAttachNone,	NULL,					     1.00,
													lHlr,	kFBAttachNone,	NULL,					     1.00 );

	// Add regions (network)
	mLayoutCommunication.AddRegion( "LayoutRegionNetwork",	"LayoutRegionNetwork",
													5,		kFBAttachLeft,		"",						1.00,
													15,		kFBAttachTop,		"NetworkSetup",			1.00,
													-10,	kFBAttachWidth,		"NetworkSetup",			1.00,
													-30,	kFBAttachHeight,	"NetworkSetup",			1.00 );
	mLayoutCommunication.AddRegion( "LabelNetworkAddress",		"LabelNetworkAddress",
													lSlbx,	kFBAttachLeft,		"LayoutRegionNetwork",	1.00,
													lSlby,	kFBAttachTop,		"LayoutRegionNetwork",	1.00,
													lWlb,	kFBAttachNone,		NULL,					1.00,
													lH,		kFBAttachNone,		NULL,					1.00 );
	mLayoutCommunication.AddRegion( "EditNetworkAddress",		"EditNetworkAddress",
													lS,		kFBAttachRight,		"LabelNetworkAddress",	1.00,
													0,		kFBAttachTop,		"LabelNetworkAddress",	1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													lH,		kFBAttachNone,		NULL,					1.00 );
	mLayoutCommunication.AddRegion( "LabelNetworkPort",	"LabelNetworkPort",
													0,		kFBAttachLeft,		"LabelNetworkAddress",	1.00,
													lS,		kFBAttachBottom,	"LabelNetworkAddress",	1.00,
													0,		kFBAttachWidth,		"LabelNetworkAddress",	1.00,
													0,		kFBAttachHeight,	"LabelNetworkAddress",	1.00 );
	mLayoutCommunication.AddRegion( "EditNetworkPort",	"EditNetworkPort",
													lS,		kFBAttachRight,		"LabelNetworkPort",		1.00,
													0,		kFBAttachTop,		"LabelNetworkPort",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelNetworkPort",		1.00 );

	// Assign regions (network)
	mLayoutCommunication.SetControl( "LabelNetworkAddress",		mLabelNetworkAddress	);
	mLayoutCommunication.SetControl( "EditNetworkAddress",		mEditNetworkAddress		);
	mLayoutCommunication.SetControl( "LabelNetworkPort",		mLabelNetworkPort		);
	mLayoutCommunication.SetControl( "EditNetworkPort",			mEditNetworkPort		);

	mLayoutSetup.SetControl	( "NetworkSetup",	mLayoutCommunication	);
}


/************************************************
 *	Configure the UI elements (main layout).
 ************************************************/
void LiveSkeletonLayout::UIConfigure()
{
	SetBorder ("MainLayout", kFBStandardBorder, false,true, 1, 0,90,0);

	mTabPanel.Items.SetString("Joints~Setup");
	mTabPanel.OnChange.Add( this, (FBCallback)&LiveSkeletonLayout::EventTabPanelChange );

	UIConfigureLayout0();
	UIConfigureLayout1();
}


/************************************************
 *	Configure the UI elements (joints layout).
 ************************************************/
void LiveSkeletonLayout::UIConfigureLayout0()
{
}


/************************************************
 *	Configure the UI elements (setup layout).
 ************************************************/
void LiveSkeletonLayout::UIConfigureLayout1()
{
	mLabelSamplingRate.Caption = "Sampling Rate :";

	mEditNumberSamplingRate.LargeStep = 0.0;
	mEditNumberSamplingRate.SmallStep = 0.0;
	mEditNumberSamplingRate.OnChange.Add(this, (FBCallback)&LiveSkeletonLayout::EventEditNumberSamplingRateChange);

    mLayoutCommunication.SetBorder( "LayoutRegionNetwork",	kFBEmbossBorder,false,true,2,1,90.0,0);
	mLayoutCommunication.SetBorder( "EditNetworkAddress",	kFBStandardBorder, false,true, 1, 0,90,0);
	mLayoutCommunication.SetBorder( "EditNetworkPort",		kFBStandardBorder, false,true, 1, 0,90,0);


	mLabelNetworkAddress.Caption	= "Address :";
	mEditNetworkAddress.Text		= mDevice->GetNetworkAddress();
	mEditNetworkAddress.OnChange.Add( this, (FBCallback) &LiveSkeletonLayout::EventEditNetworkAddressChange );

	mLabelNetworkPort.Caption		= "Port :";

	char	lBuffer[40];
	sprintf(lBuffer, "%d", mDevice->GetNetworkPort() );
	mEditNetworkPort.Text = lBuffer;
	mEditNetworkPort.OnChange.Add( this, (FBCallback) &LiveSkeletonLayout::EventEditNetworkPortChange );
}


/************************************************
 *	Refresh the UI.
 ************************************************/
void LiveSkeletonLayout::UIRefresh()
{
	UIRefreshSpreadSheet();
}


/************************************************
 *	Refresh the spreadsheet content.
 ************************************************/
void LiveSkeletonLayout::UIRefreshSpreadSheet()
{
  	for(int i=0; i<mDevice->GetChannelCount();i++)
	{
		// Update name, too? Or maybe read from selected skeleton.
		mSpreadJoints.SetCell( i, 0, mDevice->GetDataTX(i) );
		mSpreadJoints.SetCell( i, 1, mDevice->GetDataTY(i) );
		mSpreadJoints.SetCell( i, 2, mDevice->GetDataTZ(i) );
		mSpreadJoints.SetCell( i, 3, mDevice->GetDataRX(i) );
		mSpreadJoints.SetCell( i, 4, mDevice->GetDataRY(i) );
		mSpreadJoints.SetCell( i, 5, mDevice->GetDataRZ(i) );
	}
}


/************************************************
 *	Reset the UI values from device.
 ************************************************/
void LiveSkeletonLayout::UIReset()
{
	char	lBuffer[40];
	sprintf(lBuffer, "%d", mDevice->GetNetworkPort());

	UIResetSpreadSheet();

	mEditNetworkAddress.Text = mDevice->GetNetworkAddress();
	mEditNetworkPort.Text = lBuffer;

	mEditNumberSamplingRate.Value = 1.0 / ((FBTime)mDevice->SamplingPeriod).GetSecondDouble();
}


/************************************************
 *	Re-build the spreadsheet.
 ************************************************/
void LiveSkeletonLayout::UIResetSpreadSheet()
{
	int i;

	mSpreadJoints.Clear();

	// Spreadsheet
	int lColumnIndex = -1;
	mSpreadJoints.GetColumn(lColumnIndex).Width = 200;

	// column 0: Translation X
	mSpreadJoints.ColumnAdd ("PosX");
	lColumnIndex++;
	mSpreadJoints.GetColumn(lColumnIndex).Width = 60;
	mSpreadJoints.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

	// column 1: Translation Y
	mSpreadJoints.ColumnAdd ("PosY");
	lColumnIndex++;
	mSpreadJoints.GetColumn(lColumnIndex).Width = 60;
 	mSpreadJoints.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

 	// column 2: Translation Z
	mSpreadJoints.ColumnAdd ("PosZ");
	lColumnIndex++;
	mSpreadJoints.GetColumn(lColumnIndex).Width = 60;
	mSpreadJoints.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

	// column 3: Rotation X
	mSpreadJoints.ColumnAdd ("RotX");
	lColumnIndex++;
	mSpreadJoints.GetColumn(lColumnIndex).Width = 60;
	mSpreadJoints.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

	// column 4: Rotation Y
	mSpreadJoints.ColumnAdd ("RotY");
	lColumnIndex++;
	mSpreadJoints.GetColumn(lColumnIndex).Width = 60;
 	mSpreadJoints.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

 	// column 5: Rotation Z
	mSpreadJoints.ColumnAdd ("RotZ");
	lColumnIndex++;
	mSpreadJoints.GetColumn(lColumnIndex).Width = 60;
	mSpreadJoints.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

	for (i=0;i<mDevice->GetChannelCount();i++)
	{
 		mSpreadJoints.RowAdd( mDevice->GetChannelName(i), i );
	 	mSpreadJoints.GetCell(i,lColumnIndex).ReadOnly = true;
	}
}


/************************************************
 *	Tab panel change callback.
 ************************************************/
void LiveSkeletonLayout::EventTabPanelChange( HISender pSender, HKEvent pEvent )
{
	switch( mTabPanel.ItemIndex )
	{
		case 0:	SetControl("MainLayout", mLayoutJoints	);	break;
		case 1:	SetControl("MainLayout", mLayoutSetup	);	break;
	}
}

/************************************************
 *	Server port change callback.
 ************************************************/
void LiveSkeletonLayout::EventEditNetworkPortChange( HISender pSender, HKEvent pEvent )
{
	int		lPort;
	char	lBuffer[40];

	sscanf(mEditNetworkPort.Text.AsString(), "%d", &lPort);
	mDevice->SetNetworkPort(lPort);
	lPort = mDevice->GetNetworkPort();
	sprintf(lBuffer, "%d", lPort );
	mEditNetworkPort.Text = lBuffer;
}


/************************************************
 *	Server address change callback.
 ************************************************/
void LiveSkeletonLayout::EventEditNetworkAddressChange( HISender pSender, HKEvent pEvent )
{
	mDevice->SetNetworkAddress(mEditNetworkAddress.Text.AsString());
	mEditNetworkAddress.Text = mDevice->GetNetworkAddress();
}

/************************************************
*	Sampling rate change callback.
************************************************/
void LiveSkeletonLayout::EventEditNumberSamplingRateChange(HISender pSender, HKEvent pEvent)
{
	bool lOnline = mDevice->Online;
	double lVal = mEditNumberSamplingRate.Value;

	if (lVal > 0.0)
	{
		if (lOnline)
		{
			mDevice->DeviceSendCommand(FBDevice::kOpStop);
		}

		FBTime lTime;
		lTime.SetSecondDouble(1.0 / lVal);
		mDevice->SamplingPeriod = lTime;

		if (lOnline)
		{
			mDevice->DeviceSendCommand(FBDevice::kOpStart);
		}

		UIReset();
	}
}

/************************************************
 *	Device status change callback.
 ************************************************/
void LiveSkeletonLayout::EventDeviceStatusChange( HISender pSender, HKEvent pEvent )
{
	UIReset();
}


/************************************************
 *	UI Idle callback.
 ************************************************/
void LiveSkeletonLayout::EventUIIdle( HISender pSender, HKEvent pEvent )
{
	if( mDevice->Online )
	{
		UIRefresh();
	}
}

//simple name mapping.
static void SetupMapping(FBCharacter* pCharacter, FBModel* pParent)
{
    FBString lName = (const char*)pParent->Name; lName += "Link";
	FBProperty* lLink = pCharacter->PropertyList.Find(lName,false);
	if(lLink && lLink->IsList())
	{
		((FBPropertyListComponent*)lLink)->Add(pParent);
	}
	
	//do the same for children
	for(int i = 0; i < pParent->Children.GetCount(); i++)
	{
		SetupMapping(pCharacter,pParent->Children[i]);
	}
}
