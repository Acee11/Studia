# -*- encoding: utf8 -*-
from sets import Set
from time import *
from random import choice

S = {}
prev = ""
for i in open('panTad.txt'):
	i = i.split(' ')
	for j in range(1,len(i)):
		if i[j-1] not in S:
			S[i[j-1]] = [i[j]]
		elif i[j] not in S[i[j-1]]:
			S[i[j-1]].append(i[j])
	



pt = ['natenczas']
while (True):
	if pt[-1] in S:
		pt.append(' ')
		pt.append(choice(S[pt[-2]]))
	elif pt[-3] in S:
		pt.append(' ')
		pt += ' ' + choice(S[pt[-4]])
	else:
		break
	print unicode("".join(pt),'utf8',errors='ignore')
	sleep(0.2)