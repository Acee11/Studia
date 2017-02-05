def f(n):
	s = 0
	for i in range(n+1):
		if((i%3 == 0 or i%2 == 0) and i%5 != 0 and i%7 != 0):
			s += 1
	return s
def g(n):
	A = n//2 - n//10 - n//14 + n//70
	B = n//3 - n//15 - n//21 + n//105
	AnB = n//6 - n//30 - n//42 + n//210
	return A + B - AnB

for i in range(10000):
	if(f(i) != g(i)):
		print(i)




