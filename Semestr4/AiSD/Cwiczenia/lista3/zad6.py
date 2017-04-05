from math import ceil
import numpy as np

def median3(a, b, c):
	return sorted([a,b,c])[1]

def arr_median2(Arr):
	A = Arr[0]
	B = Arr[1]
	n_a = len(A)
	n_b = len(B)

	if(n_a == 2):
		return median3(A[0], A[1], B[ceil(n_b//2)-1])


	medA = A[ceil(n_a//2)-1]
	medB = B[ceil(n_b//2)-1]

	if(medA > medB):
		A,B = B,A
		n_a, n_b = n_b, n_a
	cut = min(n_a//2, n_b - n_b//2 - 1)
	A = A[cut:]
	B = B[:n_b-cut]
	if(len(A) > len(B)):
		A,B = B,A
	return arr_median2([A, B])



def arr_median3(Arr):
	A = Arr[0]
	B = Arr[1]
	C = Arr[2]
	n_a = len(A)
	n_b = len(B)
	n_c = len(C)
	if(n_a == 2):
		return median3(A[0], A[1], arr_median2([B,C]))

	medA = A[ceil(n_a//2)-1]
	medB = B[ceil(n_b//2)-1]
	medC = C[ceil(n_c//2)-1]

	perm = np.argsort(np.array([medA, medB, medC]))
	Arr1 = [None, None, None]
	Arr1[0] = Arr[perm[0]]
	Arr1[1] = Arr[perm[1]]
	Arr1[2] = Arr[perm[2]]
	A = Arr1[0]
	B = Arr1[1]
	C = Arr1[2]
	n_a = len(A)
	n_b = len(B)
	n_c = len(C)

	cut = min(n_a//2, n_c - n_c//2 - 1)
	print([A[cut:], B, C[:n_c-cut]])
	return arr_median3([A[cut:], B, C[:n_c-cut]])

	

#print(arr_median2([[1,2,3],[2,10]]))
print(arr_median3([[1,2,10],[3,5,6],[1,2,3]]))