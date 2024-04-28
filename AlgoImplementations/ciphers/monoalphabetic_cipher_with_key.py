# monoalphabetic cipher with key

key = "EKSZJTCMXOQUDYLFABGPHNRVIW "

msg = '''fxslSPT{5HK5717H710Y_3N0UH710Y_59533E2J}'''
dict = {}
a =""
for x in msg:
	for idx, y in enumerate(key):
		if x.isalpha():
			if x.lower() == y.lower():
				a += chr(65+idx)
		else:
			a += x
			break

print(a)