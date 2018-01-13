#ifndef __LIVE_SKELETON_LAYOUT_H__
#define __LIVE_SKELETON_LAYOUT_H__
/**	\file	liveskeleton_layout.h
*	Declaration for the layout of a simple skeleton device.
*	Contains the declaration for the layout of a simple input
*	device class, LiveSkeletonLayout.
*/

//--- Class declaration
#include "liveskeleton_device.h"

//! Simple device layout.
class LiveSkeletonLayout : public FBDeviceLayout
{
	//--- FiLMBOX declaration.
	FBDeviceLayoutDeclare( LiveSkeletonLayout, FBDeviceLayout );

public:
	//--- FiLMBOX Creation/Destruction.
	virtual bool FBCreate();			//!< FiLMBOX constructor.
	virtual void FBDestroy();			//!< FiLMBOX destructor.

	// UI Management
	void	UICreate				();		// Create & assign UI regions
	void		UICreateLayout0		();
	void		UICreateLayout1		();
	void	UIConfigure				();		// Configure UI options
	void		UIConfigureLayout0	();
	void		UIConfigureLayout1	();
	void	UIRefresh				();		// Refresh on idle
	void		UIRefreshSpreadSheet();
	void	UIReset					();		// Reset from device values
	void		UIResetSpreadSheet	();

	// Main Layout: Events
	void	EventDeviceStatusChange					( HISender pSender, HKEvent pEvent );
	void	EventUIIdle								( HISender pSender, HKEvent pEvent );
	void	EventTabPanelChange						( HISender pSender, HKEvent pEvent );

	// Setup Layout: Events
	void	EventEditNumberSamplingRateChange		(HISender pSender, HKEvent pEvent);
	void	EventEditNetworkAddressChange			( HISender pSender, HKEvent pEvent );
	void	EventEditNetworkPortChange				( HISender pSender, HKEvent pEvent );

private:
	FBTabPanel			mTabPanel;

	FBLayout			mLayoutJoints;
		FBSpread			mSpreadJoints;

	FBLayout			mLayoutSetup;
		FBLabel				mLabelSamplingRate;
		FBEditNumber		mEditNumberSamplingRate;

	FBLayout			mLayoutCommunication;
		FBLabel				mLabelNetworkAddress;
		FBEdit				mEditNetworkAddress;
		FBLabel				mLabelNetworkPort;
		FBEdit				mEditNetworkPort;

private:
	FBSystem				mSystem;					//!< System interface.
	LiveSkeleton*			mDevice;					//!< Handle onto device.
};

#endif /* __LIVE_SKELETON_LAYOUT_H__ */
