import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

# from vision_msgs.msg import Detection2DArray, Detection2D, ObjectHypothesisWithPose, BoundingBox2D
import torch
from torchvision import models, transforms
from PIL import Image

import json
import math 
import time
import numpy as np

from std_msgs.msg import String
from sensor_msgs.msg import Image, CameraInfo

import cv2
from cv_bridge import CvBridge
from geometry_msgs.msg import PoseArray, Pose

import transforms3d.euler as euler
from message_filters import Subscriber, ApproximateTimeSynchronizer


DEG2RAD = math.pi / 180.0
RAD2DEG = 180.0 / math.pi


class robotNode(Node):
    def __init__(self):
        super().__init__('robot_node')
        self.publisher_ = self.create_publisher(String, 'indyrp2_node/command', 10)

        # ---- Parameters ----
        self.declare_parameter('color_topic', '/camera/camera/color/image_raw')
        self.declare_parameter('depth_topic', '/camera/aligned_depth_to_color/image_raw')
        self.declare_parameter('camera_info_topic', '/camera/camera/color/camera_info')
        self.declare_parameter('conf', 0.35)
        self.declare_parameter('imgsz', 640)
        self.declare_parameter('device', 'auto')          # 'auto'|'cpu'|'cuda:0'
        self.declare_parameter('roi_frac', 0.2)
        self.declare_parameter('publish_annotated', True)

        # ---- Read params ----
        color_topic = self.get_parameter('color_topic').get_parameter_value().string_value
        depth_topic = self.get_parameter('depth_topic').get_parameter_value().string_value
        info_topic  = self.get_parameter('camera_info_topic').get_parameter_value().string_value

        self.conf   = float(self.get_parameter('conf').value)
        self.imgsz  = int(self.get_parameter('imgsz').value)
        self.roi_frac = float(self.get_parameter('roi_frac').value)
        self.publish_annotated = bool(self.get_parameter('publish_annotated').value)

        # ---- Device select (auto) ----
        device_req = self.get_parameter('device').get_parameter_value().string_value
        if device_req == 'auto':
            self.device = 'cuda:0' if torch.cuda.is_available() else 'cpu'
        else:
            self.device = device_req
        self.get_logger().info(f'Using device: {self.device}')

        # ---- QoS for sensor data ----
        sensor_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=5,
            durability=DurabilityPolicy.VOLATILE
        )

        self.bridge = CvBridge()

        # ---- YOLO (COCO) ----
        self.model = YOLO('yolov8n.pt')
        self.model.fuse()
        # names: dict {class_id: class_name}
        names = self.model.names if isinstance(self.model.names, dict) else {i: n for i, n in enumerate(self.model.names)}
        tb_list = [i for i, n in names.items() if n == 'toothbrush']
        if not tb_list:
            raise RuntimeError('This YOLO model does not include "toothbrush" class.')
        self.tb_idx = int(tb_list[0])
        self.get_logger().info(f'toothbrush class index = {self.tb_idx}')

        # ---- Publishers ----
        self.pub_det2d = self.create_publisher(Detection2DArray, 'toothbrush/detections_2d', 10)
        self.pub_pose_array = self.create_publisher(PoseArray, 'toothbrush/poses', 10)
        self.pub_annot = self.create_publisher(Image, 'toothbrush/annotated', 10) if self.publish_annotated else None

        # ---- Subscribers (no message_filters) ----
        self.sub_color = self.create_subscription(
            Image, color_topic, self.cb_color, sensor_qos
        )
        self.sub_depth = self.create_subscription(
            Image, depth_topic, self.cb_depth, sensor_qos
        )
        self.sub_info = self.create_subscription(
            CameraInfo, info_topic, self.cb_info, sensor_qos
        )

        # ---- Subscribers ----


        self.last_log_t = time.time()
        self.robot_status = 'Idle'




    @staticmethod
    def _depth_to_meters(depth_val, dtype):
        if np.isnan(depth_val):
            return np.nan
        # RealSense 기본: 16UC1(mm). 32FC1이면 이미 미터.
        return float(depth_val) * 0.001 if dtype == np.uint16 else float(depth_val)

    def cb(self, img_msg: Image, depth_msg: Image, info_msg: CameraInfo):
        print("??")
        # --- Decode images ---
        color = self.bridge.imgmsg_to_cv2(img_msg, desired_encoding='bgr8')
        depth = self.bridge.imgmsg_to_cv2(depth_msg, desired_encoding='passthrough')  # keep dtype

        h, w = color.shape[:2]
        fx = info_msg.k[0]; fy = info_msg.k[4]; cx = info_msg.k[2]; cy = info_msg.k[5]

        # --- YOLO inference (only toothbrush) ---
        results = self.model.predict(source=color, imgsz=self.imgsz, conf=self.conf,
                                     classes=[self.tb_idx], device=self.device, verbose=False)

        det_array = Detection2DArray(); det_array.header = img_msg.header
        poses = PoseArray(); poses.header = img_msg.header
        annotated = color.copy()

        for r in results:
            if r.boxes is None or len(r.boxes) == 0:
                continue
            for b in r.boxes:
                xyxy = b.xyxy[0].tolist()
                score = float(b.conf[0].item())
                x1,y1,x2,y2 = [int(max(0,min(v, w-1 if i%2==0 else h-1))) for i,v in enumerate(xyxy)]
                bw, bh = (x2-x1), (y2-y1)
                if bw <= 1 or bh <= 1:
                    continue

                # 중앙 ROI (박스 중심 기준)
                cx_pix = x1 + bw/2.0; cy_pix = y1 + bh/2.0
                rx = max(1, int(bw*self.roi_frac/2.0)); ry = max(1, int(bh*self.roi_frac/2.0))
                rx1, rx2 = int(max(0, cx_pix - rx)), int(min(w-1, cx_pix + rx))
                ry1, ry2 = int(max(0, cy_pix - ry)), int(min(h-1, cy_pix + ry))
                roi = depth[ry1:ry2+1, rx1:rx2+1]

                # 유효 깊이만 추출 (0 또는 NaN 제외)
                roi_flat = roi.reshape(-1)
                if roi.dtype == np.uint16:
                    valid = roi_flat[roi_flat > 0]
                else:  # float32
                    valid = roi_flat[~np.isnan(roi_flat)]
                if valid.size == 0:
                    # 깊이 실패: 2D만 퍼블리시
                    self._publish2d(det_array, img_msg, x1,y1,x2,y2, score, b.cls[0].item())
                    continue

                Z = np.median(valid)
                Zm = self._depth_to_meters(Z, roi.dtype)

                # 백프로젝션 (camera color optical frame, x:right, y:down, z:forward)
                X = (cx_pix - cx) / fx * Zm
                Y = (cy_pix - cy) / fy * Zm

                # 2D detection
                self._publish2d(det_array, img_msg, x1,y1,x2,y2, score, b.cls[0].item())

                # PoseArray (orientation 없음 → identity)
                p = Pose()
                p.position.x = X; p.position.y = Y; p.position.z = Zm
                p.orientation.w = 1.0
                poses.poses.append(p)

                # Annotated image
                cv2.rectangle(annotated, (x1,y1), (x2,y2), (0,255,0), 2)
                cv2.putText(annotated, f"toothbrush {score:.2f}",
                            (x1, max(0,y1-5)), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0,255,0), 2)
                txt = f"X:{X:.3f} Y:{Y:.3f} Z:{Zm:.3f} m"
                cv2.putText(annotated, txt, (x1, y2+18), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0,255,0), 2)


        # publish
        self.pub_det2d.publish(det_array)
        if len(poses.poses) > 0:
            self.pub_pose_array.publish(poses)

        if self.pub_annot is not None:
            out = self.bridge.cv2_to_imgmsg(annotated, encoding='bgr8')
            out.header = img_msg.header
            self.pub_annot.publish(out)

            
        if time.time() - self.last_log > 2.0:
            self.get_logger().info(f"2D dets: {len(det_array.detections)}, 3D points: {len(poses.poses)}")
            self.last_log = time.time()

    def _publish2d(self, det_array, header_src, x1,y1,x2,y2, score, cls_id):
        det = Detection2D()
        det.header = header_src
        bbox = BoundingBox2D()
        bbox.center.position.x = x1 + (x2-x1)/2.0
        bbox.center.position.y = y1 + (y2-y1)/2.0
        bbox.size_x = float(x2-x1); bbox.size_y = float(y2-y1)
        det.bbox = bbox
        hyp = ObjectHypothesisWithPose()
        hyp.id = str(int(cls_id)); hyp.score = float(score)
        det.results.append(hyp)
        det_array.detections.append(det)



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
        # # # initialize
        print("initialize")
        # self.sendCommand('initialize')

        # self.sendCommand("movej", 'abs', [-146.4, -42.58, -0.68, -109.37, 0.99, -28.09, -57.7])
        # time.sleep(4)

        # # move to battery origin pose
        # self.sendCommand("movej", 'abs', [-152.36, -54.32, 0.63, -92.00, -0.91, -33.88, -61.12])

        # # approach to battery
        # self.sendCommand("movel", 'tool', [0.0, 0.0, 0.048, 0.0, 0.0, 0.0])

        # # grasp   
        # self.sendCommand("gripper", 'close')

        # # pick up battery
        # self.sendCommand("movel", 'tool', [0.0, 0.0, -0.048, 0.0, 0.0, 0.0])

        # # move to battery new pose
        # self.sendCommand("movel", 'base_abs', [-0.489, -0.280, 0.0445, 180, 0, 90])

        # # ##Student









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