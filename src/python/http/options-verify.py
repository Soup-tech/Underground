#!/usr/bin/python3

import http.client

host = input("Insert the host/IP: ")
port = input("Insert the Port: ")

if (port == ""):
	port = 80

try:
	connection = http.client.HTTPConnection(host,port)
	connection.request("OPTIONS","/")
	response = connection.getresponse()
	print("Enabled methods are: ",response.getheader('allow'))
	connection.close()
except ConnectionRefusedError:
	print("Connetion Failed")