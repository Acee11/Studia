import turtle
from random import *






def funkcja(
t1, # zolw
x, # wsp. x zolwia
y,# wsp. y zolwia
n, #dlugosc galezi
k, #kat w ktory jest skierowany zolw
licznik1, #ktore rozgalezienie bedzie rysowane
licznik2, #ile rozgalezien
range1,
range2, # [range1,range2] - zakres losowej liczby o ktora bedzie powiekszane k
rs, #o ile zwiekszac/zmniejszac range2
d #o ile zwiekszac/zmniejszac n
):
	if(licznik1>licznik2): return
	t1.pu()
	t1.setpos(x,y)
	t1.pd()
	t1.seth(k)
	
	
	
	t1.fd(n)
	x = t1.xcor()
	y = t1.ycor()
	licznik1 += 1
	
	r = randint(range1,range2)
	
	range2 += rs
	
	
	funkcja(t1,x,y,int(n*d),k+r,licznik1,licznik2,range1,range2,rs,d)
	funkcja(t1,x,y,int(n*d),k-r,licznik1,licznik2,range1,range2,rs,d)
	
	
	

t1 = turtle.Turtle()
t1.speed('fastest')
t1.lt(90)
t1.pu()
t1.bk(300)
t1.pd()

funkcja(t1,t1.xcor(),t1.ycor(),25,t1.heading(),0,7,10,20,7,0.981)


raw_input()

