#!/bin/bash

#
# Find all files within a directory that matches the specified file type.
#

all=$(find . *)

for i in $all;
do
	filetype=$(file $i | cut -d ':' -f 2 | grep -i $1 2> /dev/null)
	grepped=$(echo $filetype | grep -i $1 2> /dev/null)
	
	if [[ $grepped ]]; then
		echo "$i: $grepped"
	fi
done
