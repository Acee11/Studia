def analizaCollatza(a,b):
	j = 0
	srednia = 0
	mediana = 0
	energyList = []
	
	if(a>b)
		c=b
		b=a
		a=c
	
	for i in range(a,b+1,1):
		energyList.append(energy(i))
		j += 1
		
	maxEn = energyList[0]
	minEn = energyList[0]
		
	for i in range(j):
		srednia += energyList[i]
		
		if(energyList[i] > maxEn):
			maxEn = energyList[i]
		
		if(energyList[i] < minEn):
			minEn = energyList[i]
			
	srednia /= float(j)
	
	if(j%2):
		mediana = energyList[j/2]
	else:
		mediana = (energyList[j/2] + energyList[j/2-1])/2.0
		
	print("Srednia energia: ",srednia)
	print("Mediana energii: ",mediana)
	print("Energia maksymalna: ",maxEn)
	print("Energia minimalna: ",minEn)
	
	
	
def energy(n):
	pos = 0
	while(n != 1):
		pos += 1
		n = F(n)
	return pos

def F(n):
	if(n%2 == 0):
		return n/2;
	else:
		return n * 3 + 1
		

		
a = input()
b = input()
analizaCollatza(a,b)