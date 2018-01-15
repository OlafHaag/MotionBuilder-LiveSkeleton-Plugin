/**	\file	liveskeleton_hardware.cxx
*	Definition of a virtual hardware class.
*	Contains the definition of the functions for the
*	LiveSkeletonHardware class.
*/

//--- Class declaration
#include "liveskeleton_hardware.h"

#include "gen-cpp/LiveskeletonService.h"

using namespace LiveSkeletonTransfer;

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

/************************************************
*	Thrift Proxy Constructors.
************************************************/
ThriftProxy::ThriftProxy() :
	socket(new TSocket("127.0.0.1", 9090)),
	transport(new TFramedTransport(socket)),
	protocol(new TBinaryProtocol(transport)),
	client(protocol)
{
}

ThriftProxy::ThriftProxy(const std::string& host, int port) :
	socket(new TSocket(host, port)),
	transport(new TFramedTransport(socket)),
	protocol(new TBinaryProtocol(transport)),
	client(protocol)
{
}

ThriftProxy::~ThriftProxy()
{
	transport->close();
}

bool ThriftProxy::Open()
{
	try {
		transport->open();
		return true;
	}
	catch (TException& tx) {
		FBTrace("ERROR: Transport could not be opened! %s\n", tx.what());
		return false;
	}
}

bool ThriftProxy::Close()
{
	try {
		transport->close();
		return true;
	}
	catch (TException& tx) {
		FBTrace("ERROR: Transport could not be closed! %s\n", tx.what());
		return false;
	}
}

bool ThriftProxy::IsOpen()
{
	try {
		if (transport->isOpen())
		{ return true; } 
		else
		{ return false; }
	}
	catch (TException& tx) {
		FBTrace("ERROR: Transport is not open? %s\n", tx.what());
		return false;
	}
}

/************************************************
 *	Constructor.
 ************************************************/
LiveSkeletonHardware::LiveSkeletonHardware() :
	mNetworkPort( 9090 )
{
	mNetworkAddress	= "127.0.0.1";
	mChannel.reserve(20);  // Reserve memory up to 20 joints.
}


/************************************************
 *	Destructor.
 ************************************************/
LiveSkeletonHardware::~LiveSkeletonHardware()
{
}


/************************************************
 *	Open device communications.
 ************************************************/
bool LiveSkeletonHardware::Open()
{
	FBTrace("Attempting to connect ThriftProxy to Address: %s:%d\n", (char*)mNetworkAddress, mNetworkPort);
	mThrift = ThriftProxy((char*)mNetworkAddress, mNetworkPort);
	pClient = &mThrift.client;
	if (!mThrift.Open())
	{
		return false;
	}
	return true;
}

/************************************************
*	Get version of estimation script.
************************************************/
std::string LiveSkeletonHardware::GetServerVersion()
{
	std::string ver;
	try
	{
		pClient->getServerVersion(ver);
		return ver;
	}
	catch (...)
	{
		FBTrace("Error in Hardware::GetServerVersion()");
	}
	return "not connected";
}

/************************************************
*	Get te status of the estimation script.
************************************************/
std::string LiveSkeletonHardware::GetServerStatus()
{
	ServerStatus::type status;
	std::string status_message;
	try
	{
		status = pClient->getServerStatus();
	}
	catch (...)
	{
		FBTrace("Error in Hardware::GetServerStatus");
		return "not connected";
	}
	switch (status)
	{
	case LiveSkeletonTransfer::ServerStatus::NOT_STARTED:
		status_message = "Estimation not started.";
		break;
	case LiveSkeletonTransfer::ServerStatus::INITIALIZED:
		status_message = "Estimator initialized.";
		break;
	case LiveSkeletonTransfer::ServerStatus::DEFAULT_SET:
		status_message = "Default pose was set.";
		break;
	case LiveSkeletonTransfer::ServerStatus::CONNECTED:
		status_message = "Estimation client connected to server.";
		break;
	case LiveSkeletonTransfer::ServerStatus::ESTIMATING:
		status_message = "Estimating...";
		break;
	case LiveSkeletonTransfer::ServerStatus::STOPPED:
		status_message = "Estimation stopped.";
		break;
	default:
		status_message = "Server status unknown.";
		break;
	}
	return status_message;
}

/************************************************
 *	Get device setup information.
 ************************************************/
bool LiveSkeletonHardware::GetSetupInfo()
{
	if (!IsOpen())
	{
		return false;
	}

	bool server_has_default = false;
	try
	{
		server_has_default = (pClient->getServerStatus() >= LiveSkeletonTransfer::ServerStatus::DEFAULT_SET);
	}
	catch (const std::exception&)
	{
		FBTrace("Error occured trying to getServerStatus() in Hardware::GetSetupInfo()");
		return false;
	}

	// Read from hardware.
	if (server_has_default == true)
	{
		SkeletonData DefaultPose;

		try
		{
			pClient->getSkeletonDefaultPose(DefaultPose);  // FixMe: Causes exception!
		}
		catch (...)
		{
			FBTrace("Error occured trying to getSkeletonDefaultPose in Hardware::GetSetupInfo()");
			return false;
		}

		SkeletonNodeInfo lNodeInfo;

		int lCount = (int)(DefaultPose.joints.size());  // Cast from size_type to int is dirty?
		for (int i = 0; i<lCount; i++)
		{
			// Convert to SkeletonNodeInfo.
			lNodeInfo.mName = std::string(DefaultPose.joints[i].name);
			lNodeInfo.mParentChannel = -1;
			std::copy(DefaultPose.joints[i].pos.begin(), DefaultPose.joints[i].pos.end(), lNodeInfo.mT);
			std::copy(DefaultPose.joints[i].rot.begin(), DefaultPose.joints[i].rot.end(), lNodeInfo.mR);
			mChannel.push_back(lNodeInfo);
		}

		for (int i = 0; i < lCount; i++)
		{
			// Copy the default pose to the current channels.
			memcpy(mChannel[i].mDefaultT, mChannel[i].mT, sizeof(double) * 3);
			memcpy(mChannel[i].mDefaultR, mChannel[i].mR, sizeof(double) * 3);

			// Find parent channel indices.
			for (int p = 0; p < mChannel.size(); p++)
			{
				if ( std::strcmp(mChannel[p].mName.c_str(), DefaultPose.joints[i].parent.c_str()) == 0 )
				{
					mChannel[i].mParentChannel = p;
					break;
				}
			}
		}
		return true;
	}
	return false;
}

/************************************************
 *	Close device communications.
 ************************************************/
bool LiveSkeletonHardware::Close()
{
	if (!mThrift.Close())
	{
		return false;
	}
	mChannel.clear();
	return true;
}

/************************************************
 *	Take current DataBuffer time as a time offset
 ************************************************/
void LiveSkeletonHardware::ResetPacketTimeOffset(FBTime &pTime)
{
	mPacketTimeOffset = mLastSkeletonData.timestamp;
	mStartRecordingTime = pTime;
}

/************************************************
 *	Fetch a data packet from the device. Must not block!
 ************************************************/
bool LiveSkeletonHardware::FetchDataPacket(FBTime &pTime)
{
	if (!IsOpen())
	{
		return false;
	}
	bool server_is_estimating = false;
	try
	{
		server_is_estimating = pClient->getServerStatus() >= LiveSkeletonTransfer::ServerStatus::ESTIMATING;
	}
	catch (...)
	{
		FBTrace("Error in Hardware::FetchDataPacket() at pClient->getServerStatus()");
		return false;  // Not really necessary, since server_is_estimating is false at this point.
	}
	if (server_is_estimating == true)
	{
		try
		{
			//FBTrace("Fetch... %f s\n", pTime.GetSecondDouble());
			pClient->getSkeletonData(mLastSkeletonData);
		}
		catch (...)
		{
			FBTrace("Error in Hardware::FetchDataPacket at getSkeletonData()");
			return false;
		}
		SkeletonNodeInfo*  lIter;

		for (int i = 0; i < GetChannelCount(); i++)
		{
			lIter = &mChannel[i];
			std::copy(mLastSkeletonData.joints[i].pos.begin(), mLastSkeletonData.joints[i].pos.end(), lIter->mT);
			std::copy(mLastSkeletonData.joints[i].rot.begin(), mLastSkeletonData.joints[i].rot.end(), lIter->mR);
		}

		// Update packet relative time.
		pTime.SetSecondDouble(mLastSkeletonData.timestamp-mPacketTimeOffset);  // FixMe: What's this about?! timestamp is measured with time.clock()->seconds
		pTime += mStartRecordingTime;
		return true;
	}
	return false;  // Todo: What happens to pTime?!
}

/************************************************
 *	Start data streaming from device.
 ************************************************/
bool LiveSkeletonHardware::StartDataStream()
{
	// TODO: We may not really need that, but keep it for the future.
	// TODO: Maybe set flag on thrift server like DoLoopEstimation?
	if (!IsOpen())
	{
		return false;
	}
	return true;
}

/************************************************
 *	Stop data streaming from device.
 ************************************************/
bool LiveSkeletonHardware::StopDataStream()
{
	if (!mThrift.Close())
	{
		return false;
	}
	mChannel.clear();
	return true;
}
