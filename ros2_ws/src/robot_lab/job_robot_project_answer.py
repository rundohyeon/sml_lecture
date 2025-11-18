#!/usr/bin/env python3
# ros2 launch realsense2_camera rs_launch.py align_depth.enable:=true

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

import json
import math
import time
import threading
import numpy as np

from std_msgs.msg import String
from sensor_msgs.msg import Image, CameraInfo

import cv2
from cv_bridge import CvBridge

import transforms3d.euler as euler

DEG2RAD = math.pi / 180.0
RAD2DEG = 180.0 / math.pi


class robotNode(Node):
    def __init__(self):
        super().__init__('robot_node')

        # ---- Publisher for robot command ----
        self.publisher_ = self.create_publisher(String, 'indyrp2_node/command', 10)

        # ---- Parameters for RealSense topics ----
        self.declare_parameter('color_topic', '/camera/camera/color/image_raw')
        self.declare_parameter('depth_topic', '/camera/camera/aligned_depth_to_color/image_raw')
        self.declare_parameter('info_topic', '/camera/camera/color/camera_info')

        color_topic = self.get_parameter('color_topic').get_parameter_value().string_value
        depth_topic = self.get_parameter('depth_topic').get_parameter_value().string_value
        info_topic = self.get_parameter('info_topic').get_parameter_value().string_value

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
        self.sub_info = self.create_subscription(
            CameraInfo, info_topic, self._on_camera_info, 10
        )

        # ---- Latest frames ----
        self.latest_color = None
        self.latest_depth = None
        self.show_window = True

        # ---- Camera intrinsics ----
        self.fx = None
        self.fy = None
        self.cx = None
        self.cy = None
        self.camera_frame_id = "camera_link"
        self.has_camera_info = False
        self.depth_scale = 0.001

        self.grasp_point = None

        # ---- Blue mask HSV range ----
        # OpenCV HSV: H (0~179), S (0~255), V (0~255)
        self.lower_blue = np.array([50, 80, 50], dtype=np.uint8)
        self.upper_blue = np.array([140, 255, 255], dtype=np.uint8)
        self.min_area = 500

        # ---- Robot/task status ----
        self.robot_status = 'Idle'
        self.task_started = False       # RobotTask가 이미 실행되었는지
        self.task_running = False       # RobotTask 스레드가 동작 중인지

        self.task_timer = self.create_timer(0.1, self._task_timer)
        self.get_logger().info("BlueTapeGraspDetector + RobotTask node started.")

    # ====================== Callbacks ======================

    def _on_color(self, msg: Image):
        try:
            cv_img = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            self.latest_color = cv_img

            # Depth + CameraInfo 준비되면 이 프레임에서 grasp point 업데이트
            if self.latest_depth is not None and self.has_camera_info:
                self.detect_and_update_grasp()

            if self.show_window:
                cv2.imshow("Color", cv_img)
                cv2.waitKey(1)

        except Exception as e:
            self.get_logger().error(f"Color image conversion failed: {e}")

    def _on_depth(self, msg: Image):
        try:
            depth = self.bridge.imgmsg_to_cv2(msg, desired_encoding='passthrough')
            self.latest_depth = depth
        except Exception as e:
            self.get_logger().error(f"Depth image conversion failed: {e}")

    def _on_camera_info(self, msg: CameraInfo):
        try:
            self.fx = msg.k[0]
            self.fy = msg.k[4]
            self.cx = msg.k[2]
            self.cy = msg.k[5]
            self.camera_frame_id = msg.header.frame_id
            self.has_camera_info = True
        except Exception as e:
            self.get_logger().error(f"CameraInfo conversion failed: {e}")


    # ====================== Blue color detection ======================
    def detect_and_update_grasp(self):
        if self.latest_color is None or self.latest_depth is None:
            return
        if not self.has_camera_info:
            return

        color_bgr = self.latest_color
        depth_raw = self.latest_depth

        # 1) BGR -> HSV
        hsv = cv2.cvtColor(color_bgr, cv2.COLOR_BGR2HSV)

        # 2) Blue mask
        mask = cv2.inRange(hsv, self.lower_blue, self.upper_blue)

        # 3) Morphology (noise reduction)
        kernel = np.ones((5, 5), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

        # 4) Contours
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if len(contours) == 0:
            # 파란색 없으면 그냥 마지막 grasp_point를 유지
            if self.show_window:
                cv2.imshow("BlueMask", mask)
                cv2.waitKey(1)
            return

        largest = max(contours, key=cv2.contourArea)
        area = cv2.contourArea(largest)
        if area < self.min_area:
            if self.show_window:
                cv2.imshow("BlueMask", mask)
                cv2.waitKey(1)
            return

        # 5) 파란색 중심점 (u, v)
        M = cv2.moments(largest)
        if M["m00"] == 0:
            self.get_logger().warn("Zero moment (m00 == 0), skip this contour.")
            return

        u = int(M["m10"] / M["m00"])
        v = int(M["m01"] / M["m00"])

        # image range check
        if (u < 0 or v < 0 or
            v >= depth_raw.shape[0] or u >= depth_raw.shape[1]):
            self.get_logger().warn("Centroid out of depth image bounds.")
            return

        # 6) depth 값 계산 (from aligned depth image)
        z_raw = depth_raw[v, u]
        if z_raw == 0:
            self.get_logger().info("Depth at grasp point is 0 (no measurement).")
            return

        Z = float(z_raw) * self.depth_scale  # meter

        # 7) 카메라 좌표계로 변환
        X = (u - self.cx) / self.fx * Z
        Y = (v - self.cy) / self.fy * Z

        # 최신 grasp_point 업데이트
        self.grasp_point = (X, Y, Z)
        # self.get_logger().info(f"grasp_point (camera): X={X:.3f}, Y={Y:.3f}, Z={Z:.3f}")

        if self.show_window:
            vis = color_bgr.copy()
            cv2.drawContours(vis, [largest], -1, (0, 255, 0), 2)
            cv2.circle(vis, (u, v), 6, (0, 0, 255), -1)
            cv2.putText(vis, f"({X:.3f},{Y:.3f},{Z:.3f})",
                        (u + 5, v - 5),
                        cv2.FONT_HERSHEY_SIMPLEX,
                        0.5, (255, 0, 0), 1, cv2.LINE_AA)
            cv2.imshow("BlueTape Detection", vis)
            cv2.imshow("BlueMask", mask)
            cv2.waitKey(1)

    # ====================== Grasp point helper ======================

    def getGraspPoint(self):
        """
        self.grasp_point (카메라 프레임 XYZ)를
        오프셋/안전성 체크 후 최종 사용 위치로 반환.

        return:
            (x, y, z)  : 유효하고 안전한 경우
            False      : 포인트는 있지만 unsafe
            None       : 아직 검출된 포인트 없음
        """
        if self.grasp_point is None:
            return None

        X, Y, Z = self.grasp_point

        # 카메라->툴 오프셋 등 (지금은 네가 쓰던 값 그대로)
        gx = X - 0.0325
        gy = Y - 0.06
        gz = Z - 0.1
        
        return (gx, gy, gz)

    # ====================== Robot command helpers ======================

    def sendCommand(self, cmd, mode='', coord=[]):
        """
        topic message type is String
        """

        if cmd == 'movel':
            # coord: [x, y, z, Rx(deg), Ry(deg), Rz(deg)]
            (w, x, y, z) = euler.euler2quat(
                coord[3]*DEG2RAD,
                coord[4]*DEG2RAD,
                coord[5]*DEG2RAD
            )  # (w, x, y, z)
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

        print(f"Published: {msg.data}")
        time.sleep(3)

    # ====================== Task timer + RobotTask ======================

    def _task_timer(self):
        """
        0.1초마다 호출.
        - 카메라 준비 여부 확인
        - grasp point 상태 확인
        - SAFE한 grasp point가 존재하고, 아직 RobotTask가 안 돌았다면 RobotTask를 스레드로 1번 실행
        """
        if self.task_started:
            return  

        if not self.has_camera_info:
            return
        if self.latest_color is None or self.latest_depth is None:
            return

        pos = self.getGraspPoint()

        if pos is None:
            # no blue color
            return

        self.task_started = True
        self.get_logger().info(f"Starting RobotTask with grasp pos: {pos}")

        # move robot
        th = threading.Thread(target=self.RobotTask, args=(pos,), daemon=True)
        th.start()
        self.task_running = True

    def RobotTask(self, grasp_pos):
        """
        grasp_pos: (x, y, z) [m] in tool frame
        """

        # open gripperr
        self.sendCommand("gripper", "open")

        # get grasp pose                                                                                                                                 
        gx, gy, gz = grasp_pos
        self.get_logger().info(f"[RobotTask] grasp point (tool frame) :  {grasp_pos}")

        # 2) above grasp point (only x, y)
        self.get_logger().info("[RobotTask] Moving tool in XY toward grasp position...")
        self.sendCommand("movel", "tool", [gx, gy, 0.0, 0.0, 0.0, 0.0])

        # 3) move down to grasp point (z)
        self.get_logger().info("[RobotTask] Moving tool in Z toward grasp depth...")
        self.sendCommand("movel", "tool", [0.0, 0.0, gz, 0.0, 0.0, 0.0])

        # 4) gripper close
        self.get_logger().info("[RobotTask] Closing gripper...")
        self.sendCommand("gripper", "close")

        # 5) pick up toothbrush
        self.get_logger().info("[RobotTask] Lifting object...")
        self.sendCommand("movel", "tool", [0.0, 0.0, -0.048, 0.0, 0.0, 0.0])

        self.get_logger().info("[RobotTask] Finished pick sequence.")
        self.task_running = False


def main(args=None):
    rclpy.init(args=args)
    node = robotNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()
        cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
