#!/usr/bin/python3 

import socket

serv_addr = '127.0.0.1'
serv_port = 8080

while 1:

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind((serv_addr, serv_port))
	s.listen(1)
	print("Server Started")

	connection, address = s.accept()
	while 1:
		data = connection.recv(1024)
		if not data: break
		if '\r\n' in data:
			break

	connection.close()