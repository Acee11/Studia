# -*- encoding: utf8 -*-
from sets import Set
from itertools import *
napis = "ciacho + ciacho = nadwaga"
	
def perm(L, n):
	if n == 1:
		return [[i] for i in L]
	return [[L[i]]+b for i in range(len(L)) for b in perm(L[:i]+L[i+1:],n-1)]
	
def sprawdz(a,b,c,kod):
	for i in range(len(a)):
		a[i] = kod[a[i]]
		b[i] = kod[b[i]]
		c[i] = kod[c[i]]
	if c[-1] in kod:
		c[-1] = kod[c[-1]]
	if int("".join(a))+int("".join(b)) == int("".join(c)):
		print int("".join(a))
		print int("".join(b))
		print int("".join(c))
		return True
	return False
	
def lamiglowka(napis):
	znaki = []
	kod = {}
	a,c = napis.split(' = ')
	a,b = a.split(' + ')
	k = 1
	znaki.append(a[0])
	if b[0] not in znaki:
		znaki.append(b[0])
		k+=1
	if c[0] not in znaki:
		znaki.append(c[0])
		k+=1
	for i in a:
		if i not in znaki:
			znaki.append(i)
	for i in b:
		if i not in znaki:
			znaki.append(i)
	for i in c:
		if i not in znaki:
			znaki.append(i)
	for i in znaki:
		kod[i] = -1	
	flag = True
	for i in perm(range(10),len(znaki)):
		for j in range(k):
			if i[j] == 0:
				flag=False
		if(flag == False):
			flag = True
			continue
		for j in range(len(i)):
			kod[znaki[j]] = str(i[j])
		if(sprawdz(list(a), list(b), list(c), kod) == True):
			print k
			print i
			return kod
			
print lamiglowka(napis)
