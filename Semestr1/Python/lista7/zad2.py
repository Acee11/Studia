from turtle import *

def square(x,y,b,c):
	color(int(c.split(',')[0]),int(c.split(',')[1]),int(c.split(',')[2]))
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


pic = []
for i in open("obrazek.txt",'r'):
	pic.append(i[:-1])
	
tracer(100,0)

y = 300	
b = 10

colormode(255)

for i in pic:
	x = -300
	y -= b
	for j in i.split():
		x += b
		c = j[1:-1]
		square(x,y,b,c)


	