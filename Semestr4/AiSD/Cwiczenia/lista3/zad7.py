def P(k):
	return 0.5**(2**(k-1) * k)

for i in range(1,5):
	print(i,P(i))