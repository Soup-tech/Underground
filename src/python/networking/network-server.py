#!/usr/bin/python3

import socket

serv_addr = input("Type the server IP address: ")
serv_port = int(input("Type the server port: "))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Building socket. AF_INET and SOCK_STREAM
s.bind((serv_addr,serv_port)) # Binding the socket with the addr and port
s.listen(1) # Listen, with backlog of 1
print("Server: Started")

connection, address = s.accept() 
while 1:
	data = connection.recv(1024)
	if not data: break
	connection.sendall(b"--- Message Received ---\n")
	print(data.decode('utf-8'))
connection.close()