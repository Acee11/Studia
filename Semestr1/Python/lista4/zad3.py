from random import *
from time import *

def randperm(n):
	L = range(n)
	
	for i in range(n,1,-1):
		r = randint(0,i-1)
		buf = L[i-1]
		L[i-1] = L[r]
		L[r] = buf
		
	return L
	
a1 = time()
x = randperm(500)
a2 = time()
print(a2-a1)
print(x)
		