import sys
import rclpy
from rclpy.node import Node
from std_srvs.srv import Trigger
import time

class TriggerClient(Node):
    def __init__(self):
        super().__init__('Trigger_client')
        self.client = self.create_client(Trigger, 'attack')

        while not self.client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Service not available, waiting...')

        self.get_logger().info('You said "I love you"')
        node.get_logger().info(f'The answer was.. ')
        self.req = Trigger.Request()

    def call(self):
        return self.client.call_async(self.req)


def main(args=None):
    rclpy.init(args=args)
    node = TriggerClient()
    future = node.call()
    rclpy.spin_until_future_complete(node, future)

    if future.result() is not None:

        response = future.result()
        time.sleep(3)
        node.get_logger().info(f'"{response.message}"')
    else:
        node.get_logger().error('Service call failed')

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
