n = 6
for i in range(4,101):
	n = n * i
	if(((i >= 4) & (i <=7 )) | (len(str(n)) % 100 > 20) &
	((len(str(n)) % 10 == 2) | (len(str(n)) % 10 == 3) | (len(str(n)) % 10 == 4)) ):
		print(str(i) + "! ma " + str(len(str(n))) + " cyfry")
	else:
		print(str(i) + "! ma " + str(len(str(n))) + " cyfr")
	
		
