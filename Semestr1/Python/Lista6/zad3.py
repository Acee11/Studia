#-*- coding: utf-8 -*-

def slownik(s):
	s = s.lower()
	alfabet = 'a¹bcædeêfghijkl³mnñoópqrsstuvwxyzŸ¿'
	sl = {}
	for l in alfabet:
		sl[l] = 0
	for l in s:
		sl[l] += 1
	return sl

def check(slowo1,slowo2):
	slowo1 = slowo1.lower()
	slowo2 = slowo2.lower()
	alfabet = 'a¹bcædeêfghijkl³mnñoópqrsstuvwxyzŸ¿'
	sl1 = slownik(slowo1)
	sl2 = slownik(slowo2)
	for i in alfabet:
		if (sl1[i] > sl2[i]):
			return False
	return True

print(check("kOæt","lokomotywa"))



	
