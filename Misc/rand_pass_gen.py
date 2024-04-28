
#!/usr/bin/env python3

from random import shuffle, choice
import string

charset = list(string.ascii_letters+string.digits+"!@#$%^&*()")

shuffle(charset)
# pass_len = input("enter length ")

# random no constraint password generate
def generate_pass(pass_len):

	password = [] 
	for _ in range(pass_len):
		password.append(choice(charset))
	shuffle(password)

	print("".join(password))

def gen_constrained_pass(pass_len):
	...

generate_pass(10)
