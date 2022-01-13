#!/usr/bin/env python3

import requests
import argparse
import sys
import re

class Scanner:
	def __init__(self,host,wordlist):
		self.host = host
		self.wordlist = wordlist

	def getHost(self):
		return self.host
	def getWordlist(self):
		return self.wordlist

	def bust(self):
		# Total lines in wordlist
		total_lines = len(open(self.wordlist).readlines())

		# Regex stuff here. Precompile for optimization
		wo_newline = re.compile(r'[a-zA-z0-9]+')

		# Begin directory busting webserver
		for number, line in enumerate(open(self.wordlist)):

			# Sanitize 
			pot = wo_newline.match(line)
			if pot is None: continue

			payload = createPayload(self.host, pot.group())
			
			r = requests.get(payload)
			if (r.status_code == 200): print(payload, end='\n')
			# Display progress
			progress = number / total_lines * 100
			print("{:.2f}%".format(progress), end='\r')


def parseArgs():
	"""
	Parse options for the scanner
	"""
	# Simple info about this tool
	switches = argparse.ArgumentParser(prog="bust1ng.py",description="Directory Busting")

	# Switches being considered below
	switches.add_argument('-u','--url',required=True,help="Host to be busted")
	switches.add_argument('-w','--wordlist',default='wordlists/directory-list-2.3-medium.txt',help="Wordlist to be used. Default is directory-list-2.3-medium.txt")
	switches.add_argument('-v','--version',action='version',version='%(prog)s 1.0')

	args = switches.parse_args()
	return args

def handleExceptions(host):
	# Check http at the start of host
	http = re.compile(r'http+')
	pot = http.match(host)
	if pot is None: host = f"http://{host}"

	# Check for forward slash at the end of host
	# TODO: Make it regex
	if host[-1] != '/': host = f"{host}/"

	return host

def createPayload(host, payload):
	return host + payload

args = parseArgs()
host = handleExceptions(args.url)
wordlist = args.wordlist

buster = Scanner(host, wordlist)

# Run scanner
buster.bust()