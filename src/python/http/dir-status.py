#!/usr/bin/python3

import http.client

serv_addr = input("What is the host/IP: ")
port_addr = input("What is the port: ")
wordlist = input("Wordlist: ")

if (port_addr == ""):
	port_addr = 80

for directory in open(wordlist, 'r',encoding='utf-8'):
	directory = directory.strip()

	try:
		connection = http.client.HTTPConnection(host, port)
		connection.request("GET","/"+directory)
		
		if (connection.status == 200):
			print("/"+directory)
	except:
		pass