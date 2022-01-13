#!/usr/bin/python3

import requests
from bs4 import BeautifulSoup


def main():
	
	# Preliminary data
	url = 'http://172.16.120.120/'
	req = requests.get(url)
	soup = BeautifulSoup(req.text, 'html.parser')

	tr_tags = soup.find_all('tr')
	
	print(tr_tags)
	for tr in tr_tags:
		print(tr.attrs)


if __name__ == "__main__":
	main()