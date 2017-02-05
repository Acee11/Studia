from math import *
from time import *

def isPrime(n):
	for i in range(2,int(sqrt(n)),1):
		if(n%i == 0): return False
		
	return True
		
def isLucky(n):
	nstr = str(n)
	if(len(nstr) < 3): return False
	for i in range(0,len(nstr)-2,1):
		if(nstr[i] == '7' and nstr[i +1] == '7' and nstr[i + 2] == '7'): return True
	return False
		
		
counter = 0
	
for i in range(100,100001,1):
	if(isPrime(i) and isLucky(i)):
		print(i)
		counter += 1
		
print(counter)

if(isPrime(9)): print('a')
	
