/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef LiveSkeletonService_H
#define LiveSkeletonService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "LiveSkeleton_types.h"

namespace LiveSkeletonTransfer {

#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class LiveSkeletonServiceIf {
 public:
  virtual ~LiveSkeletonServiceIf() {}
  virtual void ping() = 0;
  virtual void getServerVersion(std::string& _return) = 0;
  virtual ServerStatus::type getServerStatus() = 0;
  virtual void setServerStatus(const ServerStatus::type status) = 0;
  virtual void stopServer() = 0;
  virtual void shutdown() = 0;
  virtual void getSkeletonDefaultPose(SkeletonData& _return) = 0;
  virtual void setSkeletonDefaultPose(const SkeletonData& data) = 0;
  virtual void setSkeletonData(const SkeletonData& data) = 0;
  virtual void getSkeletonData(SkeletonData& _return) = 0;
  virtual bool getDoLoopEstimation() = 0;
  virtual void setDoLoopEstimation(const bool state) = 0;
};

class LiveSkeletonServiceIfFactory {
 public:
  typedef LiveSkeletonServiceIf Handler;

  virtual ~LiveSkeletonServiceIfFactory() {}

  virtual LiveSkeletonServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(LiveSkeletonServiceIf* /* handler */) = 0;
};

class LiveSkeletonServiceIfSingletonFactory : virtual public LiveSkeletonServiceIfFactory {
 public:
  LiveSkeletonServiceIfSingletonFactory(const boost::shared_ptr<LiveSkeletonServiceIf>& iface) : iface_(iface) {}
  virtual ~LiveSkeletonServiceIfSingletonFactory() {}

  virtual LiveSkeletonServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(LiveSkeletonServiceIf* /* handler */) {}

 protected:
  boost::shared_ptr<LiveSkeletonServiceIf> iface_;
};

class LiveSkeletonServiceNull : virtual public LiveSkeletonServiceIf {
 public:
  virtual ~LiveSkeletonServiceNull() {}
  void ping() {
    return;
  }
  void getServerVersion(std::string& /* _return */) {
    return;
  }
  ServerStatus::type getServerStatus() {
    ServerStatus::type _return = (ServerStatus::type)0;
    return _return;
  }
  void setServerStatus(const ServerStatus::type /* status */) {
    return;
  }
  void stopServer() {
    return;
  }
  void shutdown() {
    return;
  }
  void getSkeletonDefaultPose(SkeletonData& /* _return */) {
    return;
  }
  void setSkeletonDefaultPose(const SkeletonData& /* data */) {
    return;
  }
  void setSkeletonData(const SkeletonData& /* data */) {
    return;
  }
  void getSkeletonData(SkeletonData& /* _return */) {
    return;
  }
  bool getDoLoopEstimation() {
    bool _return = false;
    return _return;
  }
  void setDoLoopEstimation(const bool /* state */) {
    return;
  }
};


class LiveSkeletonService_ping_args {
 public:

  LiveSkeletonService_ping_args(const LiveSkeletonService_ping_args&);
  LiveSkeletonService_ping_args& operator=(const LiveSkeletonService_ping_args&);
  LiveSkeletonService_ping_args() {
  }

  virtual ~LiveSkeletonService_ping_args() throw();

  bool operator == (const LiveSkeletonService_ping_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LiveSkeletonService_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_ping_pargs {
 public:


  virtual ~LiveSkeletonService_ping_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_ping_result {
 public:

  LiveSkeletonService_ping_result(const LiveSkeletonService_ping_result&);
  LiveSkeletonService_ping_result& operator=(const LiveSkeletonService_ping_result&);
  LiveSkeletonService_ping_result() {
  }

  virtual ~LiveSkeletonService_ping_result() throw();

  bool operator == (const LiveSkeletonService_ping_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LiveSkeletonService_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_ping_presult {
 public:


  virtual ~LiveSkeletonService_ping_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class LiveSkeletonService_getServerVersion_args {
 public:

  LiveSkeletonService_getServerVersion_args(const LiveSkeletonService_getServerVersion_args&);
  LiveSkeletonService_getServerVersion_args& operator=(const LiveSkeletonService_getServerVersion_args&);
  LiveSkeletonService_getServerVersion_args() {
  }

  virtual ~LiveSkeletonService_getServerVersion_args() throw();

  bool operator == (const LiveSkeletonService_getServerVersion_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LiveSkeletonService_getServerVersion_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getServerVersion_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_getServerVersion_pargs {
 public:


  virtual ~LiveSkeletonService_getServerVersion_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getServerVersion_result__isset {
  _LiveSkeletonService_getServerVersion_result__isset() : success(false) {}
  bool success :1;
} _LiveSkeletonService_getServerVersion_result__isset;

class LiveSkeletonService_getServerVersion_result {
 public:

  LiveSkeletonService_getServerVersion_result(const LiveSkeletonService_getServerVersion_result&);
  LiveSkeletonService_getServerVersion_result& operator=(const LiveSkeletonService_getServerVersion_result&);
  LiveSkeletonService_getServerVersion_result() : success() {
  }

  virtual ~LiveSkeletonService_getServerVersion_result() throw();
  std::string success;

  _LiveSkeletonService_getServerVersion_result__isset __isset;

  void __set_success(const std::string& val);

  bool operator == (const LiveSkeletonService_getServerVersion_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const LiveSkeletonService_getServerVersion_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getServerVersion_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getServerVersion_presult__isset {
  _LiveSkeletonService_getServerVersion_presult__isset() : success(false) {}
  bool success :1;
} _LiveSkeletonService_getServerVersion_presult__isset;

class LiveSkeletonService_getServerVersion_presult {
 public:


  virtual ~LiveSkeletonService_getServerVersion_presult() throw();
  std::string* success;

  _LiveSkeletonService_getServerVersion_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class LiveSkeletonService_getServerStatus_args {
 public:

  LiveSkeletonService_getServerStatus_args(const LiveSkeletonService_getServerStatus_args&);
  LiveSkeletonService_getServerStatus_args& operator=(const LiveSkeletonService_getServerStatus_args&);
  LiveSkeletonService_getServerStatus_args() {
  }

  virtual ~LiveSkeletonService_getServerStatus_args() throw();

  bool operator == (const LiveSkeletonService_getServerStatus_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LiveSkeletonService_getServerStatus_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getServerStatus_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_getServerStatus_pargs {
 public:


  virtual ~LiveSkeletonService_getServerStatus_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getServerStatus_result__isset {
  _LiveSkeletonService_getServerStatus_result__isset() : success(false) {}
  bool success :1;
} _LiveSkeletonService_getServerStatus_result__isset;

class LiveSkeletonService_getServerStatus_result {
 public:

  LiveSkeletonService_getServerStatus_result(const LiveSkeletonService_getServerStatus_result&);
  LiveSkeletonService_getServerStatus_result& operator=(const LiveSkeletonService_getServerStatus_result&);
  LiveSkeletonService_getServerStatus_result() : success((ServerStatus::type)0) {
  }

  virtual ~LiveSkeletonService_getServerStatus_result() throw();
  ServerStatus::type success;

  _LiveSkeletonService_getServerStatus_result__isset __isset;

  void __set_success(const ServerStatus::type val);

  bool operator == (const LiveSkeletonService_getServerStatus_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const LiveSkeletonService_getServerStatus_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getServerStatus_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getServerStatus_presult__isset {
  _LiveSkeletonService_getServerStatus_presult__isset() : success(false) {}
  bool success :1;
} _LiveSkeletonService_getServerStatus_presult__isset;

class LiveSkeletonService_getServerStatus_presult {
 public:


  virtual ~LiveSkeletonService_getServerStatus_presult() throw();
  ServerStatus::type* success;

  _LiveSkeletonService_getServerStatus_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _LiveSkeletonService_setServerStatus_args__isset {
  _LiveSkeletonService_setServerStatus_args__isset() : status(false) {}
  bool status :1;
} _LiveSkeletonService_setServerStatus_args__isset;

class LiveSkeletonService_setServerStatus_args {
 public:

  LiveSkeletonService_setServerStatus_args(const LiveSkeletonService_setServerStatus_args&);
  LiveSkeletonService_setServerStatus_args& operator=(const LiveSkeletonService_setServerStatus_args&);
  LiveSkeletonService_setServerStatus_args() : status((ServerStatus::type)0) {
  }

  virtual ~LiveSkeletonService_setServerStatus_args() throw();
  ServerStatus::type status;

  _LiveSkeletonService_setServerStatus_args__isset __isset;

  void __set_status(const ServerStatus::type val);

  bool operator == (const LiveSkeletonService_setServerStatus_args & rhs) const
  {
    if (!(status == rhs.status))
      return false;
    return true;
  }
  bool operator != (const LiveSkeletonService_setServerStatus_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_setServerStatus_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_setServerStatus_pargs {
 public:


  virtual ~LiveSkeletonService_setServerStatus_pargs() throw();
  const ServerStatus::type* status;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_stopServer_args {
 public:

  LiveSkeletonService_stopServer_args(const LiveSkeletonService_stopServer_args&);
  LiveSkeletonService_stopServer_args& operator=(const LiveSkeletonService_stopServer_args&);
  LiveSkeletonService_stopServer_args() {
  }

  virtual ~LiveSkeletonService_stopServer_args() throw();

  bool operator == (const LiveSkeletonService_stopServer_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LiveSkeletonService_stopServer_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_stopServer_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_stopServer_pargs {
 public:


  virtual ~LiveSkeletonService_stopServer_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_shutdown_args {
 public:

  LiveSkeletonService_shutdown_args(const LiveSkeletonService_shutdown_args&);
  LiveSkeletonService_shutdown_args& operator=(const LiveSkeletonService_shutdown_args&);
  LiveSkeletonService_shutdown_args() {
  }

  virtual ~LiveSkeletonService_shutdown_args() throw();

  bool operator == (const LiveSkeletonService_shutdown_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LiveSkeletonService_shutdown_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_shutdown_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_shutdown_pargs {
 public:


  virtual ~LiveSkeletonService_shutdown_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_getSkeletonDefaultPose_args {
 public:

  LiveSkeletonService_getSkeletonDefaultPose_args(const LiveSkeletonService_getSkeletonDefaultPose_args&);
  LiveSkeletonService_getSkeletonDefaultPose_args& operator=(const LiveSkeletonService_getSkeletonDefaultPose_args&);
  LiveSkeletonService_getSkeletonDefaultPose_args() {
  }

  virtual ~LiveSkeletonService_getSkeletonDefaultPose_args() throw();

  bool operator == (const LiveSkeletonService_getSkeletonDefaultPose_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LiveSkeletonService_getSkeletonDefaultPose_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getSkeletonDefaultPose_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_getSkeletonDefaultPose_pargs {
 public:


  virtual ~LiveSkeletonService_getSkeletonDefaultPose_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getSkeletonDefaultPose_result__isset {
  _LiveSkeletonService_getSkeletonDefaultPose_result__isset() : success(false) {}
  bool success :1;
} _LiveSkeletonService_getSkeletonDefaultPose_result__isset;

class LiveSkeletonService_getSkeletonDefaultPose_result {
 public:

  LiveSkeletonService_getSkeletonDefaultPose_result(const LiveSkeletonService_getSkeletonDefaultPose_result&);
  LiveSkeletonService_getSkeletonDefaultPose_result& operator=(const LiveSkeletonService_getSkeletonDefaultPose_result&);
  LiveSkeletonService_getSkeletonDefaultPose_result() {
  }

  virtual ~LiveSkeletonService_getSkeletonDefaultPose_result() throw();
  SkeletonData success;

  _LiveSkeletonService_getSkeletonDefaultPose_result__isset __isset;

  void __set_success(const SkeletonData& val);

  bool operator == (const LiveSkeletonService_getSkeletonDefaultPose_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const LiveSkeletonService_getSkeletonDefaultPose_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getSkeletonDefaultPose_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getSkeletonDefaultPose_presult__isset {
  _LiveSkeletonService_getSkeletonDefaultPose_presult__isset() : success(false) {}
  bool success :1;
} _LiveSkeletonService_getSkeletonDefaultPose_presult__isset;

class LiveSkeletonService_getSkeletonDefaultPose_presult {
 public:


  virtual ~LiveSkeletonService_getSkeletonDefaultPose_presult() throw();
  SkeletonData* success;

  _LiveSkeletonService_getSkeletonDefaultPose_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _LiveSkeletonService_setSkeletonDefaultPose_args__isset {
  _LiveSkeletonService_setSkeletonDefaultPose_args__isset() : data(false) {}
  bool data :1;
} _LiveSkeletonService_setSkeletonDefaultPose_args__isset;

class LiveSkeletonService_setSkeletonDefaultPose_args {
 public:

  LiveSkeletonService_setSkeletonDefaultPose_args(const LiveSkeletonService_setSkeletonDefaultPose_args&);
  LiveSkeletonService_setSkeletonDefaultPose_args& operator=(const LiveSkeletonService_setSkeletonDefaultPose_args&);
  LiveSkeletonService_setSkeletonDefaultPose_args() {
  }

  virtual ~LiveSkeletonService_setSkeletonDefaultPose_args() throw();
  SkeletonData data;

  _LiveSkeletonService_setSkeletonDefaultPose_args__isset __isset;

  void __set_data(const SkeletonData& val);

  bool operator == (const LiveSkeletonService_setSkeletonDefaultPose_args & rhs) const
  {
    if (!(data == rhs.data))
      return false;
    return true;
  }
  bool operator != (const LiveSkeletonService_setSkeletonDefaultPose_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_setSkeletonDefaultPose_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_setSkeletonDefaultPose_pargs {
 public:


  virtual ~LiveSkeletonService_setSkeletonDefaultPose_pargs() throw();
  const SkeletonData* data;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_setSkeletonData_args__isset {
  _LiveSkeletonService_setSkeletonData_args__isset() : data(false) {}
  bool data :1;
} _LiveSkeletonService_setSkeletonData_args__isset;

class LiveSkeletonService_setSkeletonData_args {
 public:

  LiveSkeletonService_setSkeletonData_args(const LiveSkeletonService_setSkeletonData_args&);
  LiveSkeletonService_setSkeletonData_args& operator=(const LiveSkeletonService_setSkeletonData_args&);
  LiveSkeletonService_setSkeletonData_args() {
  }

  virtual ~LiveSkeletonService_setSkeletonData_args() throw();
  SkeletonData data;

  _LiveSkeletonService_setSkeletonData_args__isset __isset;

  void __set_data(const SkeletonData& val);

  bool operator == (const LiveSkeletonService_setSkeletonData_args & rhs) const
  {
    if (!(data == rhs.data))
      return false;
    return true;
  }
  bool operator != (const LiveSkeletonService_setSkeletonData_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_setSkeletonData_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_setSkeletonData_pargs {
 public:


  virtual ~LiveSkeletonService_setSkeletonData_pargs() throw();
  const SkeletonData* data;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_getSkeletonData_args {
 public:

  LiveSkeletonService_getSkeletonData_args(const LiveSkeletonService_getSkeletonData_args&);
  LiveSkeletonService_getSkeletonData_args& operator=(const LiveSkeletonService_getSkeletonData_args&);
  LiveSkeletonService_getSkeletonData_args() {
  }

  virtual ~LiveSkeletonService_getSkeletonData_args() throw();

  bool operator == (const LiveSkeletonService_getSkeletonData_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LiveSkeletonService_getSkeletonData_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getSkeletonData_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_getSkeletonData_pargs {
 public:


  virtual ~LiveSkeletonService_getSkeletonData_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getSkeletonData_result__isset {
  _LiveSkeletonService_getSkeletonData_result__isset() : success(false), timeout(false) {}
  bool success :1;
  bool timeout :1;
} _LiveSkeletonService_getSkeletonData_result__isset;

class LiveSkeletonService_getSkeletonData_result {
 public:

  LiveSkeletonService_getSkeletonData_result(const LiveSkeletonService_getSkeletonData_result&);
  LiveSkeletonService_getSkeletonData_result& operator=(const LiveSkeletonService_getSkeletonData_result&);
  LiveSkeletonService_getSkeletonData_result() {
  }

  virtual ~LiveSkeletonService_getSkeletonData_result() throw();
  SkeletonData success;
  TimedOutException timeout;

  _LiveSkeletonService_getSkeletonData_result__isset __isset;

  void __set_success(const SkeletonData& val);

  void __set_timeout(const TimedOutException& val);

  bool operator == (const LiveSkeletonService_getSkeletonData_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(timeout == rhs.timeout))
      return false;
    return true;
  }
  bool operator != (const LiveSkeletonService_getSkeletonData_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getSkeletonData_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getSkeletonData_presult__isset {
  _LiveSkeletonService_getSkeletonData_presult__isset() : success(false), timeout(false) {}
  bool success :1;
  bool timeout :1;
} _LiveSkeletonService_getSkeletonData_presult__isset;

class LiveSkeletonService_getSkeletonData_presult {
 public:


  virtual ~LiveSkeletonService_getSkeletonData_presult() throw();
  SkeletonData* success;
  TimedOutException timeout;

  _LiveSkeletonService_getSkeletonData_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class LiveSkeletonService_getDoLoopEstimation_args {
 public:

  LiveSkeletonService_getDoLoopEstimation_args(const LiveSkeletonService_getDoLoopEstimation_args&);
  LiveSkeletonService_getDoLoopEstimation_args& operator=(const LiveSkeletonService_getDoLoopEstimation_args&);
  LiveSkeletonService_getDoLoopEstimation_args() {
  }

  virtual ~LiveSkeletonService_getDoLoopEstimation_args() throw();

  bool operator == (const LiveSkeletonService_getDoLoopEstimation_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const LiveSkeletonService_getDoLoopEstimation_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getDoLoopEstimation_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_getDoLoopEstimation_pargs {
 public:


  virtual ~LiveSkeletonService_getDoLoopEstimation_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getDoLoopEstimation_result__isset {
  _LiveSkeletonService_getDoLoopEstimation_result__isset() : success(false) {}
  bool success :1;
} _LiveSkeletonService_getDoLoopEstimation_result__isset;

class LiveSkeletonService_getDoLoopEstimation_result {
 public:

  LiveSkeletonService_getDoLoopEstimation_result(const LiveSkeletonService_getDoLoopEstimation_result&);
  LiveSkeletonService_getDoLoopEstimation_result& operator=(const LiveSkeletonService_getDoLoopEstimation_result&);
  LiveSkeletonService_getDoLoopEstimation_result() : success(0) {
  }

  virtual ~LiveSkeletonService_getDoLoopEstimation_result() throw();
  bool success;

  _LiveSkeletonService_getDoLoopEstimation_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const LiveSkeletonService_getDoLoopEstimation_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const LiveSkeletonService_getDoLoopEstimation_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_getDoLoopEstimation_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _LiveSkeletonService_getDoLoopEstimation_presult__isset {
  _LiveSkeletonService_getDoLoopEstimation_presult__isset() : success(false) {}
  bool success :1;
} _LiveSkeletonService_getDoLoopEstimation_presult__isset;

class LiveSkeletonService_getDoLoopEstimation_presult {
 public:


  virtual ~LiveSkeletonService_getDoLoopEstimation_presult() throw();
  bool* success;

  _LiveSkeletonService_getDoLoopEstimation_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _LiveSkeletonService_setDoLoopEstimation_args__isset {
  _LiveSkeletonService_setDoLoopEstimation_args__isset() : state(false) {}
  bool state :1;
} _LiveSkeletonService_setDoLoopEstimation_args__isset;

class LiveSkeletonService_setDoLoopEstimation_args {
 public:

  LiveSkeletonService_setDoLoopEstimation_args(const LiveSkeletonService_setDoLoopEstimation_args&);
  LiveSkeletonService_setDoLoopEstimation_args& operator=(const LiveSkeletonService_setDoLoopEstimation_args&);
  LiveSkeletonService_setDoLoopEstimation_args() : state(0) {
  }

  virtual ~LiveSkeletonService_setDoLoopEstimation_args() throw();
  bool state;

  _LiveSkeletonService_setDoLoopEstimation_args__isset __isset;

  void __set_state(const bool val);

  bool operator == (const LiveSkeletonService_setDoLoopEstimation_args & rhs) const
  {
    if (!(state == rhs.state))
      return false;
    return true;
  }
  bool operator != (const LiveSkeletonService_setDoLoopEstimation_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LiveSkeletonService_setDoLoopEstimation_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class LiveSkeletonService_setDoLoopEstimation_pargs {
 public:


  virtual ~LiveSkeletonService_setDoLoopEstimation_pargs() throw();
  const bool* state;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class LiveSkeletonServiceClient : virtual public LiveSkeletonServiceIf {
 public:
  LiveSkeletonServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  LiveSkeletonServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void ping();
  void send_ping();
  void recv_ping();
  void getServerVersion(std::string& _return);
  void send_getServerVersion();
  void recv_getServerVersion(std::string& _return);
  ServerStatus::type getServerStatus();
  void send_getServerStatus();
  ServerStatus::type recv_getServerStatus();
  void setServerStatus(const ServerStatus::type status);
  void send_setServerStatus(const ServerStatus::type status);
  void stopServer();
  void send_stopServer();
  void shutdown();
  void send_shutdown();
  void getSkeletonDefaultPose(SkeletonData& _return);
  void send_getSkeletonDefaultPose();
  void recv_getSkeletonDefaultPose(SkeletonData& _return);
  void setSkeletonDefaultPose(const SkeletonData& data);
  void send_setSkeletonDefaultPose(const SkeletonData& data);
  void setSkeletonData(const SkeletonData& data);
  void send_setSkeletonData(const SkeletonData& data);
  void getSkeletonData(SkeletonData& _return);
  void send_getSkeletonData();
  void recv_getSkeletonData(SkeletonData& _return);
  bool getDoLoopEstimation();
  void send_getDoLoopEstimation();
  bool recv_getDoLoopEstimation();
  void setDoLoopEstimation(const bool state);
  void send_setDoLoopEstimation(const bool state);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class LiveSkeletonServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<LiveSkeletonServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (LiveSkeletonServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getServerVersion(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getServerStatus(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_setServerStatus(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_stopServer(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_shutdown(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getSkeletonDefaultPose(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_setSkeletonDefaultPose(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_setSkeletonData(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getSkeletonData(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getDoLoopEstimation(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_setDoLoopEstimation(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  LiveSkeletonServiceProcessor(boost::shared_ptr<LiveSkeletonServiceIf> iface) :
    iface_(iface) {
    processMap_["ping"] = &LiveSkeletonServiceProcessor::process_ping;
    processMap_["getServerVersion"] = &LiveSkeletonServiceProcessor::process_getServerVersion;
    processMap_["getServerStatus"] = &LiveSkeletonServiceProcessor::process_getServerStatus;
    processMap_["setServerStatus"] = &LiveSkeletonServiceProcessor::process_setServerStatus;
    processMap_["stopServer"] = &LiveSkeletonServiceProcessor::process_stopServer;
    processMap_["shutdown"] = &LiveSkeletonServiceProcessor::process_shutdown;
    processMap_["getSkeletonDefaultPose"] = &LiveSkeletonServiceProcessor::process_getSkeletonDefaultPose;
    processMap_["setSkeletonDefaultPose"] = &LiveSkeletonServiceProcessor::process_setSkeletonDefaultPose;
    processMap_["setSkeletonData"] = &LiveSkeletonServiceProcessor::process_setSkeletonData;
    processMap_["getSkeletonData"] = &LiveSkeletonServiceProcessor::process_getSkeletonData;
    processMap_["getDoLoopEstimation"] = &LiveSkeletonServiceProcessor::process_getDoLoopEstimation;
    processMap_["setDoLoopEstimation"] = &LiveSkeletonServiceProcessor::process_setDoLoopEstimation;
  }

  virtual ~LiveSkeletonServiceProcessor() {}
};

class LiveSkeletonServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  LiveSkeletonServiceProcessorFactory(const ::boost::shared_ptr< LiveSkeletonServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< LiveSkeletonServiceIfFactory > handlerFactory_;
};

class LiveSkeletonServiceMultiface : virtual public LiveSkeletonServiceIf {
 public:
  LiveSkeletonServiceMultiface(std::vector<boost::shared_ptr<LiveSkeletonServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~LiveSkeletonServiceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<LiveSkeletonServiceIf> > ifaces_;
  LiveSkeletonServiceMultiface() {}
  void add(boost::shared_ptr<LiveSkeletonServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void ping() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ping();
    }
    ifaces_[i]->ping();
  }

  void getServerVersion(std::string& _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getServerVersion(_return);
    }
    ifaces_[i]->getServerVersion(_return);
    return;
  }

  ServerStatus::type getServerStatus() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getServerStatus();
    }
    return ifaces_[i]->getServerStatus();
  }

  void setServerStatus(const ServerStatus::type status) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->setServerStatus(status);
    }
    ifaces_[i]->setServerStatus(status);
  }

  void stopServer() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->stopServer();
    }
    ifaces_[i]->stopServer();
  }

  void shutdown() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->shutdown();
    }
    ifaces_[i]->shutdown();
  }

  void getSkeletonDefaultPose(SkeletonData& _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getSkeletonDefaultPose(_return);
    }
    ifaces_[i]->getSkeletonDefaultPose(_return);
    return;
  }

  void setSkeletonDefaultPose(const SkeletonData& data) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->setSkeletonDefaultPose(data);
    }
    ifaces_[i]->setSkeletonDefaultPose(data);
  }

  void setSkeletonData(const SkeletonData& data) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->setSkeletonData(data);
    }
    ifaces_[i]->setSkeletonData(data);
  }

  void getSkeletonData(SkeletonData& _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getSkeletonData(_return);
    }
    ifaces_[i]->getSkeletonData(_return);
    return;
  }

  bool getDoLoopEstimation() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getDoLoopEstimation();
    }
    return ifaces_[i]->getDoLoopEstimation();
  }

  void setDoLoopEstimation(const bool state) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->setDoLoopEstimation(state);
    }
    ifaces_[i]->setDoLoopEstimation(state);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class LiveSkeletonServiceConcurrentClient : virtual public LiveSkeletonServiceIf {
 public:
  LiveSkeletonServiceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  LiveSkeletonServiceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void ping();
  int32_t send_ping();
  void recv_ping(const int32_t seqid);
  void getServerVersion(std::string& _return);
  int32_t send_getServerVersion();
  void recv_getServerVersion(std::string& _return, const int32_t seqid);
  ServerStatus::type getServerStatus();
  int32_t send_getServerStatus();
  ServerStatus::type recv_getServerStatus(const int32_t seqid);
  void setServerStatus(const ServerStatus::type status);
  void send_setServerStatus(const ServerStatus::type status);
  void stopServer();
  void send_stopServer();
  void shutdown();
  void send_shutdown();
  void getSkeletonDefaultPose(SkeletonData& _return);
  int32_t send_getSkeletonDefaultPose();
  void recv_getSkeletonDefaultPose(SkeletonData& _return, const int32_t seqid);
  void setSkeletonDefaultPose(const SkeletonData& data);
  void send_setSkeletonDefaultPose(const SkeletonData& data);
  void setSkeletonData(const SkeletonData& data);
  void send_setSkeletonData(const SkeletonData& data);
  void getSkeletonData(SkeletonData& _return);
  int32_t send_getSkeletonData();
  void recv_getSkeletonData(SkeletonData& _return, const int32_t seqid);
  bool getDoLoopEstimation();
  int32_t send_getDoLoopEstimation();
  bool recv_getDoLoopEstimation(const int32_t seqid);
  void setDoLoopEstimation(const bool state);
  void send_setDoLoopEstimation(const bool state);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif

} // namespace

#endif
