#!/usr/bin/python3

import requests
import sys

def main():
	if ( (len(sys.argv) < 4) or ('-h' in sys.argv)):
		usage()
		exit(0)

	if ('-d' in sys.argv):
		index = sys.argv.index('-d')
		form_data = sys.argv[index + 1]
		form_data = form_data.split(',')

		info = {}
		for key in range(len(form_data)):
			value = input(form_data[key] + ': ')
			info[form_data[key]] = value


	response = requests.post(sys.argv[1], data=info).text
	print(response)



def usage():
	print("Usage: " + sys.argv[0] + "[URL] -u [User Worldist] -p [Password Wordlist]\n" +
		  "Options:\n" + 
		  "\t-u\t: Username Wordlist\n" +
		  "\t-p\t: Password Wordlist\n" + 
		  "\t-h\t: Display this Help Message\n" +
		  "\t-d\t: Keys in the Body of the POST statement. Seperate using commas (ex: cookie,query,user,password).\n")


if __name__=="__main__":
	main()