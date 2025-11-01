import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy


import json
import math 
import time
import numpy as np

from std_msgs.msg import String
from sensor_msgs.msg import Image

import cv2
from cv_bridge import CvBridge

import transforms3d.euler as euler


DEG2RAD = math.pi / 180.0
RAD2DEG = 180.0 / math.pi


class robotNode(Node):
    def __init__(self):
        super().__init__('robot_node')
        self.publisher_ = self.create_publisher(String, 'indyrp2_node/command', 10)

        # ---- Parameters for RealSense topics (override via ROS params if needed) ----
        self.declare_parameter('color_topic', '/camera/camera/color/image_raw')
        self.declare_parameter('depth_topic', '/camera/camera/depth/image_rect_raw')  # optional

        color_topic = self.get_parameter('color_topic').get_parameter_value().string_value
        depth_topic = self.get_parameter('depth_topic').get_parameter_value().string_value


        # ---- QoS for sensor data ----
        sensor_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=5,
            durability=DurabilityPolicy.VOLATILE
        )

        # ---- CvBridge ----
        self.bridge = CvBridge()

        # ---- Subscribers ----
        self.color_sub = self.create_subscription(
            Image, color_topic, self._on_color, sensor_qos
        )
        self.depth_sub = self.create_subscription(
            Image, depth_topic, self._on_depth, sensor_qos
        )

        # ---- Latest frames (thread-safe enough for simple use) ----
        self.latest_color = None        # numpy array (H, W, 3) BGR
        self.latest_depth = None        # numpy array (H, W) in millimeters (uint16) or meters (float32)
        self.show_window = True   # turn off on headless machines
        self.robot_status = 'Idle'

    def _on_color(self, msg: Image):
        try:
            cv_img = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            self.latest_color = cv_img

            if self.show_window:
                cv2.imshow("RealSense Color", cv_img)
                # 1 ms wait lets HighGUI process window events
                # If 'q' pressed, shut down cleanly
                key = cv2.waitKey(1) & 0xFF
                if key == ord('q'):
                    cv2.imwrite('pos6.jpg', cv_img)
                    self.get_logger().info("Quit requested. Shutting down...")
                    rclpy.shutdown()

        except Exception as e:
            self.get_logger().error(f"Color image conversion failed: {e}")

    def _on_depth(self, msg: Image):
        try:
            # Use passthrough for depth to keep the native type (usually 16UC1)
            depth = self.bridge.imgmsg_to_cv2(msg, desired_encoding='passthrough')
            self.latest_depth = depth

            # Example: save the first depth frame as a PNG (keeps 16-bit)
            if not hasattr(self, '_saved_depth'):
                # For visualization you might normalize; here we keep raw
                # cv2.imwrite('depth_frame.png', depth)
                self._saved_depth = True
                self.get_logger().info(
                    f"Saved first depth frame: depth_frame.png  shape={depth.shape}, dtype={depth.dtype}"
                )
        except Exception as e:
            self.get_logger().error(f"Depth image conversion failed: {e}")

    def sendCommand(self, cmd, mode='', coord=[]):
        '''
            make a topic to send
            topic message type is String
            
        '''

        if cmd == 'movel':

            (w, x, y, z) = euler.euler2quat(coord[3]*DEG2RAD,coord[4]*DEG2RAD,coord[5]*DEG2RAD)   # (w, x, y, z)
            coord[3] = x
            coord[4] = y
            coord[5] = z
            coord.append(w)


        command = {
            "cmd": cmd,
            "mode": mode,
            "coord": coord
        }

        msg = String()
        msg.data = json.dumps(command)
        self.publisher_.publish(msg)
        
        print(f"Published: {msg}")
        time.sleep(3)


    def waitUntilExecuted(self):
        try:
            while True:
                if self.robot_status == 'Idle':
                    break
        except KeyboardInterrupt:
            print("keyboard interrupt")

        except Exception as e:
            print(f"An unexpected error occurred: {e}")

        finally:
            self.robot_status = 'running'


    def RobotTask(self):
        self.sendCommand("gripper", 'open')

        # # initialize
        # print("initialize")
        self.sendCommand('initialize')
        time.sleep(4)
        self.sendCommand("movej", 'abs', [-146.4, -42.58, -0.68, -109.37, 0.99, -28.09, -57.7])
        time.sleep(4)

        # move to battery origin pose
        self.sendCommand("movej", 'abs', [-152.36, -54.32, 0.63, -92.00, -0.91, -33.88, -61.12])

        # approach to battery
        self.sendCommand("movel", 'tool', [0.0, 0.0, 0.05, 0.0, 0.0, 0.0])

        # grasp
        self.sendCommand("gripper", 'close')

        # pick up battery
        self.sendCommand("movel", 'tool', [0.0, 0.0, -0.05, 0.0, 0.0, 0.0])

        # move to battery new pose
        self.sendCommand("movel", 'base_abs', [-0.489, -0.280, 0.0445, 180, 0, 90])

        # tilt gripper
        self.sendCommand("movel", 'tool', [0.0, 0.0, 0.0, -20.0, 0.0, 0.0])

        # # mount battery
        # adjust position 
        self.sendCommand("movel", 'tool', [0.0, -0.05, 0.0, 0.0, 0.0, 0.0])

        # # move down
        self.sendCommand("movel", 'base_rel', [0.0, 0.0, -0.0221, 0.0, 0.0, 0.0])

        # # release gripper
        self.sendCommand("gripper", 'open')

        # # move up
        self.sendCommand("movel", 'base_rel', [0.0, 0.0, 0.02, 0, 0, 0])

        # # close gripper
        self.sendCommand("gripper", 'close')

        # # move to spring side
        self.sendCommand("movel", 'tool', [0.0, -0.02, 0.0, 0.0, 0.0, 0.0])

        # press spring side
        self.sendCommand("movel", 'tool', [0.0, 0.0, 0.015, 0.0, 0.0, 0.0])
        self.sendCommand("movel", 'tool', [0.0, 0.0, -0.02, 0.0, 0.0, 0.0])

        # move to opposite side
        self.sendCommand("movel", 'tool', [0.0, 0.055, 0.0, 0.0, 0.0, 0.0])

        # move down 
        self.sendCommand("movel", 'tool', [0.0, 0.0, 0.02, 0.0, 0.0, 0.0])

        # insert 
        self.sendCommand("movel", 'tool', [0.0, -0.03, 0.0, 0.0, 0.0, 0.0])
        self.sendCommand("movel", 'tool', [0.0, -0.007, 0.015, 0.0, 0.0, 0.0])

        # move up 
        self.sendCommand("movel", 'base_rel', [0.0, 0.0, 0.025, 0, 0, 0])



        # # gripper control
        # self.sendCommand("gripper", 'close')
        # self.sendCommand("gripper", 'open')

        # # movej rel
        #self.sendCommand("movej", 'rel', [-90.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

        # # movej abs
        # print("move abs")
        # self.sendCommand("movej", 'abs', [-146.4, -42.58, -0.68, -109.37, 0.99, -28.09, -57.7])

        # # movel rel
        #self.sendCommand("movel", 'tool', [0.01, 0.0, 0.0, 0.0, 0.0, 0.0])

        # # movel abs
        # self.sendCommand("movel", 'base', [0.166, -0.460, 0.480, 0.0, 180.0, 90])


# 1 2 3 4 5
#  6  7  8
# 1 : (J) -133.26, -46.5, -0.69, -98.58. 0.87, -34.93, -44.45
#     (L) -493.64, -251.29, 92.96, 180.00, 0.0, 90.0
# 2 : (J) -138.88, -44.0, -0.79, -105.27, 1.08, -30.76, -50.34
#     (L) -493.64, -177.26, 92.96, 180.00, 0.0, 90.0
# 3 : (J) -146.4, -42.58, -0.68, -109.37, 0.99, -28.09, -57.7
#     (L) -493.64, -99.48, 92.96,  180.00, 0.0, 90.0
# 4 : (J) -155.7, -42.0, -0.28, -111.37, 0.42, -26.67, -66.22
#     (L) -493.64, -16.25, 92.96,  180.00, 0.0, 90.0
# 5 : (J) -164.14, -42.26, 0.28, -111.1, -0.43, -26.7, -73.42
#     (L) -493.64, 52.02, 92.96,  180.00, 0.0, 90.0
# 6 : (J) -126.8, -40.0, -3.66, -114.77, 5.57, -25.5, -44.65
#     (L) -417.62, -214.75, 92.96,  180.00, 0.0, 90.0
# 7 : (J) -137.41, -37.93, -3.17, -121.65, 5.59, -20.63, -55.09
#     (L) -417.62, -109.48, 92.96,  180.00, 0.0, 90.0
# 8 : (J) -155.3, -37.42, -1.69, -124.77, 3.34, -17.9, -69.71
#     (L) -417.62, 21.94, 92.96,  180.00, 0.0, 90.0

if __name__ == '__main__':
    rclpy.init()

    node = robotNode()
    try:
        node.RobotTask()
        rclpy.spin(node)

    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()