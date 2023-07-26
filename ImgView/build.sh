#!/bin/bash
#debug mode (enabled): set -xe
cc -o imgview.out imgview.c -lm

if [[ $? -eq 0 ]]; then
	printf "\e[48;5;23m[BUILD SUCCESSFUL]\e[0m\n"
else
	printf "\e[48;5;196m[BUILD FAILED]\e[0m\n"
fi
