from sets import Set
from math import *

def sumy1(L,S):
	S.add(sum(L))
	for i in range(len(L)):
		L1 = list(L)
		del L1[i]
		sumy1(L1,S)
	return S
	
def kombinacje(a,b,n):
	if n == 1:
		return [[i] for i in range(a,b+1)]
	return [[i] + j for i in range(a,b+1) for j in kombinacje(i,b,n-1)]

		
	
#10,9,8,7,6,5
a = [1,2,3]
b = [[7,8,9]]
print kombinacje(1,3,3)
