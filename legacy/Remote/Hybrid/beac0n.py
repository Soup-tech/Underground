#!/usr/bin/python3

# ======= Modules =======
import os
import sys
import socket

# ======= Variables =======
PORT = 1337

# ======= Main =======

if (os.fork() != 0):
	sys.exit(0)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.settimeout(5)

sock.bind(("localhost",PORT))
sock.listen(0)