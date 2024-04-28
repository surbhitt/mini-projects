
# morse code
# dits and dahs
# s

#!/usr/bin/env python -tt

ref =	{		
				"A" : ".-",
				"B" : "-...",
				"C" : "-.-.",
				"D" : "-..",
				"E" : ".",	
				"F" : "..-.",
				"G" : "--.",	
				"H" : "....",
				"I" : "..",	
				"J" : ".---",
				"K" : "-.-",	
				"L" : ".-..",
				"M" : "--",	
				"N" : "-.",
				"O" : "---",	
				"P" : ".--.",
				"Q" : "--.-",
				"R" : ".-.",
				"S" : "...",	
				"T" : "-",
				"U" : "..-",	
				"V" : "...-",
				"W" : ".--",	
				"X" : "-..-",
				"Y" : "-.--",	
				"Z" : "--..",
				"0" : "-----",	
				"1" : ".----",
				"2" : "..---",	
				"3"	: "...--",
				"4"	: "....-",	
				"5"	: ".....",
				"6"	: "-....",	
				"7"	: "--...",
				"8"	: "---..",	
				"9"	: "----.",
				"." : ".-.-.-",	
				"," : "--..--",
				"?" : "..--..",	
				"=" : "-...-",
				" " : "\t"
		}

# encryption
def enc():

	print('\tEnter the message(in uppercase): ')
	l = list(input("\t"))

	print("\n\t-input received is")
	print("\t", l)
	msg = ""
	for y in l:
		msg += " "
		for x in ref.keys():
			# print(x, y)
			if x == y:
				msg += ref[x]	
				break

	print("\n\t-encrypted:", msg)		

# decryption
def dec():

	print('\tEnter the message: ')
	l = [ y for y in input("\t").split() ]

	print("\n\t-input received is")
	print("\t", l)	
	msg = ""
	for y in l:
		for x in ref.values():
			if x == y:
				msg += list(ref.keys())[list(ref.values()).index(x)]
				break

	print("\n\t-decrypted:", msg)

# function main
def main():
	

	header = '''

	---------------------------
		___MorSE_._COdE___
			 '''					
	menu = '''

	> enter the option
	a. encode
	b. decode
	c. exit()

			'''

	# menu loop
	while 1:
		print(header)
		print(menu)

		opt = input('\t- ')

		if opt == "a" or opt == "A": enc()
		elif opt == "b" or opt == "B": dec()
		elif opt == "c" or opt == "C": 
			print("\n\thuba luba lu\n")
			exit()
		else: print("\tchoose one of the three")


if __name__=="__main__":
	main()		
	
	

	

	

