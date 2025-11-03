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
        # # initialize
        # print("initialize")
        self.sendCommand('initialize')
        # time.sleep(4)
        self.sendCommand("movej", 'abs', [-146.4, -42.58, -0.68, -109.37, 0.99, -28.09, -57.7])
        time.sleep(4)


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