from functools import reduce

def s(n):
	a = 0
	t = 4
	for k in range(2,n+1):
		a += t*k*(k-1)
		t *= 2
	return a

def f(n):
	return (2**(n+2)) * (((n*(n-1))/2) - n + 2) - 8


for i in range(2,10):
	print(f(i))

for i in range(2,10):
	print(s(i))