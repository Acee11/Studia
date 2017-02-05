def e(n):
	s = 0
	m = 1
	k = 1
	f = 1
	for i in range(n):
		s += m/k
		m = -m
		k *= f
		f += 1
	return s

print(e(10) - e(3))

