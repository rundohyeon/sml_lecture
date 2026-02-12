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

        # ---- Parameters for RealSense topics ----
        self.declare_parameter('color_topic', '/camera/camera/color/image_raw')
        self.declare_parameter('depth_topic', '/camera/camera/depth/image_rect_raw')

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

        # ---- Latest frames ----
        self.latest_color = None
        self.latest_depth = None

        self.show_window = True
        self.robot_status = 'Idle'

        self.get_logger().info("Robot node initialized!")


    # ========================= COLOR CALLBACK =========================
    def _on_color(self, msg: Image):
        try:
            cv_img = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            self.latest_color = cv_img

            if self.show_window:
                cv2.imshow("RealSense Color", cv_img)
                key = cv2.waitKey(1) & 0xFF
                if key == ord('q'):
                    cv2.imwrite('color_frame.jpg', cv_img)
                    self.get_logger().info("Quit requested. Shutting down...")
                    rclpy.shutdown()

        except Exception as e:
            self.get_logger().error(f"Color image conversion failed: {e}")


    # ========================= DEPTH CALLBACK =========================
    def _on_depth(self, msg: Image):
        try:
            depth = self.bridge.imgmsg_to_cv2(msg, desired_encoding='passthrough')
            self.latest_depth = depth

            if self.show_window:
                depth_copy = depth.astype(np.float32).copy()
                depth_copy[depth_copy == 0] = np.nan

                min_d = 200.0     # 20cm
                max_d = 2000.0    # 2m

                depth_clip = np.clip(depth_copy, min_d, max_d)
                depth_clip = (depth_clip - min_d) / (max_d - min_d)
                depth_clip[np.isnan(depth_clip)] = 0.0

                depth_8u = (depth_clip * 255.0).astype(np.uint8)
                depth_color = cv2.applyColorMap(depth_8u, cv2.COLORMAP_JET)

                cv2.imshow("RealSense Depth", depth_color)
                key = cv2.waitKey(1) & 0xFF
                if key == ord('q'):
                    cv2.imwrite('depth_frame.png', depth_8u)
                    self.get_logger().info("Depth window quit. Shutting down...")
                    rclpy.shutdown()

            # 로그 한 번만 출력
            if not hasattr(self, '_saved_depth'):
                self._saved_depth = True
                self.get_logger().info(
                    f"Depth frame received: shape={depth.shape}, dtype={depth.dtype}"
                )

        except Exception as e:
            self.get_logger().error(f"Depth image conversion failed: {e}")


    # ========================= ROBOT CONTROL =========================
    def sendCommand(self, cmd, mode='', coord=[]):
        if cmd == 'movel':
            (w, x, y, z) = euler.euler2quat(
                coord[3] * DEG2RAD,
                coord[4] * DEG2RAD,
                coord[5] * DEG2RAD
            )
            coord[3], coord[4], coord[5] = x, y, z
            coord.append(w)

        command = {"cmd": cmd, "mode": mode, "coord": coord}
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
            print(f"Unexpected error: {e}")

        finally:
            self.robot_status = 'running'


    def RobotTask(self):
        print("initialize")
        self.sendCommand('initialize')


# ========================= MAIN =========================
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

