namespace cpp LiveSkeletonTransfer
namespace py LiveSkeletonTransfer

typedef double TimeStamp  # Which format should this be? Convert in Class method?
typedef string FilePath

enum ServerStatus {
  STOPPED = 0
  NOT_STARTED = 1
  INITIALIZED = 2
  DEFAULT_SET = 3
  CONNECTED = 4
  FITTING_INITIAL_POSE = 5
  ESTIMATING = 6
}

enum JointType {
  ROOT = 1,
  JOINT = 2,
  ENDSITE = 3
}

struct Joint {
  1: string name,
  2: optional string parent,
  3: JointType type,
  4: optional list<double> rot,
  5: optional list<double> pos,
}

struct SkeletonData {
  1: optional list<Joint> joints,  # or map<string,Joint> joints?
  2: TimeStamp timestamp,
  3: i32 frame,
}

exception InvalidOperation {
  1: i32 whatOp
  2: string why
}

exception TimedOutException {
}

service LiveSkeletonService {
  void ping(),

  string getServerVersion(),
  
  ServerStatus getServerStatus(),
  
  oneway void setServerStatus(1: ServerStatus status),

  oneway void stopServer(),

  oneway void shutdown(),

  SkeletonData getSkeletonDefaultPose(),

  oneway void setSkeletonDefaultPose(1: SkeletonData data),

  oneway void setSkeletonData(1: SkeletonData data),

  SkeletonData getSkeletonData() throws (1: TimedOutException timeout),

  bool getDoLoopEstimation(),

  oneway void setDoLoopEstimation(1: bool state)

}
