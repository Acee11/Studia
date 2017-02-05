c = 0.5
def f(x):
	x0 = 0.7
	for i in range(0,x):
		x0 = x0 * (2 - c * x0)
		print(x0)

f(10)


