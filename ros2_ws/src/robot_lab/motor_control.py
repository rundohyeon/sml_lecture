#!/usr/bin/env python3
# client_set.py
import zmq, json, sys

RPI_IP = "192.168.1.9"   # 라즈베리파이 IP
PORT   = 5555


angle = 60.0
angle = 160.0

ctx = zmq.Context()
sock = ctx.socket(zmq.REQ)
sock.connect(f"tcp://{RPI_IP}:{PORT}")

print("before send")
sock.send_string(json.dumps({"cmd": "set", "angle_deg": angle}))
print(sock.recv_json())

