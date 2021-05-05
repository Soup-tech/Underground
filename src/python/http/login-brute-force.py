#!/usr/bin/python3

import http.client
import urllib.parse

serv_ip = input("Host/IP: ")
serv_port = input("Port: ")
user_wordlist = input("Username Wordlist: ")
password_wordlist = input("Password Wordlist: ")

connection = http.client.HTTPConnection(serv_ip,serv_port)

for user in open(user_wordlist,'r'):
	user = user.strip()
	for password in open(password_wordlist, 'r'):
		password = password.strip()


		
		