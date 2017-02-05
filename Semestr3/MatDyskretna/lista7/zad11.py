def p(k, n, r):
	rn = r**n
	lm = rn / (((1-r)**n) - rn)
	return -lm + lm*(((1-r)/r)**k)


print(p(1, 100, 0.6))
