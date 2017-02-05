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
	cellsC = 0
	cellsN = 0
	

	for i in range (x-1,x+2):
		if(P[y-1][i] == 'c'):
			cellsC += 1
		elif(P[y-1][i] == 'n'):
			cellsN += 1
		
				
	if(P[y][x-1] == 'c'):
		cellsC += 1
	elif(P[y][x-1] == 'n'):
		cellsN += 1
		
	if(P[y][x+1] == "c"):
		cellsC += 1
	if(P[y][x+1] == "n"):
		cellsN += 1
		
			
	for i in range (x-1,x+2):
		if(P[y+1][i] == 'c'):
			cellsC += 1
		elif(P[y+1][i] == 'n'):
			cellsN += 1
			
	if(P[y][x] != '.'):
		if(cellsN+cellsC >= 4 or cellsN+cellsC <= 1):
			return '.'
		else:
			return P[y][x]
			
	elif(P[y][x] == '.'):
		if (cellsC + cellsN == 3):
			if cellsC > cellsN:
				return 'c'
			else:
				return 'n'
		else:
			return '.'
		
	

startposx = -100
startposy = 100
bok = 20
		
planszatmp  = []
planszac = []
planszan = []

tracer(100,0)

for i in open("czerwone.txt",'r'):
	i = i[:-1]
	s = ""
	for j in i:
		if j == '#':
			s+= 'c'
		else:
			s += '.'
	planszac.append(s)
	

	

	
for i in open("niebieskie.txt",'r'):
	i = i[:-1]
	s = ""
	for j in i:
		if j == '#':
			s+= 'n'
		else:
			s += '.'
	planszan.append(s)
	
for i in range(len(planszan)):
	s = ""
	for j in range(len(planszan[0])):
		if planszac[i][j] != planszan[i][j]:
			if planszac[i][j] == '.':
				s += 'n'
			elif planszan[i][j] == '.':
				s += 'c'
		else:
			s+= '.'
	planszatmp.append(s)
	


		
			
planszacopy = []
for i in planszatmp:
		planszacopy.append(i)
		
for i in range(len(planszatmp)):
	for j in range(len(planszatmp[i])):
		if(planszatmp[i][j] == 'n'):
			square(bok,'blue',startposx + j*bok,startposy + i*bok)	
		elif(planszatmp[i][j] == 'c'):
			square(bok,'red',startposx + j*bok,startposy + i*bok)	

		
	
while(True):

	plansza = []
	
	for i in range(len(planszatmp)):
		for j in range(len(planszatmp[i])):
			if((planszacopy[i][j] != planszatmp[i][j]) and planszatmp[i][j] == 'c'):
				square(bok,'red',startposx + j*bok,startposy + i*bok)
			elif((planszacopy[i][j] != planszatmp[i][j]) and planszatmp[i][j] == 'n'):
				square(bok,'blue',startposx + j*bok,startposy + i*bok)
			elif((planszacopy[i][j] != planszatmp[i][j]) and planszatmp[i][j] == '.'):
				square(bok,'white',startposx + j*bok,startposy + i*bok)
				
				
			



	
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