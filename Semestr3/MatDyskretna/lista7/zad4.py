from fractions import *

def a(n):
	m = 1 if n%2==0 else -1
	k = 3 * (2**(n-1))
	return Fraction(m,int(k)) + Fraction(1,3)

for i in range(10):
	print(a(i))