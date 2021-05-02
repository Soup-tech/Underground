#!/usr/bin/python3

import socket
import os

def main():
    serv_addr = input("Server IP: ")
    serv_port = int(input("Server Port: "))

    client(serv_addr, serv_port)

def client(serv_addr, serv_port):

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((serv_addr,serv_port))
	print("Connected to Server...")

	while 1:
	    send_message = input("> ")
	    b_message = bytes(send_message, 'utf-8')
	    s.send(b_message)



if __name__ == "__main__":
    main()
