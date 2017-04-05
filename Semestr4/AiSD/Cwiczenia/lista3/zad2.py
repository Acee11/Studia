from numpy.random import randint

def min_max(A):
	n = len(A)
	if n == 1:
		return (A[0],A[0],0)
	else:
		if n == 2:
			a1, a2 = A[0], A[1]
			if a1 < a2:
				a1, a2 = a2, a1
			return (a1, a2, 1)
		else:
			(max1, min1, r1) = min_max(A[:n//2])
			(max2, min2, r2) = min_max(A[n//2:])
			w_max = max1 if max1 >= max2 else max2
			w_min = min1 if min1 <= min2 else min2
			return (w_max, w_min, r1 + r2 + 2)


n = 129
k = (3*n)//2 - 2
A = randint(0, 100000, n)

for i in range(100000, 100000000):
	k1 = min_max(randint(0, 100000, i))[2]
	print(k1/((3*i)//2-2))
	#if k1 == (3*i)//2 - 2:
	#	print(i)
