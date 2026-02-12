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

# ---- Dynamixel SDK (추가된 부분) ----
from dynamixel_sdk import PortHandler, PacketHandler  # pip install dynamixel-sdk

DEG2RAD = math.pi / 180.0
RAD2DEG = 180.0 / math.pi


class robotNode(Node):
    def __init__(self):
        super().__init__('robot_node')

        # ---- Publisher for robot command ----
        self.publisher_ = self.create_publisher(String, 'indyrp2_node/command', 10)

        # ---- Parameters for RealSense topics ----
        self.declare_parameter('color_topic', '/camera/camera/color/image_raw')
        color_topic = self.get_parameter('color_topic').get_parameter_value().string_value

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

        # ---- Robot/task status ----
        self.robot_status = 'Idle'

        self.get_logger().info("RobotTask node started.")

        # ================== Dynamixel (추가 모터) 설정 ==================

        # 파라미터로 포트/보레이트/ID 설정 가능하게
        self.declare_parameter('dxl_device_name', '/dev/ttyUSB0')
        self.declare_parameter('dxl_baudrate', 57600)
        self.declare_parameter('dxl_id', 1)

        self.dxl_device_name = self.get_parameter('dxl_device_name').get_parameter_value().string_value
        self.dxl_baudrate = self.get_parameter('dxl_baudrate').get_parameter_value().integer_value
        self.dxl_id = self.get_parameter('dxl_id').get_parameter_value().integer_value

        # XM/XH/X-series 기준 주소 (Protocol 2.0)
        self.DXL_ADDR_TORQUE_ENABLE    = 64
        self.DXL_ADDR_GOAL_POSITION    = 116
        self.DXL_ADDR_PRESENT_POSITION = 132

        self.DXL_PROTOCOL_VERSION = 2.0
        self.DXL_TORQUE_ENABLE    = 1
        self.DXL_TORQUE_DISABLE   = 0

        # 이 값들은 그리퍼용 다이내믹셀 위치에 맞게 튜닝 필요 (0~4095)
        self.DXL_OPEN_POS  = 3000   # 열린 위치
        self.DXL_CLOSE_POS = 1500   # 닫힌 위치

        self.dxl_port_handler = None
        self.dxl_packet_handler = None
        self.dxl_ok = False

        self._init_dynamixel()

        # ---- Start robot task in a separate thread ----
        self.task_thread = threading.Thread(target=self.robot_main, daemon=True)
        self.task_thread.start()

    # ====================== Dynamixel helpers (서보랑 완전 분리) ======================

    def _init_dynamixel(self):
        """추가 Dynamixel 포트/패킷 핸들 초기화 + 토크 ON"""
        try:
            self.dxl_port_handler = PortHandler(self.dxl_device_name)
            self.dxl_packet_handler = PacketHandler(self.DXL_PROTOCOL_VERSION)

            # Open port
            if not self.dxl_port_handler.openPort():
                self.get_logger().error(f"[DXL] Failed to open port: {self.dxl_device_name}")
                return

            # Set baudrate
            if not self.dxl_port_handler.setBaudRate(self.dxl_baudrate):
                self.get_logger().error(f"[DXL] Failed to set baudrate: {self.dxl_baudrate}")
                return

            # Enable torque
            dxl_comm_result, dxl_error = self.dxl_packet_handler.write1ByteTxRx(
                self.dxl_port_handler,
                self.dxl_id,
                self.DXL_ADDR_TORQUE_ENABLE,
                self.DXL_TORQUE_ENABLE
            )

            if dxl_comm_result != 0 or dxl_error != 0:
                self.get_logger().error(
                    f"[DXL] Failed to enable torque (id={self.dxl_id}, "
                    f"comm={dxl_comm_result}, err={dxl_error})"
                )
                return

            self.get_logger().info(
                f"[DXL] Initialized on {self.dxl_device_name} "
                f"(baud={self.dxl_baudrate}, id={self.dxl_id})"
            )
            self.dxl_ok = True

        except Exception as e:
            self.get_logger().error(f"[DXL] Exception while init: {e}")
            self.dxl_ok = False

    def _dxl_write_goal_position(self, pos):
        """추가 Dynamixel 목표 위치 쓰기"""
        if not self.dxl_ok:
            self.get_logger().warn("[DXL] Not initialized, skip write_goal_position")
            return

        dxl_comm_result, dxl_error = self.dxl_packet_handler.write4ByteTxRx(
            self.dxl_port_handler,
            self.dxl_id,
            self.DXL_ADDR_GOAL_POSITION,
            int(pos)
        )

        if dxl_comm_result != 0 or dxl_error != 0:
            self.get_logger().error(
                f"[DXL] Failed to write goal position {pos} "
                f"(comm={dxl_comm_result}, err={dxl_error})"
            )
        else:
            self.get_logger().info(f"[DXL] Goal position -> {pos}")

    def dxl_open(self):
        """추가 Dynamixel: OPEN"""
        self.get_logger().info("[DXL] OPEN")
        self._dxl_write_goal_position(self.DXL_OPEN_POS)

    def dxl_close(self):
        """추가 Dynamixel: CLOSE"""
        self.get_logger().info("[DXL] CLOSE")
        self._dxl_write_goal_position(self.DXL_CLOSE_POS)

    # ====================== Callbacks ======================

    def _on_color(self, msg: Image):
        try:
            cv_img = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            self.latest_color = cv_img

            if self.show_window:
                cv2.imshow("Color", cv_img)
                cv2.waitKey(1)

        except Exception as e:
            self.get_logger().error(f"Color image conversion failed: {e}")

    # ====================== Robot command helpers (기존 서보/로봇용) ======================

    def sendCommand(self, cmd, mode='', coord=[]):
        """
        topic message type is String
        -> 여기는 기존 로봇 + 서보 컨트롤 그대로 사용
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

        self.get_logger().info(f"Published: {msg.data}")
        time.sleep(3)

    # ====================== Your task function (used like main) ======================

    def task(self):
        """
        로봇 + 기존 서보 그리퍼 + 추가 Dynamixel 모터를
        동시에 써보는 예시 태스크
        """

        # 1) 기존 서보 그리퍼 (로봇 컨트롤러 쪽에서 처리)
        self.get_logger().info("=== Servo gripper sequence ===")
        # self.sendCommand("gripper", "open")
        # time.sleep(1)
        self.sendCommand("gripper", "close")
        time.sleep(1)

        # # 2) 추가 Dynamixel 모터 (로봇과 완전 별도)
        # self.get_logger().info("=== Dynamixel extra motor sequence ===")
        # self.dxl_open()
        # time.sleep(2)
        # self.dxl_close()
        # time.sleep(2)

        # 필요하면 둘을 동시에/섞어서 써도 됨

    def robot_main(self):
        """
        이 함수가 '메인 함수'처럼 한 번 실행되는 로봇 태스크.
        __init__에서 스레드로 호출됨.
        """

        self.get_logger().info("Robot task started.")

        # 카메라 첫 프레임 들어올 때까지 대기
        while rclpy.ok() and self.latest_color is None:
            self.get_logger().info("Waiting for first color frame...")
            time.sleep(0.1)

        if not rclpy.ok():
            return

        self.get_logger().info("First color frame received. Start robot sequence.")

        self.task()

        self.get_logger().info("Robot task finished.")

        # 반복시키고 싶으면 while rclpy.ok(): 로 감싸서 loop 가능


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
