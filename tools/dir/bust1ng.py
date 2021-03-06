#!/usr/bin/env python3

import requests
import argparse
import sys
import re

aa = """
 /dfa#$$&%                         /E@    /@#
| $^___  $F                       | !$    |__/
| FV   \ *( /*&    /&*  /FEE#$%# /^$%RF#   /^$ /#%^faFC   /&#^27df 
| ^$%$@!34 | )(   | VD /#!_____/|_  J(_/  | (&| 1D__ j9  /8v__  !@
| V#___  !@| 2j   | !@|  (&*@!@   | !@    | !@| Z3  \ MI| #$  \ #$
| CD   \ D#| QX   | ^& \____  #$  | )# /!@| *f| fV  | #v| az  | (v
| $%GFV&#%/|  @#%FE!V/ /)!*!#&F/  |  (*#@/| @#| #%  | %F|  V3@#%!a
|________/  \_______/  |______/   \___/   |__/|__/  |__/ \___   V1
                                                         /!$ \  !c
                                                        |  $&#$!J/
                                                         \______/"""



class Scanner:
	def __init__(self,host,wordlist,filename,responseCodes,extensions):
		self.host = host
		self.wordlist = wordlist
		self.filename = filename
		self.responseCodes = responseCodes
		self.extensions = extensions

	def openHandler(self):
		self.outputFile = open(self.filename,'w')
		return

	def closeHandler(self):
		self.outputFile.close()
		return

	def handleResponse(self, payload, pot, response):

		if response.status_code in self.responseCodes:
			hit = f"/{pot : <20} (code: {response.status_code})"
			
			print(hit)

			# If output switch is set, write to a file
			if (filename):
				hit += '\n'
				self.outputFile.write(hit)

		return

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

			# Create entire url payload
			for ext in self.extensions:
				payload = createPayload(self.host, pot.group(), ext)
				
				# Make request
				response = requests.get(payload,allow_redirects=False)
				self.handleResponse(payload, pot.group() + ext, response)

				# Display progress
				progress = number / total_lines * 100
				print("{:.2f}%".format(progress), end='\r')

	def metaHeader(self):
		return f"+ Host: {self.host}\n+ Wordlist: {self.wordlist}\n+ Response Codes: {self.responseCodes}\n+ Extensions: {self.extensions}\n+ Output File: {self.filename}\n+ Version: Bust1ng v1.0"

def parseArgs():
	"""
	Parse options for the scanner
	"""
	# Simple info about this tool
	switches = argparse.ArgumentParser(prog="bust1ng.py",description="Directory Busting")

	# Switches being considered below
	switches.add_argument('-o','--output',help="Write to a file")
	switches.add_argument('-r','--response',default='200,301,302',help="Acceptable response codes. Default: 200,301,302")
	switches.add_argument('-u','--url',required=True,help="Host to be busted")
	switches.add_argument('-w','--wordlist',default='wordlists/directory-list-2.3-medium.txt',help="Wordlist to be used. Default is directory-list-2.3-medium.txt")
	switches.add_argument('-v','--version',action='version',version='%(prog)s 1.0')
	switches.add_argument('-x','--extensions',default='',help="Acceptable extensions")

	args = switches.parse_args()
	return args

def handleExceptions(host):
	"""
	Format host entire correct format
	"""
	# Check http at the start of host
	http = re.compile(r'http+')
	pot = http.match(host)
	if pot is None: host = f"http://{host}"

	# Check for forward slash at the end of host
	# TODO: Make it regex
	if host[-1] != '/': host = f"{host}/"

	return host

def createPayload(host, payload, ext):
	return host + payload + ext

def responseCodes(codes):
	code_list = [int(x) for x in codes.split(',')]
	return code_list

def acceptableExt(ext):
	# List of extensions
	if (',' in ext):
		ext = ['.'+x for x in ext.split(',')]
		ext.append('')
	# Single extension
	elif (ext is not None):
		ext = "." + ext
	return ext

# Parse arguments
args = parseArgs()

# Create parameters
host = handleExceptions(args.url)
wordlist = args.wordlist
filename = args.output
responseCodes = responseCodes(args.response)
extensions = acceptableExt(args.extensions)

# Create scanner object
buster = Scanner(host, wordlist, filename, responseCodes,extensions)

# Print ascii art and metadata of scan
print(aa)
meta = f"""
+================================================================+
{buster.metaHeader()}
+================================================================+
"""
print(meta)

# If an output file is specified
if filename is not None: buster.openHandler()

# Run scanner
buster.bust()
buster.closeHandler()