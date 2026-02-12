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

        # ---- RealSense topic params ----
        self.declare_parameter('color_topic', '/camera/camera/color/image_raw')
        self.declare_parameter('depth_topic', '/camera/camera/depth/image_rect_raw')

        color_topic = self.get_parameter('color_topic').get_parameter_value().string_value
        depth_topic = self.get_parameter('depth_topic').get_parameter_value().string_value

        # ---- QoS ----
        sensor_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=5,
            durability=DurabilityPolicy.VOLATILE
        )

        self.bridge = CvBridge()

        # ---- Subscribers ----
        self.color_sub = self.create_subscription(Image, color_topic, self._on_color, sensor_qos)
        self.depth_sub = self.create_subscription(Image, depth_topic, self._on_depth, sensor_qos)

        self.latest_color = None
        self.latest_depth = None
        self.show_window = True
        self.robot_status = 'Idle'

        # =======  슬롯 좌표 세팅  =======
        # 기준 뚜껑 슬롯 (아래줄 왼쪽 첫 번째)
        base_lid = np.array([-0.41881, -0.15743, -0.00311, -179.33, 0.28, 179.40])  # [x, y, z, u, v, w]

        # y 방향 80mm 간격으로 5개
        self.lid_slots = []
        for i in range(5):
            p = base_lid.copy()
            p[1] += 0.08 * i
            self.lid_slots.append(p)

        # 기준 본체 슬롯 (윗줄 왼쪽 첫 번째)  ← 실제 값 넣어줘야 함!!
        base_body = np.array([-0.49881, -0.11743, -0.00311, -179.33, 0.28, 179.40])  # TODO: z, y 값 조정
        self.body_slots = []
        for i in range(3):
            p = base_body.copy()
            p[1] += 0.08 * i
            self.body_slots.append(p)

        # 비전 한 번 끝나면 작업 시작하도록 플래그
        self.vision_done = False
        self.mapping = None  # {lid_idx: body_idx}

        # 일정 주기로 비전 + 작업 루프 실행
        self.timer = self.create_timer(0.5, self._main_loop)

    # ======================
    #  ROS I/O
    # ======================
    def _on_color(self, msg: Image):
        try:
            cv_img = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            self.latest_color = cv_img

            if self.show_window:
                cv2.imshow("RealSense Color", cv_img)
                key = cv2.waitKey(1) & 0xFF
                if key == ord('q'):
                    self.get_logger().info("Quit requested")
                    rclpy.shutdown()

        except Exception as e:
            self.get_logger().error(f"Color image conversion failed: {e}")

    def _on_depth(self, msg: Image):
        try:
            depth = self.bridge.imgmsg_to_cv2(msg, desired_encoding='passthrough')
            self.latest_depth = depth
        except Exception as e:
            self.get_logger().error(f"Depth image conversion failed: {e}")

    # ======================
    #  로봇 명령
    # ======================
    def sendCommand(self, cmd, mode='', coord=None):
        if coord is None:
            coord = []

        if cmd == 'movel':
            # coord = [x, y, z, u, v, w] (deg)  → quaternion
            (wq, xq, yq, zq) = euler.euler2quat(coord[3] * DEG2RAD,
                                                coord[4] * DEG2RAD,
                                                coord[5] * DEG2RAD)
            coord_q = coord.copy()
            coord_q[3] = xq
            coord_q[4] = yq
            coord_q[5] = zq
            coord_q.append(wq)
        else:
            coord_q = coord

        command = {
            "cmd": cmd,
            "mode": mode,
            "coord": coord_q
        }

        msg = String()
        msg.data = json.dumps(command)
        self.publisher_.publish(msg)
        self.get_logger().info(f"Published: {msg.data}")
        time.sleep(2.0)

    def gripper_close(self):
        # TODO: 실제 그리퍼 명령으로 바꾸기
        self.sendCommand("gripper", "close")

    def gripper_open(self):
        # TODO: 실제 그리퍼 명령으로 바꾸기
        self.sendCommand("gripper", "open")

    def dynamixel_rotate(self, angle_deg):
        # TODO: 다이나믹셀 제어 노드/토픽에 맞게 수정
        # 예시: /dynamixel/goal_angle 토픽에 publish 등
        self.get_logger().info(f"[Dummy] Dynamixel rotate to {angle_deg} deg")
        time.sleep(1.0)

    # ======================
    #  Vision: 뚜껑/본체 인식
    # ======================
    def detect_squares(self, img):
        """
        img 에서 파란 테이프 테두리 사각형들을 찾고
        각 사각형의 중심(y), 넓이로 뚜껑/본체 나눔 + 크기 반환.
        return:
            lids  = [{'center_x':..,'center_y':..,'area':..}, ...]
            bodies= [{'center_x':..,'center_y':..,'area':..}, ...]
        """
        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

        # 파란 테이프 roughly threshold (대충 값, 나중에 튜닝)
        lower_blue = np.array([90, 50, 50])
        upper_blue = np.array([140, 255, 255])
        mask = cv2.inRange(hsv, lower_blue, upper_blue)

        # morphology 조금
        kernel = np.ones((3, 3), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=1)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=1)

        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        h_img, w_img = img.shape[:2]
        all_sq = []
        for c in contours:
            area = cv2.contourArea(c)
            if area < 500:  # 너무 작은 건 무시
                continue

            # 사각형 approximation
            peri = cv2.arcLength(c, True)
            approx = cv2.approxPolyDP(c, 0.02 * peri, True)
            if len(approx) != 4:
                continue

            x, y, w, h = cv2.boundingRect(approx)
            cx = x + w / 2.0
            cy = y + h / 2.0

            sq = {
                "center_x": cx,
                "center_y": cy,
                "area": float(w * h),
                "bbox": (x, y, w, h)
            }
            all_sq.append(sq)

        # 위/아래 줄 나누기: y 기준으로 k-means 나 median split
        if not all_sq:
            return [], []

        ys = np.array([s["center_y"] for s in all_sq])
        y_median = np.median(ys)

        lids = []
        bodies = []
        for s in all_sq:
            if s["center_y"] > y_median:
                lids.append(s)    # 아래쪽
            else:
                bodies.append(s)  # 위쪽

        # 디버그용
        self.get_logger().info(f"Detected {len(lids)} lids, {len(bodies)} bodies")

        return lids, bodies

    def match_lids_to_bodies(self, lids, bodies):
        """
        넓이(=크기)를 기준으로 가장 가까운 body 와 매칭.
        실제론 미리 측정한 size threshold 로 discrete class 나눠도 됨.
        return: {lid_idx: body_idx}
        """
        if not lids or not bodies:
            return None

        lid_areas = np.array([l["area"] for l in lids])
        body_areas = np.array([b["area"] for b in bodies])

        mapping = {}
        for i, a in enumerate(lid_areas):
            # 가장 넓이 가까운 body 찾기
            j = int(np.argmin(np.abs(body_areas - a)))
            mapping[i] = j

        self.get_logger().info(f"Pairing (lid_idx -> body_idx): {mapping}")
        return mapping

    # ======================
    #  Pick & Place 로직
    # ======================
    def pick_and_place_one(self, lid_slot_idx, body_slot_idx):
        # """
        # 특정 뚜껑 슬롯 → 특정 본체 슬롯으로 옮기고 180° 회전
        # """
        # lid_pose = self.lid_slots[lid_slot_idx].copy()
        # body_pose = self.body_slots[body_slot_idx].copy()

        # # safe z 조금 위로 올려서 접근용
        # safe_z = 100.0  # mm, 상황에 맞게 수정

        # # 1) 뚜껑 위로 이동
        # p = lid_pose.copy()
        # p[2] = safe_z
        # self.sendCommand('movel', coord=p.tolist())

        # # 2) 뚜껑까지 내려가기
        # p[2] = lid_pose[2]  # 실제 Z
        # self.sendCommand('movel', coord=p.tolist())

        # # 3) 그리퍼 닫기
        # self.gripper_close()

        # # 4) 다시 safe z
        # p[2] = safe_z
        # self.sendCommand('movel', coord=p.tolist())

        # # 5) 본체 위로 이동
        # q = body_pose.copy()
        # q[2] = safe_z
        # self.sendCommand('movel', coord=q.tolist())

        # # 6) 본체 쪽으로 내려가기
        # q[2] = body_pose[2]
        # self.sendCommand('movel', coord=q.tolist())

        # # 7) 다이나믹셀 180도 회전
        # self.dynamixel_rotate(180.0)

        # # 8) 그리퍼 오픈
        # self.gripper_open()

        # # 9) 다시 safe z 로 올라가기
        # q[2] = safe_z
        # self.sendCommand('movel', coord=q.tolist())

    # ======================
    #  메인 루프
    # ======================
    def _main_loop(self):
        # 아직 이미지 안 들어왔으면 패스
        if self.latest_color is None or self.latest_depth is None:
            return

        # 비전 아직 안 했으면 한 번만 수행
        if not self.vision_done:
            lids, bodies = self.detect_squares(self.latest_color)
            mapping = self.match_lids_to_bodies(lids, bodies)
            if mapping is None:
                self.get_logger().warn("No valid mapping yet...")
                return
            self.mapping = mapping
            self.vision_done = True
            self.get_logger().info("Vision done. Start RobotTask soon.")
            return

        # 비전 끝났으면 실제 pick&place 수행 후 타이머 끄기
        if self.mapping is not None:
            self.get_logger().info("Start pick and place")

            # 예: mapping 의 key 순서대로 실행
            for lid_idx, body_idx in self.mapping.items():
                # 슬롯 개수 체크 (혹시 인식 5개/3개 이상/이하 대비)
                if lid_idx >= len(self.lid_slots) or body_idx >= len(self.body_slots):
                    self.get_logger().warn(f"Index out of range: {lid_idx}, {body_idx}")
                    continue
                self.pick_and_place_one(lid_idx, body_idx)

            self.get_logger().info("All done. Stop timer.")
            self.timer.cancel()  # 더 이상 안 돈다


def main(args=None):
    rclpy.init(args=args)
    node = robotNode()

    # 시작할 때 로봇 initialize 한 번
    node.sendCommand('initialize')

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
