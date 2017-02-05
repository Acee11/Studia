from math import *
from time import *

def isPrime(n):
	for i in range(2,int(sqrt(n)),1):
		if(n%i == 0): return False
		
	return True
		
def isHyperLucky(n,m):
	nstr = str(n)
	licznik = 1
	if(len(nstr) < m): return False
	for i in range(0,len(nstr)-m+1,1):
		if(nstr[i] == '7'):
			licznik = 1
			while(licznik != m and nstr[i+licznik] == '7'):
				licznik += 1
			i += licznik - 1
			if(licznik == m): return True
				
	return False
		
		

counter = 0
i = 9999999999
a1 = time()
while(i >= 1000000000):
	if(isHyperLucky(i,7) and isPrime(i)):
		print(i)
		break
	i -= 2
	
a2 = time()

print(a2-a1)
		
