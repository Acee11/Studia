#-*- coding: utf-8 -*-

from sets import *
	
slowa =Set()


for wiersz in open("slowa.txt"):
	wiersz = wiersz[:-1]
	wiersz = unicode(wiersz,'utf8')
	slowa.add(wiersz)
	
for wiersz in open("slowa.txt"):
	wiersz = wiersz[:-1]
	wiersz = unicode(wiersz,'utf8')
	if wiersz[::-1] in slowa:
		print wiersz,wiersz[::-1]
		if wiersz in slowa:
			slowa.remove(wiersz)
		







	