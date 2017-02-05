# -*- coding: utf-8 -*-
#może nie działać na linuxie(nie wiem dlaczego)

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
		
		
planszatmp  = []
for i in open("plansza.txt",'r'):
		planszatmp.append(i[:-1])
		
	
while(True):

	plansza = []
	
	for i in planszatmp:
		print i
	
	l = len(planszatmp[0])
	
	for i in range(len(planszatmp)):
		p = ""
		p+=planszatmp[i][-1]
		p += planszatmp[i]
		p += planszatmp[i][0]
		plansza.append(p)
	
	p = plansza[0]
	k = plansza[-1]

	plansza.append(p)
	plansza.insert(0,k)

		
	print
	
	planszatmp = []
	
	for i in range(1,len(plansza)-1):
		p = ""
		for j in range(1,len(plansza[0])-1):
			p += deadOrAlive(plansza,i,j)
		planszatmp.append(p)


	raw_input()
	
	
	
	
	







