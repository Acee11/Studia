# -*- coding: utf-8 -*-
#może nie działać na linuxie(nie wiem dlaczego)

from turtle import *

delay(0)

def square(b,c,x,y):
	color(c,c)
	
	pu()
	setpos(x,y)
	pd()
	begin_fill()
	fd(b)
	rt(90)
	fd(b)
	rt(90)
	fd(b)
	rt(90)
	fd(b)
	rt(90)
	end_fill()

def deadOrAlive(P,y,x):
	cells = 0
	

	for i in range (x-1,x+2):
		if(P[y-1][i] == '#'):
			cells += 1
				
	if(P[y][x-1] == "#"):
		cells += 1
		
	if(P[y][x+1] == "#"):
		cells += 1
		
			
	for i in range (x-1,x+2):
		if(P[y+1][i] == '#'):
			cells += 1
			
	if(P[y][x] == '#'):
		if(cells >= 4):
			return '.'
		if(cells == 2 or cells == 3):
			return '#'
		if(cells <= 1):
			return '.'
			
	elif(P[y][x] == '.'):
		if (cells == 3):
			return '#'
		else: return '.'
		

startposx = -100
startposy = 100
bok = 20
		
planszatmp  = []
for i in open("plansza.txt",'r'):
		planszatmp.append(i[:-1])
planszacopy = []
for i in planszatmp:
		planszacopy.append(i)
		
for i in range(len(planszatmp)):
	for j in range(len(planszatmp[i])):
		if(planszatmp[i][j] == '#'):
			square(bok,'green',startposx + j*bok,startposy + i*bok)	

		
	
while(True):

	plansza = []
	
	for i in range(len(planszatmp)):
		for j in range(len(planszatmp[i])):
			if((planszacopy[i][j] != planszatmp[i][j]) and planszatmp[i][j] == '#'):
				square(bok,'green',startposx + j*bok,startposy + i*bok)
			elif((planszacopy[i][j] != planszatmp[i][j]) and planszatmp[i][j] == '.'):
				square(bok,'white',startposx + j*bok,startposy + i*bok)
				
				
			
	
	l = len(planszatmp[0])
	
	for i in range(len(planszatmp)):
		p = ""
		p += planszatmp[i][-1]
		p += planszatmp[i]
		p += planszatmp[i][0]
		plansza.append(p)
	
	p = plansza[0]
	k = plansza[-1]

	plansza.append(p)
	plansza.insert(0,k)

		
	print
	
	planszacopy = []
	
	for i in planszatmp:
		planszacopy.append(i)
	
	planszatmp = []
	
	for i in range(1,len(plansza)-1):
		p = ""
		for j in range(1,len(plansza[0])-1):
			p += deadOrAlive(plansza,i,j)
		planszatmp.append(p)
		
	raw_input()