/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "LiveSkeleton_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace LiveSkeletonTransfer {

int _kServerStatusValues[] = {
  ServerStatus::STOPPED,
  ServerStatus::NOT_STARTED,
  ServerStatus::INITIALIZED,
  ServerStatus::DEFAULT_SET,
  ServerStatus::CONNECTED,
  ServerStatus::FITTING_INITIAL_POSE,
  ServerStatus::ESTIMATING
};
const char* _kServerStatusNames[] = {
  "STOPPED",
  "NOT_STARTED",
  "INITIALIZED",
  "DEFAULT_SET",
  "CONNECTED",
  "FITTING_INITIAL_POSE",
  "ESTIMATING"
};
const std::map<int, const char*> _ServerStatus_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(7, _kServerStatusValues, _kServerStatusNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

int _kJointTypeValues[] = {
  JointType::ROOT,
  JointType::JOINT,
  JointType::ENDSITE
};
const char* _kJointTypeNames[] = {
  "ROOT",
  "JOINT",
  "ENDSITE"
};
const std::map<int, const char*> _JointType_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(3, _kJointTypeValues, _kJointTypeNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));


Joint::~Joint() throw() {
}


void Joint::__set_name(const std::string& val) {
  this->name = val;
}

void Joint::__set_parent(const std::string& val) {
  this->parent = val;
__isset.parent = true;
}

void Joint::__set_type(const JointType::type val) {
  this->type = val;
}

void Joint::__set_rot(const std::vector<double> & val) {
  this->rot = val;
__isset.rot = true;
}

void Joint::__set_pos(const std::vector<double> & val) {
  this->pos = val;
__isset.pos = true;
}

uint32_t Joint::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->name);
          this->__isset.name = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->parent);
          this->__isset.parent = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast0;
          xfer += iprot->readI32(ecast0);
          this->type = (JointType::type)ecast0;
          this->__isset.type = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->rot.clear();
            uint32_t _size1;
            ::apache::thrift::protocol::TType _etype4;
            xfer += iprot->readListBegin(_etype4, _size1);
            this->rot.resize(_size1);
            uint32_t _i5;
            for (_i5 = 0; _i5 < _size1; ++_i5)
            {
              xfer += iprot->readDouble(this->rot[_i5]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.rot = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->pos.clear();
            uint32_t _size6;
            ::apache::thrift::protocol::TType _etype9;
            xfer += iprot->readListBegin(_etype9, _size6);
            this->pos.resize(_size6);
            uint32_t _i10;
            for (_i10 = 0; _i10 < _size6; ++_i10)
            {
              xfer += iprot->readDouble(this->pos[_i10]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.pos = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Joint::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Joint");

  xfer += oprot->writeFieldBegin("name", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->name);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.parent) {
    xfer += oprot->writeFieldBegin("parent", ::apache::thrift::protocol::T_STRING, 2);
    xfer += oprot->writeString(this->parent);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldBegin("type", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32((int32_t)this->type);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.rot) {
    xfer += oprot->writeFieldBegin("rot", ::apache::thrift::protocol::T_LIST, 4);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_DOUBLE, static_cast<uint32_t>(this->rot.size()));
      std::vector<double> ::const_iterator _iter11;
      for (_iter11 = this->rot.begin(); _iter11 != this->rot.end(); ++_iter11)
      {
        xfer += oprot->writeDouble((*_iter11));
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.pos) {
    xfer += oprot->writeFieldBegin("pos", ::apache::thrift::protocol::T_LIST, 5);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_DOUBLE, static_cast<uint32_t>(this->pos.size()));
      std::vector<double> ::const_iterator _iter12;
      for (_iter12 = this->pos.begin(); _iter12 != this->pos.end(); ++_iter12)
      {
        xfer += oprot->writeDouble((*_iter12));
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Joint &a, Joint &b) {
  using ::std::swap;
  swap(a.name, b.name);
  swap(a.parent, b.parent);
  swap(a.type, b.type);
  swap(a.rot, b.rot);
  swap(a.pos, b.pos);
  swap(a.__isset, b.__isset);
}

Joint::Joint(const Joint& other13) {
  name = other13.name;
  parent = other13.parent;
  type = other13.type;
  rot = other13.rot;
  pos = other13.pos;
  __isset = other13.__isset;
}
Joint& Joint::operator=(const Joint& other14) {
  name = other14.name;
  parent = other14.parent;
  type = other14.type;
  rot = other14.rot;
  pos = other14.pos;
  __isset = other14.__isset;
  return *this;
}
void Joint::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Joint(";
  out << "name=" << to_string(name);
  out << ", " << "parent="; (__isset.parent ? (out << to_string(parent)) : (out << "<null>"));
  out << ", " << "type=" << to_string(type);
  out << ", " << "rot="; (__isset.rot ? (out << to_string(rot)) : (out << "<null>"));
  out << ", " << "pos="; (__isset.pos ? (out << to_string(pos)) : (out << "<null>"));
  out << ")";
}


SkeletonData::~SkeletonData() throw() {
}


void SkeletonData::__set_joints(const std::vector<Joint> & val) {
  this->joints = val;
__isset.joints = true;
}

void SkeletonData::__set_timestamp(const TimeStamp val) {
  this->timestamp = val;
}

void SkeletonData::__set_frame(const int32_t val) {
  this->frame = val;
}

uint32_t SkeletonData::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->joints.clear();
            uint32_t _size15;
            ::apache::thrift::protocol::TType _etype18;
            xfer += iprot->readListBegin(_etype18, _size15);
            this->joints.resize(_size15);
            uint32_t _i19;
            for (_i19 = 0; _i19 < _size15; ++_i19)
            {
              xfer += this->joints[_i19].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.joints = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->timestamp);
          this->__isset.timestamp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->frame);
          this->__isset.frame = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t SkeletonData::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("SkeletonData");

  if (this->__isset.joints) {
    xfer += oprot->writeFieldBegin("joints", ::apache::thrift::protocol::T_LIST, 1);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->joints.size()));
      std::vector<Joint> ::const_iterator _iter20;
      for (_iter20 = this->joints.begin(); _iter20 != this->joints.end(); ++_iter20)
      {
        xfer += (*_iter20).write(oprot);
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldBegin("timestamp", ::apache::thrift::protocol::T_DOUBLE, 2);
  xfer += oprot->writeDouble(this->timestamp);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("frame", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->frame);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(SkeletonData &a, SkeletonData &b) {
  using ::std::swap;
  swap(a.joints, b.joints);
  swap(a.timestamp, b.timestamp);
  swap(a.frame, b.frame);
  swap(a.__isset, b.__isset);
}

SkeletonData::SkeletonData(const SkeletonData& other21) {
  joints = other21.joints;
  timestamp = other21.timestamp;
  frame = other21.frame;
  __isset = other21.__isset;
}
SkeletonData& SkeletonData::operator=(const SkeletonData& other22) {
  joints = other22.joints;
  timestamp = other22.timestamp;
  frame = other22.frame;
  __isset = other22.__isset;
  return *this;
}
void SkeletonData::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "SkeletonData(";
  out << "joints="; (__isset.joints ? (out << to_string(joints)) : (out << "<null>"));
  out << ", " << "timestamp=" << to_string(timestamp);
  out << ", " << "frame=" << to_string(frame);
  out << ")";
}


InvalidOperation::~InvalidOperation() throw() {
}


void InvalidOperation::__set_whatOp(const int32_t val) {
  this->whatOp = val;
}

void InvalidOperation::__set_why(const std::string& val) {
  this->why = val;
}

uint32_t InvalidOperation::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->whatOp);
          this->__isset.whatOp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->why);
          this->__isset.why = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t InvalidOperation::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("InvalidOperation");

  xfer += oprot->writeFieldBegin("whatOp", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->whatOp);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("why", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->why);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(InvalidOperation &a, InvalidOperation &b) {
  using ::std::swap;
  swap(a.whatOp, b.whatOp);
  swap(a.why, b.why);
  swap(a.__isset, b.__isset);
}

InvalidOperation::InvalidOperation(const InvalidOperation& other23) : TException() {
  whatOp = other23.whatOp;
  why = other23.why;
  __isset = other23.__isset;
}
InvalidOperation& InvalidOperation::operator=(const InvalidOperation& other24) {
  whatOp = other24.whatOp;
  why = other24.why;
  __isset = other24.__isset;
  return *this;
}
void InvalidOperation::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "InvalidOperation(";
  out << "whatOp=" << to_string(whatOp);
  out << ", " << "why=" << to_string(why);
  out << ")";
}

const char* InvalidOperation::what() const throw() {
  try {
    std::stringstream ss;
    ss << "TException - service has thrown: " << *this;
    this->thriftTExceptionMessageHolder_ = ss.str();
    return this->thriftTExceptionMessageHolder_.c_str();
  } catch (const std::exception&) {
    return "TException - service has thrown: InvalidOperation";
  }
}


TimedOutException::~TimedOutException() throw() {
}


uint32_t TimedOutException::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    xfer += iprot->skip(ftype);
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t TimedOutException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("TimedOutException");

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TimedOutException &a, TimedOutException &b) {
  using ::std::swap;
  (void) a;
  (void) b;
}

TimedOutException::TimedOutException(const TimedOutException& other25) : TException() {
  (void) other25;
}
TimedOutException& TimedOutException::operator=(const TimedOutException& other26) {
  (void) other26;
  return *this;
}
void TimedOutException::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "TimedOutException(";
  out << ")";
}

const char* TimedOutException::what() const throw() {
  try {
    std::stringstream ss;
    ss << "TException - service has thrown: " << *this;
    this->thriftTExceptionMessageHolder_ = ss.str();
    return this->thriftTExceptionMessageHolder_.c_str();
  } catch (const std::exception&) {
    return "TException - service has thrown: TimedOutException";
  }
}

} // namespace
