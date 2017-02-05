from turtle import *
from random import *

def prostokat(x,y):
	fd(x)
	lt(90)
	fd(y)
	lt(90)
	fd(x)
	lt(90)
	fd(y)
	lt(90)
	fd(x)
	
pu()
bk(350)
pd()

x = 10

speed('fastest')

for i in range(50):
	y = randint(20,300)
	prostokat(x,y)
	pu()
	fd(4)
	pd()
	
raw_input()