#!/bin/bash
#debug mode (enabled): set -xe
cc -o imgview imgview.c -lm

if [ "$1" == "r" ]; then 
	./imgview
else 
	printf "\e[48;5;23m[BUILD SUCCESSFUL]\e[0m\n"
fi
