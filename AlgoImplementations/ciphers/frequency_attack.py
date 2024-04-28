# frequency attack

#!/usr/bin/env python3
from string import ascii_lowercase

#empty dictionary for the msg letter frequency analysis
msg_freq = {a:0 for a in ascii_lowercase}
#english letter freq sorted in descending order
eng_freq = 'ETAOINSHRDLCUMWFGYPBVKJXQZ'.lower()
decrypted_msg = ''

with open('message.txt', 'r') as f:
	for x in f.read():
		# print(x)
		if x.isalpha():
			msg_freq[x.lower()]+=1
print(" _the message is_______ ")
with open('message.txt', 'r') as f:
	for x in f.readlines():
		print(x)
print(" \nthe result for the frequency analysis is \n", msg_freq)			

msg_freq = sorted(msg_freq.items(), key = lambda x : x[1], reverse = True)

print("the result for sorted frequency analysis is \n", msg_freq)	
trans_msg = {}

for x in range(len(msg_freq)):
	trans_msg[msg_freq[x][0]] = x

with open('message.txt', 'r') as f:
	for y in f.read():

		if y.isalpha():	
			decrypted_msg += eng_freq[trans_msg[y.lower()]]
		else:
			decrypted_msg += y

print("\n _final decrypted msg_______")
print(decrypted_msg)			

