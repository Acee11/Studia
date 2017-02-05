from turtle import *
from random import choice, randint
from time import *

speed('fastest')
tracer(1,0)

col = ['yellow','black','blue','red','green']

def kwadrat(a,color):
	pu()
	bk(a/2)
	lt(90)
	bk(a/2)
	
	fillcolor(color)
	begin_fill()
	for i in range(4):
		fd(a)
		rt(90)
	end_fill()
	
def func(a,x,y,k,i):
	if(i==k): return
	
	pu()
	goto(x,y)
	pd()
	
	if(i == 0): color = 'black'
	elif(i == 1): color = 'blue'
	elif (i == 2): color = 'yellow'
	elif(i == 3): color = 'green'
	elif(i == 4): color = 'red'
	
	kwadrat(a,color)
	
	func(int(0.5*a), int(x - 0.75 * a), y, k, i+1)
	
	func(int(0.5*a), int(x + 0.75 * a), y, k, i+1)
	
	func(int(0.5*a), x, int(y + 0.75 * a), k, i+1)
	
	func(int(0.5*a), x, int(y - 0.75 * a), k, i+1)
	
	
func(200,0,0,5,0)

raw_input()


