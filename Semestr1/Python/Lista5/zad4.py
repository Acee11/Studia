# -*- encoding: utf8 -*-
from turtle import *
from random import choice, randint
from time import *

speed('fastest')
ht()
color('black', 'yellow')

def poczatkowyWaz(N):
  wynik = []
  for i in range(N):
    wynik.append( (i,0) )
  return wynik
    
def nast(dx,dy,x,y,range):
	if x == range:
		if(dx != 1):
			return -1,0
		else:
			return 0,choice([-1,1])
		
		
	if x == -range:
		if(dx != -1):
			return 1,0
		else:
			return 0,choice([-1,1])
			
	if y == range:
		if(dy != 1):
			return 0,-1
		else:
			return choice([-1,1]),0
			
	if y == -range:
		if(dy != -1):
			return 0,1
		else:
			return choice([-1,1]),0
	
	if (randint(0,5) != 0) :
		return dx,dy
	if dx == 0:
		return choice([-1,1]),0
	return 0, choice([-1,1])
   
def kwadrat1(bok):
	for i in range(4):
		fd(bok)
		rt(90)
   
def kwadrat(x,y,bok, c1,c2):
   color(c1,c2)
   pu()
   goto(x * bok, y * bok)
   pd()
         
   begin_fill()
   for i in range(4):
     fd(bok)
     rt(90)
   end_fill()
   
def glowa(x,y,dx,dy,bok, c1,c2):
   color(c1,c2)
   pu()
   goto(x * bok, y * bok)
   
   pd()
         
   begin_fill()
   for i in range(4):
     fd(bok)
     rt(90)
   end_fill()
   
   pu()
   
   if(dy == 1): 
	lt(90)
	bk(bok)
	
   elif(dy == -1): 
	fd(bok)
	rt(90)
	
   elif(dx == -1): 
	fd(bok)
	rt(90)
	fd(bok)
	rt(90)
   
   fd(int(0.8*bok))
   rt(90)
   fd(int(0.2 * bok))
   
   pd()
   color('black','black')
   begin_fill()
   
   kwadrat1(int(0.2 * bok))
   end_fill()
   pu()
   fd(int(0.4 * bok))
   pd()
   begin_fill()
   kwadrat1(int(0.2 * bok))
   end_fill()
   
   seth(0)
   
   

	
   
    
tracer(1,0) # nie wchodząc w szczegóły -- przyśpiesza działanie funkcji rysujących modułu turtle    

snake = poczatkowyWaz(10)

for x,y in snake:
   kwadrat(x,y,15, 'black', 'yellow')

dx = 1
dy = 0

raw_input()

while True:
  f = 0
  x,y = snake[-1]  #x,y - wspolrzedne glowy weza
  x = x+dx
  y = y+dy
  

  

  
  
      
  
  snake.append( (x,y) )
  
  rand = randint(1,10) #losowe wydluzanie weza
  
  if(rand == 1):
	f = 1
  
  x0,y0 = snake[0]

  if(f == 0):
    del snake[0]
  
  x1,y1 = snake[-2]
  
  if(f == 0):
    kwadrat(x0,y0,15, 'white', 'white') #wymazywanie ogona   ///     x0,y0 - wspolrzedne ogona weza

  
  glowa(x,y,dx,dy,15, 'black', 'yellow') #rysowanie glowy   ///   x,y - wspolrzedne glowy weza
  kwadrat(x1,y1,15,'black','yellow')
  
  dx,dy = nast(dx,dy,x,y,15)
  
  sleep(0.03)
  
  
    
update() # niepotrzebne, chyba ze w wyniku jakiejs modyfikacji program dojdzie do tego miejsca. W wyniku tego polecenia zostają narysowane wszystkie ,,zaległe'' rzeczy, czyli takie, które już zostały wprowadzone, a jeszcze nie znalazły się na ekranie. Chcąc wiedzieć więcej, przeanalizuj działanie funkcji tracer
raw_input()
