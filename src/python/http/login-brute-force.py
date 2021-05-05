#!/usr/bin/python3

import http.client
import urllib.parse
import sys


def main():
	if (len(sys.argv) == 3):
		print("Usage: ./login-brute-force [user wordlist] [password wordlist]")
		exit(1)

	serv_host = input("host/IP : ")
	serv_port = input("port : ")

	lst = serv_host.split("/")

	if (len(lst) < 3):
		url = '/'
	else:
		url = extension(serv_host)	

	print(url)	
	serv_ip = serv_host[2]

	# check if server is up
	connection = http.client.HTTPConnection(host, serv_port)
	connection.request('GET','/')	
	pirnt(connection.status)


	# Drive loop
	#for user in open(sys.argv[1], 'r', encoding='utf-8'):
	#	user = user.strip()
	#	for password in open(sys.argv[2], 'r' encoding='utf-8'):
	#		password = password.strip()


def extension(serv_host):
	lst = serv_host.split('/')
	url = "/" + "/".join(lst[3:])
	return url




if __name__=="__main__":
	main()