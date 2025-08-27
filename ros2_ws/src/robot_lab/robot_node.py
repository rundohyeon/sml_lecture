import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import json
import math 
import transforms3d.euler as euler
import time

DEG2RAD = math.pi / 180.0
RAD2DEG = 180.0 / math.pi


class robotNode(Node):
    def __init__(self):
        super().__init__('robot_node')
        self.publisher_ = self.create_publisher(String, 'indyrp2_node/command', 10)

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

    def RobotTask(self):
        # initialize
        self.sendCommand('initialize')

        # # movej rel
        self.sendCommand("movej", 'rel', [-90.0, 0.0, 0.0, 0.0, 0.0, 0.0])

        # # movej abs
        self.sendCommand("movej", 'abs', [90.0, -25.0, 0.0, 115.0, 0.0, 90.0, 0.0])

        # # movel rel
        self.sendCommand("movel", 'tool', [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

        # # movel abs
        self.sendCommand("movel", 'base', [0.166, -0.460, 0.480, 0.0, 180.0, 90])



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