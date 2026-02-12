#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

import json
import time
import math
import serial
import sys

# =========================
# Arduino Serial 설정
# =========================
ARDUINO_PORT = "/dev/ttyUSB0"
ARDUINO_BAUD = 115200


# =========================
# ROS2 Job Node
# =========================
class JobJJNode(Node):
    def __init__(self):
        super().__init__('job_jj_node')

        # ROS publisher (robot command)
        self.publisher_ = self.create_publisher(
            String,
            'indyrp2_node/command',
            10
        )

        # Arduino Serial 연결
        self.arduino = None
        self._init_arduino()

    # -------------------------
    # Arduino Serial Init
    # -------------------------
    def _init_arduino(self):
        try:
            self.arduino = serial.Serial(
                ARDUINO_PORT,
                ARDUINO_BAUD,
                timeout=1
            )
            # Arduino는 시리얼 연결 시 리셋됨 → 대기
            time.sleep(2.0)
            self.get_logger().info(
                f"Arduino connected: {ARDUINO_PORT}"
            )
        except Exception as e:
            self.get_logger().error(
                f"Arduino connection failed: {e}"
            )
            self.arduino = None

    # -------------------------
    # Conveyor Control (Serial)
    # -------------------------
    def conveyor_move(self, direction: str, duration: float):
        """
        direction: 'in' or 'out'
        duration: seconds (float)
        """
        if self.arduino is None:
            self.get_logger().warn("Arduino not connected")
            return

        direction = direction.lower()
        if direction not in ("in", "out"):
            self.get_logger().error(
                "direction must be 'in' or 'out'"
            )
            return

        if duration <= 0.0:
            self.get_logger().error(
                "duration must be > 0"
            )
            return

        cmd = f"MOVE {direction} {duration}\n"
        self.arduino.write(cmd.encode("utf-8"))
        self.get_logger().info(
            f"[CONVEYOR] {cmd.strip()}"
        )

    def conveyor_stop(self):
        if self.arduino is None:
            self.get_logger().warn("Arduino not connected")
            return

        self.arduino.write(b"STOP\n")
        self.get_logger().info("[CONVEYOR] STOP")

    # -------------------------
    # Robot Command Publisher
    # -------------------------
    def send_command(self, cmd, mode="", coord=None):
        if coord is None:
            coord = []

        command = {
            "cmd": cmd,
            "mode": mode,
            "coord": coord
        }

        msg = String()
        msg.data = json.dumps(command)

        self.publisher_.publish(msg)
        self.get_logger().info(
            f"[ROBOT CMD] {msg.data}"
        )

    # -------------------------
    # Main Job Sequence
    # -------------------------
    def run_job(self):
        # 1) 로봇 initialize (posj.home으로 이동)
        self.send_command("initialize")
        time.sleep(2.0)

        # 2) 컨베이어 IN 방향으로 5초
        self.conveyor_move("in", 2.0)
        time.sleep(5.5)   # Arduino에서 duration 처리 안 하면 Python에서 대기

        # 3) 컨베이어 정지
        self.conveyor_stop()
        time.sleep(1.0)

        # 4) 로봇 대기자세로 이동
        self.send_command(
            "movej",
            "abs",
            [-130.62, -28.78, -28.65, -84.82, 10.78, -61.28, 73.41]
        )
        time.sleep(2.0)

        # # poly mailer height (double)
        # self.send_command(
        #     "movej",
        #     "abs",
        #     [-132.11, -45.59, -44.59, -80.22, 30.47, -65.36, 73.41]
        # )
        # time.sleep(2.0)        

        # # box height
        # self.send_command(
        #     "movej",
        #     "abs",
        #     [-132.14, -39.29, -35.53, -80.32, 22.16, -67.2, 73.41]
        # )
        # time.sleep(4.0)

        #mailer plus box height
        self.send_command(
            "movej",
            "abs",
            [-132.45, -36.19, -37.10, -85.04, 23.27, -64.01, 73.41]
        )
        time.sleep(4.0)

        # up
        self.send_command(
            "movej",
            "abs",
            [-131.45, -20.79, -28.08, -79.14, 10.49, -77.93, 73.41]
        )
        time.sleep(4.0)

        # go to right
        self.send_command(
            "movej",
            "abs",
            [-141.26, -24.86, -74.58, -80.06, 23.35, -84.9, 73.41]
        )
        time.sleep(4.0)

        # 4) 로봇 대기자세로 이동
        self.send_command(
            "movej",
            "abs",
            [-130.62, -28.78, -28.65, -84.82, 10.78, -61.28, 73.41]
        )
        time.sleep(2.0)

        # single mailer height
        self.send_command(
            "movej",
            "abs",
            [-130.82, -45.25, -41.62, -79.86, 29.43, -65.37, 73.41]
        )
        time.sleep(4.0)

        # up
        self.send_command(
            "movej",
            "abs",
            [-131.45, -20.79, -28.08, -79.14, 10.49, -77.93, 73.41]
        )
        time.sleep(4.0)

        # go to right
        self.send_command(
            "movej",
            "abs",
            [-141.26, -24.86, -74.58, -80.06, 23.35, -84.9, 73.41]
        )
        time.sleep(4.0)

        # # 5) TCP 기준 Z축으로 10 mm 이동
        # self.send_command(
        #     "movel",
        #     "tool",
        #     [0.0, 0.0, 0.01, 0.0, 0.0, 0.0]
        # )

        self.get_logger().info("Job finished")


# =========================
# main
# =========================
def main():
    rclpy.init()

    node = JobJJNode()

    try:
        node.run_job()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if node.arduino is not None:
            node.arduino.close()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
