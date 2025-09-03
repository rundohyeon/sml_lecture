import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

for i in range(10):
   print(f"send req {i}")
   socket.send_string("hello")
   
   msg = socket.recv()
   print(f"received reply {msg}")
