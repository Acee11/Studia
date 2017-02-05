def szachownica(n,k):
	szach1 = n * (k * ' ' + k * '*')
	szach2 = n * (k * '*' + k * ' ')

	for i in range(2*n):
		if(i % 2 == 0):
			for j in range(k):
				print(szach1)
		else:
			for j in range(k):
				print(szach2)
			
szachownica(4,3)