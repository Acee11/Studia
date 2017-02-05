from itertools import permutations
def sswap(c, i, j):
	c = list(c)
	c[i], c[j] = c[j], c[i]
	return ''.join(c)


def hamilton(s, V, n):
	if(len(V) == n):
		return V
	for i in range(len(s)-1):
		if s[i] != s[i+1]:
			sn = sswap(s, i, i+1)
			if sn not in V:
				H = hamilton(sn,V + [sn],n)
				if H is not None:
					return H



s = 'aaabbb'
print(hamilton(s, [s], 20))

print()



for s in set(permutations('abcccc')):
	h = hamilton(''.join(s), [''.join(s)], 30)
	if h is not None:
		print(h)
