#ifndef __LIVE_SKELETON_HARDWARE_H__
#define __LIVE_SKELETON_HARDWARE_H__
/**	\file	liveskeleton_hardware.h
*	Declaration of a virtual hardware class.
*	Contains the declaration of the virtual input hardware class
*	LiveSkeletonHardware.
*/
#include <vector>
//--- SDK include
#include <fbsdk/fbsdk.h>

#pragma warning(push)
#pragma warning(disable:4265)  // FixMe: Without disabling this warning, there're compiler errors! "class has virtual functions, but destructor is not virtual"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#pragma warning(pop)

#include "gen-cpp/LiveskeletonService.h"

class ThriftProxy {
public:
	ThriftProxy();
	ThriftProxy(const std::string& host, int port);
	~ThriftProxy();

	bool Open();
	bool IsOpen();
	bool Close();

private:
	boost::shared_ptr<apache::thrift::transport::TTransport> socket;
	boost::shared_ptr<apache::thrift::transport::TTransport> transport;
	boost::shared_ptr<apache::thrift::protocol::TProtocol> protocol;
public:
	LiveSkeletonTransfer::LiveSkeletonServiceClient client;
};

//! Simple hardware.
class LiveSkeletonHardware
{
public:
	//! Constructor & destructor
	LiveSkeletonHardware();
	~LiveSkeletonHardware();

	//--- Opens and closes connection with data server. returns true if successful
	bool	Open();								//!< Open the connection.
	bool	Close();							//!< Close connection.

	std::string GetServerVersion();					//!< Get version of estimation script.
	std::string GetServerStatus();					//!< What's the script doing?
	bool	GetSetupInfo	();						//!< Get the setup information.

	//--- Hardware communication
	bool	IsOpen() { return mThrift.IsOpen(); }   //!< See if the connection is open.
	bool	StartDataStream	();						//!< Put the device in streaming mode.
	bool	StopDataStream	();						//!< Take the device out of streaming mode.

	void	ResetPacketTimeOffset(FBTime &pTime);	//!< Reset time offset for recording
	bool	FetchDataPacket	(FBTime &pTime);		//!< Fetch a data packet from the computer.

	//--- Attribute management
	void		SetNetworkAddress	(const char *pIPAddress){ mNetworkAddress =  pIPAddress;			}
	const char*	GetNetworkAddress	()						{ return mNetworkAddress;					}
	void		SetNetworkPort		(int pPort)				{ mNetworkPort = pPort;						}
	int			GetNetworkPort		()						{ return mNetworkPort;						}

	//--- Channel & Channel data management
	int		GetChannelCount	()					{	return mChannel.size();					}
	const char*	GetChannelName(int pChannel)	{	return mChannel[pChannel].mName.c_str();	}
	int		GetChannelParent(int pChannel)		{	return mChannel[pChannel].mParentChannel;	}
	FBVector3d GetDefaultT	(int pChannel)		{	SkeletonNodeInfo& lSI = mChannel[pChannel]; return FBVector3d(lSI.mDefaultT[0],lSI.mDefaultT[1],lSI.mDefaultT[2]);		}
	FBVector3d GetDefaultR	(int pChannel)		{	SkeletonNodeInfo& lSI = mChannel[pChannel]; return FBVector3d(lSI.mDefaultR[0],lSI.mDefaultR[1],lSI.mDefaultR[2]);		}
	double	GetDataTX		(int pChannel)		{	return mChannel[pChannel].mT[0];		}
	double	GetDataTY		(int pChannel)		{	return mChannel[pChannel].mT[1];		}
	double	GetDataTZ		(int pChannel)		{	return mChannel[pChannel].mT[2];		}
	double	GetDataRX		(int pChannel)		{	return mChannel[pChannel].mR[0];		}
	double	GetDataRY		(int pChannel)		{	return mChannel[pChannel].mR[1];		}
	double	GetDataRZ		(int pChannel)		{	return mChannel[pChannel].mR[2];		}

private:
	struct SkeletonNodeInfo
	{
		std::string	mName;
		int			mParentChannel;
		double		mDefaultT[3];
		double		mDefaultR[3];
		double		mT[3];
		double		mR[3];
	};

	std::vector<SkeletonNodeInfo>			mChannel;			//!< Dynamic array for channels. Channel data & info.
	LiveSkeletonTransfer::SkeletonData		mLastSkeletonData;	//!< Last data that came in.

	LiveSkeletonTransfer::TimeStamp			mPacketTimeOffset;	//!< Packet time offset for recording
	FBTime		mStartRecordingTime;			//!< Time at start of recording

	FBString	mNetworkAddress;				//!< Network address.
	int			mNetworkPort;					//!< Network port.
	FBSystem	mSystem;						//!< System interface.

	ThriftProxy	mThrift;						//!< RPC layer for communication.
	LiveSkeletonTransfer::LiveSkeletonServiceClient* pClient;			//!< Pointer to client of mThrift.
};

#endif /* __LIVE_SKELETON_HARDWARE_H__ */
