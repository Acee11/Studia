# -*- encoding: utf8 -*-
import sys
from turtle import *
import random
from time import *


P = {}
tracer(0,0)

DX = 14
DY = 14
DD = 20
SX = DD * DX / 2
SY = DD * DY / 2

Col = {
  'r' : 'red',
  'g' : 'green',
  'y' : 'yellow',
  'b' : 'blue',
  'm' : 'magenta',
  'o' : 'orange'
}

colors = Col.values()

def kw(x,y,c):
  pu()
  color(c,c)
  begin_fill()
  goto(x*DD-SX, y*DD-SY)
  for i in range(4):
    fd(DD)
    rt(90)    
  end_fill()
    
for x in range(DX):
  for y in range(DY):
    P[x,y] = random.choice(colors)

def rysuj():
  for x,y in P:
    kw(x,y, P[x,y])
  update()  
  
def sasiedzi(start):
  x,y = start
  k1 = P[x,y]
  wynik = []
  for dx,dy in [ (0,1), (0,-1), (1,0), (-1,0)]:
     nx = x + dx
     ny = y + dy
     if (nx,ny) in P and P[nx,ny] == k1:
       wynik.append( (nx,ny) )
  return wynik
       
        
def bfs2(a):
	kolejka = [a]
	odwiedzone = set([a])
	while kolejka != []:
		e = kolejka[0]
		del kolejka[0]
		for n in sasiedzi(e):
			if n not in odwiedzone:
				kolejka.append(n)
				odwiedzone.add(n)
	return odwiedzone    

rysuj()
Start = (0,DY-1)
zakolorowane = set( )





nr = 1
while len(zakolorowane) != DX * DY:
  print 'Ruch', nr
  #print sasiedzi(Start)
  #print bfs2(Start)
  k = Col[raw_input('Podaj kolor: ')]
  for x,y in zakolorowane:
    P[x,y] = k
  rysuj()  
  zakolorowane =  bfs2(Start)
  nr += 1
  
if nr <= 25:
   print 'WYGRALES!'
else:
   print 'Ty cieniasie!'
   
raw_input()  
