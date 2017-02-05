

def dodaj(L1,L2):
	carry = 0
	res = []
	
	if len(L1) > len(L2):
		L1r = list(reversed(list(L1)))
		L2r = list(reversed(list(L2)))
	else:
		L1r = list(reversed(list(L2)))
		L2r = list(reversed(list(L1)))
		
	for i in range(len(L1r)):
		carry += L1r[i]
		if i<len(L2r):
			carry += L2r[i]
		res.append(carry%10)
		carry /= 10
		
	if carry!=0:
		res.append(carry)
		
	res.reverse()
	return res
	
R = [1,2,3]
S = [7,7]

print dodaj(R,S)
		
