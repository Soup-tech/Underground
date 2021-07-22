#!/usr/bin/python3

import socket

serv_ip = input("Type in the IP address of the server: ")
serv_port = int(input("Type in the port listening on the server: "))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((serv_ip, serv_port))

print("Connected to Server")

while 1:
	send_message = input("> ")
	b_message = bytes(send_message, 'utf-8')
	s.send(b_message)

s.close()