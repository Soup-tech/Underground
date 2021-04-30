#!/usr/bin/python3

# using connect_ex() rather than connect(). connect_ex() returns 0 if the operation succeeded; otherwise it returns an error code

import socket

serv_ip = input("Target IP: ")


for port in range(65535):
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	status = s.connect_ex((serv_ip,port))

	if (status == 0):
		print("Port:",port,"is open")

	s.close()