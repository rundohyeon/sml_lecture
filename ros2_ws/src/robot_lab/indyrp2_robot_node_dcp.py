#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped
from control_msgs.msg import JointJog
from std_srvs.srv import Trigger
from std_msgs.msg import String, Header, Int32, Float32MultiArray, ColorRGBA

import threading
import time
import json
import math
from scipy.spatial.transform import Rotation as R

from visualization_msgs.msg import Marker, MarkerArray

# from metalab.ros2_wrapper import BehaviorTreeServerNode
# from mtlab_msgs.msg import BehaviorTreeStatus
# from metalab.moveit2_interface import MoveIt2Interface
# from metalab.moveit2_servo  import MoveIt2Servo
# from metalab.linear_robot_driver import LinearRobotManager
from indy_interfaces.srv import IndyService
from indy_driver.indy_define import *
from tf import ROS2TF 
from tf2_ros import Buffer, TransformListener

from neuromeka import IndyDCP3, JointBaseType, TaskBaseType

# -----TELE STATUS-----
TELE_STOP   = 0
TELE_TASK   = 1
TELE_JOINT  = 2

DEG2RAD = math.pi / 180.0
RAD2DEG = 180.0 / math.pi
EPSILON = 0.0001



class IndyRP2Node(Node):
    def __init__(self):
        super().__init__('indyrp2_node')

        self.declare_parameter('indy_ip', "192.168.1.10")
        self.declare_parameter('posj.home', [90.0, -25.0, 0.0, 115.0, 0.0, 90.0, 0.0]) # heading to lazer

        self.workspace_pub = self.create_publisher(MarkerArray, 'workspace_marker', 1)

        self.indy = IndyDCP3(self.get_parameter('indy_ip').get_parameter_value().string_value)
        self.rosTF = ROS2TF(node=self)

        # publishers
        # self._status_publisher = self.create_publisher(Int32, f'{node_name}/status', 1)

        # subscribers
        self._command_subscriber = self.create_subscription(String,
                                                           'indyrp2_node/command',
                                                           self._command_callback, 10)



    def _command_callback(self, msg):
        try:
            command = json.loads(msg.data)
            print(f"Received command: {command}")

            # Access fields
            cmd = command.get("cmd")
            mode = command.get("mode")
            coord = command.get("coord")
            print(f"parsed result: {cmd}, {mode}, {coord}")


            if cmd =="initialize":
                self.init_robot()

            elif cmd == "movej":
                self.move_joints(coord, mode)

            elif cmd == "movel":
                # trans in meter, rot in quat
                if mode == 'base':
                    self.move_linear_from_base(coord[:3], coord[3:7])
                elif mode == 'tool':
                    self.move_linear_from_tcp(coord[:3], coord[3:7])
            else:
                print(f"Unknown command: {cmd}")

        except json.JSONDecodeError as e:
            self.get_logger().error(f"Failed to parse JSON: {e}")
        except Exception as e:
            self.get_logger().error(f"Error handling message: {e}")


    def init_robot(self):
        self.move_joints(self.get_parameter('posj.home').get_parameter_value().double_array_value, 'abs')
        self.wait_robot_move()


    def wait_robot_move(self):
        self.indy.wait_for_motion_state('is_target_reached')


    def move_joints(self, joints: list, absolute):
        '''
            [6,] float list in degree
            ex. [90.0, -25.0, 0.0, 115.0, 0.0, 90.0, 0.0]
        '''
        if absolute == 'abs':
            self.indy.movej(joints)
        elif absolute == 'rel':
            self.indy.movej(jtarget=joints, base_type=JointBaseType.RELATIVE)
        self.wait_robot_move()


    def move_linear_from_base(self, trans_in_meter, rot_in_quat=None, from_base=True):
        '''
            [3,] float list in meter
            [4,] float list in quat
        '''

        pose = []
        pos_mm = [q * 1000.0 for q in trans_in_meter]
        if rot_in_quat is None:
            _, rot_in_quat = self.rosTF.getTF('link0', 'tcp')
            euler = R.from_quat(rot_in_quat).as_euler('xyz', degrees=True)
        else:
            euler = R.from_quat(rot_in_quat).as_euler('xyz', degrees=True)
        pose.extend(pos_mm)
        pose.extend(euler)
        if from_base:
            self.indy.movel(ttarget=pose)
        else:
            self.indy.movel(ttarget=pose, base_type=TaskBaseType.RELATIVE)
        self.wait_robot_move()


    def move_linear_from_tcp(self, trans_in_meter, rot_in_quat=[0,0,0,1]):
        '''
            [3,] float list in meter
            [4,] float list in quat
        '''
        pose = []
        pos_mm = [q * 1000.0 for q in trans_in_meter]
        euler = R.from_quat(rot_in_quat).as_euler('xyz', degrees=True)
        pose.extend(pos_mm)
        pose.extend(euler)
        self.indy.movel(ttarget=pose, base_type=TaskBaseType.TCP)
        self.wait_robot_move()


if __name__ == '__main__':
    rclpy.init()

    node = IndyRP2Node()
    try:
        rclpy.spin(node)   # keep the node alive
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()