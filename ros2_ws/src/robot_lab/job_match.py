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
from sensor_msgs.msg import Image

import cv2
from cv_bridge import CvBridge

import transforms3d.euler as euler

# Dynamixel SDK
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
        self.show_window = True

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
        self.DXL_ADDR_TORQUE_ENABLE      = 64
        self.DXL_ADDR_GOAL_POSITION      = 116
        self.DXL_ADDR_PRESENT_POSITION   = 132
        self.DXL_ADDR_PROFILE_VELOCITY   = 112  # 회전 속도 설정용

        self.DXL_PROTOCOL_VERSION = 2.0
        self.DXL_TORQUE_ENABLE    = 1
        self.DXL_TORQUE_DISABLE   = 0

        # 그리퍼용 다이내믹셀 위치 (0~4095) – 필요시 튜닝
        self.DXL_OPEN_POS  = 3000   # 열린 위치
        self.DXL_CLOSE_POS = 3000 - 1850   # 닫힌 위치

        self.dxl_port_handler = None
        self.dxl_packet_handler = None
        self.dxl_ok = False
        self.dxl_is_open = False   # 현재 상태 플래그

        self._init_dynamixel()

        # ================== 로봇/비전 관련 파라미터 ==================

        # 안전 조인트 자세 (구동 시작 시 이동)
        self.safe_joint = [-136.78, -46.49, 3.92, -100.40, -5.15, -33.52, -129.76]

        # 1번 케이스 / 뚜껑 기준 pose (단위: m, deg)
        case1 = [-0.4968, -0.24453, -0.00132, 179.84, 0.16, 180.0]
        lid1  = [-0.4168, -0.28453, -0.00132, 179.84, 0.16, 180.0]

        # 케이스는 12cm 간격, 뚜껑은 8cm 간격
        dy_body = 0.12  # 12cm
        dy_lid  = 0.08  # 8cm

        # 케이스 3개 (12cm 간격)
        self.body_slots = []
        for i in range(3):
            p = case1.copy()
            p[1] += dy_body * i
            self.body_slots.append(p)

        # 뚜껑 5개 (8cm 간격)
        self.lid_slots = []
        for i in range(5):
            p = lid1.copy()
            p[1] += dy_lid * i
            self.lid_slots.append(p)

        # 그리퍼 기준 케이스/뚜껑이 있는 위치(물체 위치)에서
        # "물체 위 10cm" 기준 카메라가 정중앙에 오도록 하는 오프셋
        # → 물체의 (x, y, z+0.1) 에서 x-0.0346, y+0.06144, z-0.04054
        self.cam_offset = [-0.0346, 0.06144, -0.04054]

        # ---- Start robot task in a separate thread ----
        self.task_thread = threading.Thread(target=self.robot_main, daemon=True)
        self.task_thread.start()

    # ====================== Dynamixel helpers ======================

    def _init_dynamixel(self):
        """추가 Dynamixel 포트/패킷 핸들 초기화 + 토크 ON + 속도 설정 + 초기 OPEN"""
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

            # 회전 속도 설정 (Profile Velocity)
            slow_speed = 200  # 낮을수록 느림 (0~32767), 필요하면 조정
            dxl_comm_result, dxl_error = self.dxl_packet_handler.write4ByteTxRx(
                self.dxl_port_handler,
                self.dxl_id,
                self.DXL_ADDR_PROFILE_VELOCITY,
                slow_speed
            )

            if dxl_comm_result != 0 or dxl_error != 0:
                self.get_logger().error(
                    f"[DXL] Failed to set Profile Velocity (comm={dxl_comm_result}, err={dxl_error})"
                )
            else:
                self.get_logger().info(f"[DXL] Profile Velocity set to {slow_speed}")

            # 초기 상태: OPEN으로 맞추기
            self.dxl_open()
            self.get_logger().info("[DXL] Set initial position: OPEN")

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
        if not self.dxl_ok:
            return
        self._dxl_write_goal_position(self.DXL_OPEN_POS)
        self.dxl_is_open = True
        self.get_logger().info("[DXL] State -> OPEN")

    def dxl_close(self):
        """추가 Dynamixel: CLOSE"""
        if not self.dxl_ok:
            return
        self._dxl_write_goal_position(self.DXL_CLOSE_POS)
        self.dxl_is_open = False
        self.get_logger().info("[DXL] State -> CLOSE")

    def dxl_toggle(self):
        """현재 상태에서 180도 회전 (OPEN <-> CLOSE 토글)"""
        if not self.dxl_ok:
            self.get_logger().warn("[DXL] Not initialized, skip toggle")
            return

        if self.dxl_is_open:
            self.get_logger().info("[DXL] Toggle: OPEN -> CLOSE")
            self.dxl_close()
        else:
            self.get_logger().info("[DXL] Toggle: CLOSE -> OPEN")
            self.dxl_open()

    # ====================== Callbacks ======================

    def _on_color(self, msg: Image):
        """RealSense 컬러 콜백 - 최신 프레임 저장 + raw 화면 표시"""
        try:
            cv_img = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            self.latest_color = cv_img

            if self.show_window:
                cv2.imshow("Color_raw", cv_img)
                cv2.waitKey(1)

        except Exception as e:
            self.get_logger().error(f"Color image conversion failed: {e}")

    # ====================== Robot command helpers ======================

    def sendCommand(self, cmd, mode='', coord=[]):
        """
        topic message type is String
        "movej", "movel", "gripper" 등 로봇 컨트롤 명령 전송
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
        # 로봇이 움직이는 동안 잠깐 대기 (간단한 동기화용)
        time.sleep(3.0)

    # ====================== Vision helper ======================

    def estimate_inner_square_size(self, img, label="obj") -> float:
        """
        중앙 60% ROI + HSV S 채널 threshold 기반으로
        바깥/안쪽 정사각형을 찾아서 안쪽 길이를 m 단위로 추정
        """

        if img is None:
            self.get_logger().warn(f"[{label}] No image available")
            return np.nan

        h, w, _ = img.shape

        # --- 중앙 60% ROI ---
        x0 = int(w * 0.2)
        x1 = int(w * 0.8)
        y0 = int(h * 0.2)
        y1 = int(h * 0.8)
        roi = img[y0:y1, x0:x1].copy()

        # 원본에 ROI 박스 그려서 보기
        vis_full = img.copy()
        cv2.rectangle(vis_full, (x0, y0), (x1, y1), (0, 255, 0), 2)
        if self.show_window:
            cv2.imshow("Color_with_ROI", vis_full)
            cv2.waitKey(1)

        # --- HSV S 채널 기반 이진화 ---
        hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
        _, s_ch, _ = cv2.split(hsv)

        threshold = 80  # 실습에서 사용하던 값
        _, binary = cv2.threshold(s_ch, threshold, 255, cv2.THRESH_BINARY)

        if self.show_window:
            cv2.imshow(f"{label}_roi_binary", binary)
            cv2.waitKey(1)

        # --- 컨투어 찾기 ---
        cnts, hier = cv2.findContours(
            binary, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_SIMPLE
        )

        if hier is None or len(cnts) == 0:
            self.get_logger().warn(f"[{label}] No contour found in binary image")
            return np.nan

        # 면적 기준 상위 2개 -> OUTER, INNER
        areas = [(cv2.contourArea(c), i) for i, c in enumerate(cnts)]
        areas.sort(reverse=True)

        if len(areas) < 2:
            self.get_logger().warn(
                f"[{label}] Not enough contours (len={len(areas)})"
            )
            return np.nan

        outer_idx = areas[0][1]
        inner_idx = areas[1][1]

        c_outer = cnts[outer_idx]
        c_inner = cnts[inner_idx]

        # 가시화용: ROI 위에 OUTER/INNER 그려보기
        roi_vis = roi.copy()
        cv2.drawContours(roi_vis, [c_outer], -1, (0, 0, 255), 2)  # 빨강: outer
        cv2.drawContours(roi_vis, [c_inner], -1, (255, 0, 0), 2)  # 파랑: inner

        if self.show_window:
            cv2.imshow(f"{label}_detected", roi_vis)
            cv2.waitKey(1)

        # --- boundingRect로 길이 계산 ---
        xo, yo, wo, ho = cv2.boundingRect(c_outer)
        xi, yi, wi, hi = cv2.boundingRect(c_inner)

        outer_side_px = (wo + ho) / 2.0
        inner_side_px = (wi + hi) / 2.0

        if outer_side_px < 10 or inner_side_px < 5:
            self.get_logger().warn(
                f"[{label}] outer/inner too small (outer={outer_side_px}, inner={inner_side_px})"
            )
            return np.nan

        # --- px -> m (OUTER = 40mm) ---
        OUTER_SIDE_M = 0.04  # 40mm
        meter_per_px = OUTER_SIDE_M / outer_side_px
        inner_side_m = inner_side_px * meter_per_px

        return float(inner_side_m)

    def measure_slot(self, base_pose, label):
        """
        물체(base_pose) 기준 케이스/뚜껑 위치에서
        카메라 오프셋을 적용한 시점으로 movel 한 뒤,
        latest_color로 inner square 크기 측정
        """
        vision_pose = base_pose.copy()
        vision_pose[0] += self.cam_offset[0]
        vision_pose[1] += self.cam_offset[1]
        vision_pose[2] += 0.1 + self.cam_offset[2]  # 물체 위 10cm + cam_offset_z

        self.get_logger().info(
            f"[{label}] movel(base_abs) to vision pose: {vision_pose}"
        )
        self.sendCommand("movel", "base_abs", vision_pose)

        # 색상 프레임이 최신으로 들어올 시간을 조금 줌
        time.sleep(0.5)

        size_m = self.estimate_inner_square_size(self.latest_color, label=label)
        self.get_logger().info(f"[{label}] inner square size = {size_m} m")
        return size_m

    # ====================== Matching & Task ======================

    def auto_match_task(self):
        """
        [TEST MODE]
        - 비전 인식 / 길이 측정 / greedy 매칭 전부 생략
        - 정답 매칭 (body, lid) = (0,1), (1,2), (2,3) 고정
        - 순서대로 body 0 → 1 → 2에 대해 픽앤플레이스만 실행
        """

        self.get_logger().info("=== [TEST] Fixed pick&place without vision ===")

        # 1) 안전 자세로 이동
        self.get_logger().info("=== Move to safe joint position ===")
        self.sendCommand("movej", "abs", self.safe_joint)

        # 2) 정답 매칭 하드코딩
        fixed_pairs = [
            (0, 1),  # body 0 <- lid 1
            (1, 2),  # body 1 <- lid 2
            (2, 3),  # body 2 <- lid 3
        ]

        self.get_logger().info(f"[TEST] Using fixed pairs: {fixed_pairs}")

        # 3) body 0 → 1 → 2 순서대로 픽앤플레이스
        for (b_idx, l_idx) in fixed_pairs:
            self.get_logger().info(f"[TEST] Assemble body {b_idx} <- lid {l_idx}")
            self.assemble_lid_to_body(b_idx, l_idx)

        self.get_logger().info("=== [TEST] fixed auto_match_task finished ===")

    def assemble_lid_to_body(self, body_idx, lid_idx):
        """
        매칭된 lid를 집어서 180도 회전 후 매칭된 body에 꽂는 픽앤플레이스 동작.
        순서:
        1) 매칭된 lid의 바로 위까지 수평방향으로 이동
        2) 매칭된 lid의 저장된 좌표까지 수직방향 아래로 이동
        3) gripper close
        4) z + 0.1m (base_rel)
        5) dxl_toggle()으로 180도 회전
        6) 매칭된 body의 바로 위(+y 오프셋)까지 수평방향으로 이동
        7) body의 저장된 좌표(+y 오프셋, z=0.03545)까지 수직방향 아래로 이동
        """
        self.get_logger().info(
            f"[ASSEMBLE] body {body_idx} <- lid {lid_idx}"
        )

        lid_pose  = self.lid_slots[lid_idx].copy()     # [x, y, z, rx, ry, rz]
        body_pose = self.body_slots[body_idx].copy()   # [x, y, z, rx, ry, rz]

        z_lift = 0.10
        x_offset = 0.003
        y_offset = -0.005    # ← body 쪽으로 갈 때 y를 이만큼 더 밀어줌
        insert_z = 0.03545  # ← 너가 말한 최대 삽입 깊이

        # 1) lid 위로 수평 이동 (lid 자세 사용)
        approach_lid = lid_pose.copy()
        approach_lid[2] = lid_pose[2] + z_lift
        self.get_logger().info(f"[ASSEMBLE] move above lid {lid_idx}: {approach_lid}")
        self.sendCommand("movel", "base_abs", approach_lid)

        # 2) lid 저장된 좌표까지 수직 아래로
        pick_pose = lid_pose.copy()
        self.get_logger().info(f"[ASSEMBLE] move down to lid {lid_idx}: {pick_pose}")
        self.sendCommand("movel", "base_abs", pick_pose)

        # 3) gripper close
        self.get_logger().info("[ASSEMBLE] gripper close")
        try:
            self.sendCommand("gripper", "close", [])
        except Exception as e:
            self.get_logger().warn(f"[ASSEMBLE] gripper close command failed: {e}")

        # 4) z + 0.1m 위로 (현재 자세 기준 base_rel)
        self.get_logger().info("[ASSEMBLE] lift lid up (base_rel z +0.1)")
        lift_rel = [0.0, 0.0, z_lift, 0.0, 0.0, 0.0]
        self.sendCommand("movel", "base_rel", lift_rel)

        # 5) DXL 180도 회전 (OPEN <-> CLOSE 토글)
        self.get_logger().info("[ASSEMBLE] rotate lid 180deg with Dynamixel (toggle)")
        self.dxl_toggle()
        time.sleep(0.5)

        # lid에서 쓰던 orientation 유지
        rx, ry, rz = lid_pose[3], lid_pose[4], lid_pose[5]

        # 6) body 위로 수평 이동 (여기서 y에 +0.005 오프셋)
        approach_body = [
            body_pose[0] + x_offset,                    # x
            body_pose[1] + y_offset,         # y + 0.005
            body_pose[2] + z_lift,           # z: body 위 10cm
            rx, ry, rz
        ]
        self.get_logger().info(f"[ASSEMBLE] move above body {body_idx}: {approach_body}")
        self.sendCommand("movel", "base_abs", approach_body)

        # 7) body 삽입 위치로 수직 아래로 (y 오프셋 + z 고정)
        place_pose = [
            body_pose[0] + x_offset,
            body_pose[1] + y_offset,         # y + 0.005
            insert_z,                        # z = 0.03545 고정
            rx, ry, rz
        ]
        self.get_logger().info(f"[ASSEMBLE] move down to body {body_idx}: {place_pose}")
        self.sendCommand("movel", "base_abs", place_pose)

        self.get_logger().info("[ASSEMBLE] sequence finished.")

        # 8) gripper open
        self.get_logger().info("[ASSEMBLE] gripper open")
        try:
            self.sendCommand("gripper", "open", [])
        except Exception as e:
            self.get_logger().warn(f"[ASSEMBLE] gripper open command failed: {e}")
        self.sendCommand("movel", "base_rel", [0.0, 0.0, 0.05, 0.0, 0.0, 0.0])

    # ====================== Main task thread ======================

    def robot_main(self):
        """
        이 함수가 '메인 함수'처럼 한 번 실행되는 로봇 태스크.
        __init__에서 스레드로 호출됨.
        """
        self.get_logger().info("Robot main started.")

        # 시작할 때 그리퍼 OPEN 보장 (로봇 내장 그리퍼 기준)
        self.get_logger().info("[INIT] Ensure robot gripper is OPEN")
        try:
            self.sendCommand("gripper", "open", [])
        except Exception as e:
            self.get_logger().warn(f"[INIT] Failed to send initial gripper open: {e}")

        # 카메라 첫 프레임 들어올 때까지 대기
        while rclpy.ok() and self.latest_color is None:
            self.get_logger().info("Waiting for first color frame...")
            time.sleep(0.1)

        if not rclpy.ok():
            return

        self.get_logger().info("First color frame received. Start auto match task.")
        self.auto_match_task()
        self.get_logger().info("Robot main finished.")


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
