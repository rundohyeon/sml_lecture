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
        # self.set_param('linear_port', "/dev/ttyUSB0")
        # self.set_param('linear_baudrate', 9600)
        # self.set_param('joint_names', ["joint0", "joint1", "joint2", "joint3", "joint4", "joint5", "joint6"])

        # self.set_param('linear.pos.home', 0)
        # self.set_param('linear.pos.basket', 300)
        # self.set_param('linear.pos.conveyor', 600)

        # self.set_param('workspace/x', [-0.90, -0.7])
        # self.set_param('workspace/y', [-0.4, 0.05])
        # self.set_param('workspace/z', [-0.05, 0.15])

        self.declare_parameter('posj.home', [90.0, -25.0, 0.0, 115.0, 0.0, 90.0, 0.0]) # heading to lazer

        # self.set_param('offset.approach_to_target', [0.05, -0.03, 0.155])


        # self.add_async_timer(1, self.vis_workspace)

        self.workspace_pub = self.create_publisher(MarkerArray, 'workspace_marker', 1)

        self.indy = IndyDCP3(self.get_parameter('indy_ip').get_parameter_value().string_value)
        # self.linear = LinearRobotManager(self.param['linear_port'], self.param['linear_baudrate'])

        self.rosTF = ROS2TF(node=self)


        ## if functions can be run in parallel, use this group
        # self._parallel_callback_group = rclpy.callback_groups.ReentrantCallbackGroup()
        ## if functions must be run in sequence, use this group
        # self._sequential_callback_group = rclpy.callback_groups.MutuallyExclusiveCallbackGroup()

        # publishers
        # self._status_publisher = self.create_publisher(Int32, f'{node_name}/status', 1)

        # subscribers
        self._command_subscriber = self.create_subscription(String,
                                                           'indyrp2_node/command',
                                                           self._command_callback, 10)


        # self.approach_to_target()
        # self.move_linear_from_tcp([0.01, 0.0, 0.0])
        # time.sleep(3)
        # print("linear move home", self.linear.inpos)
        # self.linear_move_abs(self.param['linear.pos.home'])
        # print("linear move 100", self.linear.inpos)
        # time.sleep(5)
        # self.linear_move_abs(0)
        # self.linear_move_abs(200)
        # self.linear_move_abs(300)
        # self.linear_move_abs(400)
        # self.linear_move_abs(500)
        # print("linear move conveyor", self.linear.inpos)
        # self.linear_move_abs(self.param['linear.pos.conveyor'])
        # print("linear move home", self.linear.inpos)
        # self.linear_move_abs(self.param['linear.pos.home'])



        # self.move_linear_from_tcp(trans_in_meter=[0.0, 0.0, 0.0], rot_in_quat=[0.0, 0.0, 0.0, 1.0])


    def vis_workspace(self):
        m_array = MarkerArray()

        # 왼쪽 workspace marker
        left_marker = Marker()
        left_marker.header.frame_id = self.param['base_frame_id']
        left_marker.header.stamp = self.get_clock().now().to_msg()
        left_marker.ns = "workspace"
        left_marker.id = 0
        left_marker.type = Marker.CUBE
        left_marker.action = Marker.ADD
        left_marker.pose.position.x = (self.param['workspace/x'][0] + self.param['workspace/x'][1]) / 2
        left_marker.pose.position.y = (self.param['workspace/y'][0] + self.param['workspace/y'][1]) / 2
        left_marker.pose.position.z = (self.param['workspace/z'][0] + self.param['workspace/z'][1]) / 2
        left_marker.pose.orientation.x = 0.0
        left_marker.pose.orientation.y = 0.0
        left_marker.pose.orientation.z = 0.0
        left_marker.pose.orientation.w = 1.0
        left_marker.scale.x = self.param['workspace/x'][1] - self.param['workspace/x'][0]
        left_marker.scale.y = self.param['workspace/y'][1] - self.param['workspace/y'][0]
        left_marker.scale.z = self.param['workspace/z'][1] - self.param['workspace/z'][0]
        left_marker.color.a = 0.3
        left_marker.color.r = 0.0
        left_marker.color.g = 1.0
        left_marker.color.b = 0.0

        # 오른쪽 workspace marker (y값만 반전)
        right_marker = Marker()
        right_marker.header.frame_id = "base_link"
        right_marker.header.stamp = self.get_clock().now().to_msg()
        right_marker.ns = "workspace"
        right_marker.id = 1
        right_marker.type = Marker.CUBE
        right_marker.action = Marker.ADD
        right_marker.pose.position.x = (self.param['workspace/x'][0] + self.param['workspace/x'][1]) / 2
        right_marker.pose.position.y = -(self.param['workspace/y'][0] + self.param['workspace/y'][1]) / 2  # y 위치 반전
        right_marker.pose.position.z = (self.param['workspace/z'][0] + self.param['workspace/z'][1]) / 2
        right_marker.pose.orientation.x = 0.0
        right_marker.pose.orientation.y = 0.0
        right_marker.pose.orientation.z = 0.0
        right_marker.pose.orientation.w = 1.0
        right_marker.scale.x = self.param['workspace/x'][1] - self.param['workspace/x'][0]
        right_marker.scale.y = self.param['workspace/y'][1] - self.param['workspace/y'][0]
        right_marker.scale.z = self.param['workspace/z'][1] - self.param['workspace/z'][0]
        right_marker.color.a = 0.3
        right_marker.color.r = 0.0
        right_marker.color.g = 1.0
        right_marker.color.b = 0.0

        m_array.markers.extend([left_marker, right_marker])
        self.workspace_pub.publish(m_array)


    def _command_callback(self, msg):
        # try:
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

        # except json.JSONDecodeError as e:
        #     self.get_logger().error(f"Failed to parse JSON: {e}")
        # except Exception as e:
        #     self.get_logger().error(f"Error handling message: {e}")










    def init_robot(self):
        self.move_joints(self.get_parameter('posj.home').get_parameter_value().double_array_value, 'abs')
        
        # self.linear.moveHome()
        self.wait_robot_move()


    # def linear_move_abs(self, pos_mm):
    #     self.linear.add_queue(self.linear.moveAbs, int(pos_mm))
    #     time.sleep(0.5)
    #     while abs(float(self.linear.loc) - float(pos_mm)) > 1.0:
    #         time.sleep(0.1)
    #     time.sleep(0.5)




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

    # def check_workspace(self, target_id):
    #     trans, _ = self.rosTF.getTF('link0', 'target')
    #     if trans[0] < self.param['workspace/x'][0] or trans[0] > self.param['workspace/x'][1]:
    #         return False
    #     if trans[1] < self.param['workspace/y'][0] or trans[1] > self.param['workspace/y'][1]:
    #         return False
    #     if trans[2] < self.param['workspace/z'][0] or trans[2] > self.param['workspace/z'][1]:
    #         return False
    #     return True

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


    # def search_conveyor(self, arg_json={}):
    #     self.linear_move_abs(self.param['linear.pos.conveyor'])
    #     self.move_joints(self.param['posj.search.conveyor'])
    #     timeout = 5.0

    #     start_time = time.time()
    #     trans = []
    #     while time.time() - start_time < timeout:
    #         trans, _ = self.rosTF.getTF('tcp', 'target')
    #         if len(trans) > 0:
    #             break
    #         self.get_logger().info('Searching conveyor...')
    #         time.sleep(0.1)
    #     time.sleep(3.0)

    #     self.set_status(BehaviorTreeStatus.TASK_STATUS_SUCCESS)


    # def approach_to_target(self, arg_json={}):
    #     target_id = 'target' # arg_json['target_id']
    #     trans, rot = self.rosTF.getTF('link0', 'target')

    #     trans_offset = [trans[0] + self.param['offset.approach_to_target'][0],
    #              trans[1] + self.param['offset.approach_to_target'][1],
    #              self.param['conveyor.absolute.height']]
    #     print(trans_offset)
    #     if self.check_workspace('target'):
    #         print('Target is in workspace')
    #         self.move_linear_from_base(trans_offset)
    #     else:
    #         print('Target is out of workspace')


    # def bring_target_to_basket(self, arg_json={}):
    #     self.move_joints(self.param['posj.search.conveyor'])
    #     self.move_joints(self.param['posj.home'])
    #     self.linear_move_abs(self.param['linear.pos.basket'])
    #     self.move_joints(self.param['posj.basket'])
    #     self.set_status(BehaviorTreeStatus.TASK_STATUS_SUCCESS)


    def return_to_safe_config(self, arg_json={}):
        self.move_joints(self.param['posj.home'])
        self.set_status(BehaviorTreeStatus.TASK_STATUS_SUCCESS)



    def indy_service(self, data):
        self.indy_req.data = data
        self.future = self.cli.call_async(self.indy_req)
        while not self.future.done():
            time.sleep(0.01)
        try:
            response = self.future.result()
        except Exception as e:
            self.get_logger().error('Service call failed %r' % (e,))
        return response



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