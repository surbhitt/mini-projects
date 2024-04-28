''' program to decode railfence cipher
	surbhit'''

#!/usr/bin/env python3 

msg = "Ta _7N6D8Dhlg:W3D_H3C31N__387ef sHR053F38N43DFD i33___N6"

vf1, vf2, vf3, vf4, vf2v, vf3v = 1, 2, 3, 4, 2, 4
length = len(msg)
print(length)

msgdic = {1 : msg[0]}

for x in range(2, 58):
	if vf1 + 6 <= length:
		vf1 += 6
		msgdic[vf1] = msg[x-1]
	elif vf2 <= length:
		msgdic[vf2] = msg[x-1]
		vf2v = 2 if vf2v == 4 else 4
		vf2 += vf2v
	elif vf3 <= length:
		msgdic[vf3] = msg[x-1]
		vf3v = 4 if vf3v == 2 else 2
		vf3 += vf3v
	elif vf4 <= length:
		msgdic[vf4] = msg[x-1]
		vf4 += 6
	else: print("EMPTY ENTER")	

print(msgdic)
sl = [value for key, value in sorted(msgdic.items())] # Note the () after items!
print("".join(sl))
print(len(sl))
print(len(msg))














# print({True: a, False: b}[a<b])
# type(var)