import rclpy
from rclpy.node import Node
from std_srvs.srv import Trigger
import time

class TriggerService(Node):
    def __init__(self):
        super().__init__('trigger_service')
        
        self.get_logger().info('you are a server')
        self.srv = self.create_service(Trigger, 'attack', self.cb)
        self.get_logger().info('')

    def cb(self, request, response):
        self.get_logger().info(f"you received a service from the client")
        response.success = True
        response.message = "Hello, client"

        return response


def main(args=None):
    rclpy.init(args=args)
    node = TriggerService()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()


