import sys
import argparse
import os
import threading
import time
import six

from transforms3d.euler import euler2mat, mat2euler, euler2quat, quat2euler
import numpy as np

from bvhplayer_skeleton import process_bvhfile, process_bvhkeyframe

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

sys.path.append('gen-py')
from LiveSkeletonTransfer import LiveSkeletonService
from LiveSkeletonTransfer.ttypes import *
from LiveSkeletonTransfer.constants import *


class LiveSkeletonHandler:
    def __init__(self):
        self.default_pose = None
        self.sendBuffer = None
        self.sendLock = threading.RLock()
        self.server_status = ServerStatus.NOT_STARTED
        self.do_loop = True
    
    def ping(self):
        print('Received ping.')
    
    def getServerVersion(self):
        return 'Script Ver. DummyServer'
    
    def getServerStatus(self):
        return self.server_status
    
    def setServerStatus(self, status):
        self.server_status = status
    
    def stopServer(self):
        self.shutdown()
    
    def shutdown(self):
        quit()
    
    def getSkeletonData(self):
        self.sendLock.acquire()
        data = self.sendBuffer
        self.sendLock.release()
        return data
    
    def setSkeletonData(self, data):
        self.sendLock.acquire()
        self.sendBuffer = data
        self.sendLock.release()
    
    def getSkeletonDefaultPose(self):
        return self.default_pose
    
    def setSkeletonDefaultPose(self, data):
        self.default_pose = data
    
    def getDoLoopEstimation(self):
        return self.do_loop
    
    def setDoLoopEstimation(self, state):
        self.do_loop = state


class LiveSkeletonSimulation(object):
    def __init__(self, bvh_file, target_fps=24):
        self._skeleton = process_bvhfile(bvh_file, DEBUG=0)

        print("Analyzing frames...")
        # Fill skeleton's joints with frame data for rotation and world position.
        for i in range(self._skeleton.frames):
            process_bvhkeyframe(self._skeleton.keyframes[i], self._skeleton.root, self._skeleton.dt * i, DEBUG=0)
        print("done")
        self.skeleton_dict = self._skeleton.as_dict()
        self._joints = dict()
        self._fps = target_fps
        if not self._fps:
            self._sleep_time = self._skeleton.dt
        else:
            self._sleep_time = 1.0/self._fps
        self.frame = 0
        self.get_default_pose()
        # Simulate some getting ready time for testing the plugin.
        print("Ready in...")
        sleep_t = 3
        for i in range(sleep_t):
            if i > 1:
                unit = "second"
            else:
                unit = "seconds"
            print(sleep_t - i, unit)
            time.sleep(1)
    
    def get_joints(self):
        return self._joints
    
    def get_joints_data(self, in_worldspace=False, default=False):
        """
        :param in_worldspace: Whether to get the position in worldspace.
        :type in_worldspace: bool
        :param default: Whether to get the default positions of the joints or current frame.
        :type default: bool
        :return: A dictionary of joint_label: (parent_label, position, rotation, joint type, children).
        :rtype: dict
        """
        if default:
            joint_trans = self._skeleton.get_frame(0)
        else:
            joint_trans = self._skeleton.get_frame(self.frame)
        joint_dict = dict()
        
        def get_pos(joint_name, is_worldspace):
            if self.skeleton_dict[joint_name][3] == 'root':  # Make sure root is always set to worldpos.
                return joint_trans[joint_name][1]
            if is_worldspace:
                return joint_trans[joint_name][1]
            else:
                return self._skeleton.get_offsets()[joint_name]
        
        def get_rot_ordered(rot, order='sxyz'):
            if order[1:] == 'zyx':
                return rot[2], rot[1], rot[0]
            elif order[1:] == 'zxy':
                return rot[2], rot[0], rot[1]
            elif order[1:] == 'yxz':
                return rot[1], rot[0], rot[2]
            elif order[1:] == 'xzy':
                return rot[0], rot[2], rot[1]
            elif order[1:] == 'yzx':
                return rot[1], rot[2], rot[0]
            else:
                return rot[0], rot[1], rot[2]
        
        def get_xyz_rot(rot, order='sxyz'):
            if order[1:] == 'zyx':
                return rot[2], rot[1], rot[0]
            elif order[1:] == 'zxy':
                return rot[1], rot[2], rot[0]
            elif order[1:] == 'yxz':
                return rot[1], rot[0], rot[2]
            elif order[1:] == 'xzy':
                return rot[0], rot[2], rot[1]
            elif order[1:] == 'yzx':
                return rot[2], rot[0], rot[1]
            else:
                return rot[0], rot[1], rot[2]
                
        for joint, data in six.iteritems(self.skeleton_dict):
            rot = joint_trans[joint][0]
            if rot is not None:
                # This is for testing different joint rotation orders.
                in_order = 'syxz'
                out_order = 'sxyz'
                rot = np.deg2rad(rot)
                m = euler2mat(*get_rot_ordered(rot, in_order), axes=in_order)
                rot = np.rad2deg(mat2euler(m, axes=out_order))
                rot = get_xyz_rot(rot, out_order)
            joint_dict[joint] = (data[0], get_pos(joint, in_worldspace), rot, data[3], data[4])
        return joint_dict
        
    def get_default_pose(self):
        """
        :return: A dictionary of joint_label: (parent_label, position, rotation, joint type, children).
        :rtype: dict
        """
        joint_dict = self.get_joints_data(default=True)
        self._joints = joint_dict  # Have at least one set of data, if no new data comes in by advance_next_frame?
        return joint_dict

    def advance_next_frame(self, in_worldspace=False):
        """
        Sets joint data at a certain speed.
        :param in_worldspace: Fill joint positions with worldspace coordinates or offsets.
        :type in_worldspace: bool
        :return Whether or not there are still frames to process.
        :rtype: bool
        """
        if self.frame >= self._skeleton.frames:
            return False
        else:
            time.sleep(self._sleep_time)
            #print(joint_data)  # Debug print
            self._joints = self.get_joints_data(in_worldspace)
            self.frame += 1
            return True
    

class SimulationThriftWrapper(object):
    """ Handles interaction between thrift handler and LiveSkeletonSimulation.
    """
    
    def __init__(self, thrift_handler, default_pose_func, process_pose_func, get_joints_func, **kwargs):
        self._handler = thrift_handler
        self._get_default_pose = default_pose_func
        self._process_pose = process_pose_func
        self._get_joints = get_joints_func
        if not kwargs:
            self._kwargs = dict()
        else:
            self._kwargs = kwargs
    
    def get_thrift_joints(self, joint_dict):
        """
        Convert joints from dictionary to format for cross language thrift messaging.
        :param joint_dict: {joint_label: (parent_label, position, rotation, joint type, children)}
        :type joint_dict: dict
        :return: List of LiveSkeletonService.Joint data types.
        :rtype: list
        """
        joints = list()
        for joint_name, data in six.iteritems(joint_dict):  # Will this have the same order even if dict is unordered?
            parent = data[0] if data[0] is not None else ""
            j_type = data[3]
            if j_type == 'root':
                j_type = LiveSkeletonService.JointType.ROOT
            elif j_type == 'end':
                j_type = LiveSkeletonService.JointType.ENDSITE
            else:
                j_type = LiveSkeletonService.JointType.JOINT
            pos = list(data[1]) if data[1] is not None else [0.0, 0.0, 0.0]
            rot = list(data[2]) if data[2] is not None else [0.0, 0.0, 0.0]
            joint = LiveSkeletonService.Joint(name=joint_name, parent=parent, pos=pos, rot=rot, type=j_type)
            joints.append(joint)
        return joints

    def set_default_pose(self):
        """
        Create default SkeletonData/pose with dummy time 0.0 and frame -1.
        :return: Whether setting default pose was successful or not.
        :rtype: bool
        """
        print("Setting up default pose on server.")
        thrift_joints = self.get_thrift_joints(self._get_joints())
        default_pose = LiveSkeletonService.SkeletonData(thrift_joints, 0.0, -1)
        self._handler.setSkeletonDefaultPose(default_pose)
        self._handler.setSkeletonData(default_pose)  # Have at least 1 pose on server, even if there's no further data.

        print("SkeletonJoints on server:")
        for i, joint in enumerate(default_pose.joints):
            print("{0}: {1}, pos: {2} rot: {3}".format(i, joint.name, joint.pos, joint.rot))
        if default_pose.joints:
            return True
        else:
            print("ERROR: No default joints found!")
            return False
    
    def start_simulation(self):
        print("Starting the simulation...")
        frame = 0
        start_time = time.clock()
        self._handler.setServerStatus(ServerStatus.ESTIMATING)
        try:
            while self._handler.getDoLoopEstimation():
                if not self._process_pose(**(self._kwargs)):
                    break
                timestamp = time.clock()
                thrift_joints = self.get_thrift_joints(self._get_joints())
                data = LiveSkeletonService.SkeletonData(thrift_joints, timestamp, frame)
                self._handler.setSkeletonData(data)
                frame += 1
        
        except KeyboardInterrupt:
            print("Quitting from keyboard interrupt.")
        
        except SystemExit:
            print("Quitting from shutdown call.")
            
            # except Exception, e:
            #    logging.exception(e)
        
        finally:
            print("Simulation was running for {:.2f} minutes.".format((time.clock() - start_time) / 60.0))
            print("Shutting down server")
            self._handler.setServerStatus(ServerStatus.STOPPED)
    

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Provides a thrift server with animation from a BVH file.")
    parser.add_argument("-w", "--worldspace", action='store_true', help="Provide position data in worldspace.")
    parser.add_argument("-p", "--port", type=int, default=9090, help="out port for relaying joint angles")
    parser.add_argument("--fps", type=int, default=0, help="target fps for playback. Default 0: get from bvh file.")
    parser.add_argument("filename", type=str, help="BVH motion file to play.")
    args = parser.parse_args()
    file_in = args.filename
    if not os.path.exists(file_in):
        print("Error: file {} not found.".format(file_in))
        sys.exit(1)
    fps = args.fps

    ### Network Thrift Server ###
    thrift_host = '127.0.0.1'
    out_port = args.port
    handler = LiveSkeletonHandler()
    processor = LiveSkeletonService.Processor(handler)
    transport = TSocket.TServerSocket(thrift_host, out_port)  # Pass host in case we're not connected to a network.
    tfactory = TTransport.TFramedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()
    server = TServer.TThreadedServer(processor, transport, tfactory, pfactory, daemon=True)
    
    # Start a thread with the server -- that thread will then start one
    # more thread for each request
    server_thread = threading.Thread(target=server.serve)
    # Exit the server thread when the main thread terminates
    server_thread.name = 'LiveSkeletonServerThread'
    server_thread.daemon = True
    server_thread.start()
    print("Server loop running on port {} in thread: {}".format(out_port, server_thread.name))
    sys.stdout.flush()

    ### Simulation ###
    skeleton_simulator = LiveSkeletonSimulation(bvh_file=file_in, target_fps=fps)
    wrapper = SimulationThriftWrapper(thrift_handler=handler,
                                      default_pose_func=skeleton_simulator.get_default_pose,
                                      process_pose_func=skeleton_simulator.advance_next_frame,
                                      get_joints_func=skeleton_simulator.get_joints,
                                      in_worldspace=args.worldspace)
    try:
        if wrapper.set_default_pose():
            handler.setServerStatus(LiveSkeletonService.ServerStatus.DEFAULT_SET)
            handler.setServerStatus(LiveSkeletonService.ServerStatus.ESTIMATING)
            wrapper.start_simulation()
    finally:
        handler.setDoLoopEstimation(False)
        handler.setServerStatus(LiveSkeletonService.ServerStatus.STOPPED)
        print("Shutting down thread {}...".format(server_thread.name))
        server_thread.join(1)  # FixMe: join isn't doing anything, because server serves forever, not breaking the loop?
        transport.close()
        print('done.')
