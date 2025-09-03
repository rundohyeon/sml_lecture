import zmq
import time

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
   msg = socket.recv()
   print(f"I received {msg}")
   
   time.sleep(1)

   socket.send_string("nice to meet you")
