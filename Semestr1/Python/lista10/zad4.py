# -*- encoding: utf8 -*-
#może źle działać na linuxie
from time import *
from random import choice

f = open('imionanew.txt')
S = {}

alfabet = 'abcdefghijklmnoprstuwyz'

for i in f:
	i = unicode(i[:-1],'utf8')
	for j in range(len(i)-2):
		if i[j]+i[j+1] not in S:
			S[i[j]+i[j+1]] = [i[j+2]]
		else:
			S[i[j]+i[j+1]].append(i[j+2])


def imie(len):
	name = '__'
	for i in range(len):
		if name[i]+name[i+1] in S:
			name += choice(S[name[i]+name[i+1]])
		else:
			name += choice(alfabet)
	return name[2:]
		

		
for i in range(20):
	print imie(8)