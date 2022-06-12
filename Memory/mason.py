#!/usr/bin/env python3

import random
import argparse

def generateSeq(length):
	num = [str(random.randint(0,9)) for i in range(length)]
	return "".join(num)

def parseArgs():
	switches = argparse.ArgumentParser(prog="mason.py", description="The numbers Mason, what do they mean!?")

	switches.add_argument('-l','--length',required=True,help="Length of the sequence")
	args = switches.parse_args()

	return args

args = parseArgs()
length = int(args.length)

s = generateSeq(length)
print(s)