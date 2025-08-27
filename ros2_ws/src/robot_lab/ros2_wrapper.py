#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import rclpy
import rclpy.executors
from rclpy.node import Node
from rcl_interfaces.msg import SetParametersResult
from mtlab_msgs.msg import BehaviorTreeCommand, BehaviorTreeStatus, Heartbeat

# force developers for specific implementation
from abc import ABC, abstractmethod

# utils
import yaml
import json
import threading
import time
import sys


class manipulatorNode(Node):
  available_actions = {}
  def __init__(self, node_name):
    super().__init__(node_name)
    self.node_name = node_name

    ## if functions can be run in parallel, use this group
    self._parallel_callback_group = rclpy.callback_groups.ReentrantCallbackGroup()
    ## if functions must be run in sequence, use this group
    self._sequential_callback_group = rclpy.callback_groups.MutuallyExclusiveCallbackGroup()

    # publishers
    # self._status_publisher = self.create_publisher(BehaviorTreeStatus, f'{node_name}/status', 1)

    # subscribers
    # self._command_subscriber = self.create_subscription(BehaviorTreeCommand,
    #                                                    f'{node_name}/command',
    #                                                    self._command_callback, 1)

    # for derived class
    self.add_on_set_parameters_callback(self._on_params_changed)

    # status publisher timer
    self._timers.append(self.create_timer(
      self.bt_server_config['status_publish_latency_seconds'],
      self._publish_status,
      callback_group=self._parallel_callback_group))
    self._timers.append(self.create_timer(
      self.bt_server_config['heartbeat_publish_latency_seconds'],
      self._publish_heartbeat,
      callback_group=self._parallel_callback_group))

    # multi-threaded executor
    self.my_executor = rclpy.executors.MultiThreadedExecutor(
      self.bt_server_config['num_executor_threads'])
    self.my_executor.add_node(self)

    self.initialized = False


  def _on_params_changed(self, params):
      for param in params:
            try:
              if isinstance(param.value, str):
                try:    data = json.loads(param.value)
                except: data = param.value
              else:
                data = param.value
              self.param[param.name] = data
            #   self._logger.info(f"[Parameter set] {param.name} = {self.param[param.name]}  (type: {type(self.param[param.name])})")
            except Exception as e:
              self._handle_bt_error(f'Failed to set parameter: {param.name}', str(e))
      self.on_params_changed()
      return SetParametersResult(successful=True, reason='Parameter set')


  # TODO: override this function in derived class
  def on_params_changed(self):
    pass


  def set_param(self, name, value):

      def check_param(value):
          if isinstance(value, bool):
              p_type = rclpy.Parameter.Type.BOOL
          elif isinstance(value, int):
              p_type = rclpy.Parameter.Type.INTEGER
          elif isinstance(value, float):
              p_type = rclpy.Parameter.Type.DOUBLE
          elif isinstance(value, str):
              p_type = rclpy.Parameter.Type.STRING
          else:
              value = json.dumps(value)
              p_type = rclpy.Parameter.Type.STRING
          return value, p_type

      if name not in self.param:
          if self.initialized:
              self._handle_bt_error('You must add subscriber before start_ros_thread()')
          ros_param_value, ros_param_type = check_param(value)
          self.declare_parameter(name, ros_param_value)
          self.param[name] = value
      else:
          ros_param_value, ros_param_type = check_param(value)
          self.set_parameters([rclpy.parameter.Parameter(name, ros_param_type, ros_param_value)])
          self.param[name] = value

      return self.param[name]


  def _handle_bt_error(self, msg: str='', msg_verbose: str=''):
    msg = f'BtServerNode caught an error: {msg}'
    if self.bt_server_config['verbose']:
      msg += f'\ndetail: {msg_verbose}'
    if self.on_failure_action == 'raise_value_error':
      raise ValueError(msg)
    else:
      self.get_logger().error(msg)


  def _publish_heartbeat(self):
    msg = self.get_heartbeat()
    self._heartbeat_publisher.publish(msg)

  def get_heartbeat(self):
    with self._heartbeat_lock:
      return self._current_heartbeat

  def set_heartbeat(self, heartbeat: int, content: str=''):
    with self._heartbeat_lock:
      self._current_heartbeat.heartbeat = heartbeat
      if content != '':
        self._current_heartbeat.content = content

  def start_ros_thread(self, async_spin=True):
    self.initialized = True
    print(f'core of bt server is initialized: {self.node_name}')
    if async_spin:
      self._start_spin_async()
    else:
      self._start_spin()

  def _start_spin_async(self):
    def run(executor):
      executor.spin()
    thr = threading.Thread(target=run, args=(self.my_executor,), daemon=True)
    thr.start()

  def _start_spin(self):
    self.my_executor.spin()

  @classmethod
  def available_action(cls, name):
    def decorator(func):
      cls.available_actions[name] = func
      print(f"Action registered: {name} -> {func.__name__}")
      return func
    return decorator

  def print_helper_functions(self):
    # print functions that are not start with _ or __ and defined in the current class, not in the parent class
    method_names = []
    for func in dir(self):
      if not callable(getattr(self, func)):
        continue
      if func not in dir(BehaviorTreeServerNode):
        continue
      if func in dir(Node):
        continue
      if func.startswith('_'):
        continue
      # check if func is abstract method
      if func in BehaviorTreeServerNode.__abstractmethods__:
        func += ' (implementation required)'
      method_names.append(func)
    print('implement your own class with using below functions - ')
    for f in method_names:
      print(f'  {f}')

  def _add_subscriber(self, msg_type, topic, callback, callback_group, qos=1):
    # you must consider race condition when handling async methods
    if self.initialized:
      self._handle_bt_error('You must add subscriber before start_ros_thread()')
    sub = self.create_subscription(
      msg_type,
      topic,
      callback,
      qos,
      callback_group=callback_group)
    self.subs[topic] = sub

  def get_subscriber(self, sub_topic_name):
    return self.subs.get(sub_topic_name)

  def add_async_subscriber(self, msg_type, topic, callback, qos=1):
    self._add_subscriber(msg_type, topic, callback, self._parallel_callback_group, qos)

  def add_sequential_subscriber(self, msg_type, topic, callback, qos=1):
    self._add_subscriber(msg_type, topic, callback, self._sequential_callback_group, qos)

  def add_async_timer(self, seconds, func):
    self._timers.append(self.create_timer(seconds, func, callback_group=self._parallel_callback_group))

  def add_sequential_timer(self, seconds, func):
    self._timers.append(self.create_timer(seconds, func, callback_group=self._sequential_callback_group))


  def _command_callback(self, msg: BehaviorTreeCommand): # this function has dependency on msg_id management
    if self._last_received_command_msg is not None:
      current_status = self.get_status()
      # assume msg_id is increasing
      if current_status is not None and current_status.msg_id >= msg.msg_id: # if already completed action
        return

    self._last_received_command_msg = msg

    args_json = json.loads(msg.args_json)

    self._is_current_status_updated = False

    action = args_json.pop('_action')

    available_action_names = BehaviorTreeServerNode.available_actions.keys()
    if action not in available_action_names:
      self._handle_bt_error(f'Invalid action: {action}')
      return
    self.get_logger().info(f'execute action: {action}')
    BehaviorTreeServerNode.available_actions[action](self, args_json)

    if self._is_current_status_updated == False:
      self._handle_bt_error(f'You must call set_status() in {action} function')

  def get_last_command(self) -> dict[str, any]:
    if self._last_received_command_msg is None:
      return None
    return json.loads(self._last_received_command_msg.args_json)

  def _publish_status(self):
    status = self.get_status()
    if status is None:
      return
    self._status_publisher.publish(status)

  def set_status(self,
                 task_status: int,
                 why: str='',
                 args_json:dict[str, any]={},
                 stamp: rclpy.time.Time=None) -> None:
    stamp = self.get_clock().now().to_msg() if stamp is None else stamp
    with self._status_lock:
      allowed_task_status = [
        BehaviorTreeStatus.TASK_STATUS_SUCCESS,
        BehaviorTreeStatus.TASK_STATUS_FAILURE,
        BehaviorTreeStatus.TASK_STATUS_RUNNING]
      if not task_status in allowed_task_status:
        raise ValueError('task_status must be belong to BehaviorTreeStatus.TASK_STATUS_XXX')

      self._current_status = BehaviorTreeStatus()
      self._current_status.header.stamp = stamp
      self._current_status.task_status = task_status
      self._current_status.msg_id = self._last_received_command_msg.msg_id
      self._current_status.why = why
      self._current_status.args_json = json.dumps(args_json)
      self._is_current_status_updated = True

  def get_status(self):
    with self._status_lock:
      return self._current_status


class BehaviorTreeClient(Node):
  def __init__(self, node_name):
    super().__init__(node_name)
    self.node_name = node_name
    self.last_status_msg = BehaviorTreeStatus()
    self.async_callback_group = rclpy.callback_groups.ReentrantCallbackGroup()
    self.my_executor = rclpy.executors.MultiThreadedExecutor(16)
    self.my_executor.add_node(self)
    self.pubs = {}
    self.subs = {}
    self.target_msg_id = 0
    self.print_result_only = True
    self.last_heartbeat_dict = {}

  def wait_heartbeat(self):
    while True:
      do_break = True
      for k, v in self.last_heartbeat_dict.items():
        print(f'{k}: {v}')
        if v != 0:
          do_break = False
          break
      if do_break:
        break
      self.my_executor.spin_once(timeout_sec=0.1)


  def enroll_node(self, node_name):
    if self.pubs.get(node_name) is not None:
      return
    self.last_heartbeat_dict[node_name] = -1

    self.pubs[node_name] = self.create_publisher(
      BehaviorTreeCommand,
      f'{node_name}/command',
      1)

    self.subs[node_name+'_status'] = self.create_subscription(
      BehaviorTreeStatus,
      f'{node_name}/status',
      self.status_callback,
      1,
      callback_group=self.async_callback_group)

    self.subs[node_name+'_heartbeat'] = self.create_subscription(
      Heartbeat,
      f'{node_name}/heartbeat',
      lambda msg: self.heartbeat_callback(msg, node_name),
      1,
      callback_group=self.async_callback_group)

    print(f'enroll_node: {node_name}')

  def send_command_and_wait(self, node_name: str,
                            action: str,
                            args_json_command: dict[str, any]={},
                            check_latency_ms: int=100,
                            print_result_only: bool =True):
    if self.pubs.get(node_name) is None:
      # i may call enroll_node here,
      # but it will result in inconsistent latency of 'send_command_and_wait' function
      # so i'll force developer to call enroll_node() first
      print('deny to send command: call enroll_node() first!')
      return
    print(f'call action({action} with args({args_json_command})')
    args_json_command['_action'] = action
    pub = self.pubs[node_name]

    self.last_status_msg.task_status = BehaviorTreeStatus.TASK_STATUS_RUNNING
    self.print_result_only = print_result_only

    self.target_msg_id = int(time.time()*1000) # id with millisecond
    print('msg_id: ', self.target_msg_id)
    msg_to_pub = BehaviorTreeCommand(
      msg_id=self.target_msg_id,
      args_json=json.dumps(args_json_command)
    )

    prev_ts = time.time()
    loop_latency_seconds = check_latency_ms/1000
    while self.last_status_msg.task_status == BehaviorTreeStatus.TASK_STATUS_RUNNING:
      pub.publish(msg_to_pub)
      self.my_executor.spin_once()
      current_ts = time.time()
      seconds_to_wait = loop_latency_seconds - (current_ts - prev_ts)
      if seconds_to_wait > 0:
        self.my_executor.spin_once(timeout_sec=seconds_to_wait)
      prev_ts = current_ts

    print('command is successfully executed, received status: ', self.last_status_msg.args_json)
    return json.loads(self.last_status_msg.args_json)

  def status_callback(self, msg):
    if self.target_msg_id != msg.msg_id:
      return
    self.last_status_msg = msg
    if not self.print_result_only:
      print('status received: ', msg)

  def heartbeat_callback(self, msg, node_name):
    self.last_heartbeat_dict[node_name] = msg.heartbeat
    print(f'[heartbeat_callback] {node_name}: {msg.heartbeat}')
    if not self.print_result_only:
      print('heartbeat received: ', msg)

class TestClass(BehaviorTreeServerNode):
  def __init__(self, node_name):
    super().__init__(node_name)
    self.print_helper_functions()

  def valid_command_callback(self, args_json: dict[str, any]):
    print('valid_command_callback: ', args_json)


class TestBTServerNode(BehaviorTreeServerNode):
  def __init__(self, node_name):
    super().__init__(node_name)
    self.print_helper_functions()
    self.start_ros_thread(async_spin=True)

  @BehaviorTreeServerNode.available_action('test_action')
  def test_action(self, args_json: dict[str, any]):
    print('run test_action: ', args_json)
    self.set_status(BehaviorTreeStatus.TASK_STATUS_SUCCESS)


if __name__ == '__main__':
  rclpy.init()

  server = TestBTServerNode('test_bt_server_node')
  client = BehaviorTreeClient('test_bt_client_node')
  client.enroll_node('test_bt_server_node')

  client.send_command_and_wait(
    'test_bt_server_node',
    'test_action')
