from turtle import *

def f(bok,gr):
	if gr <= 0:
		fd(bok)
	else:
		f(bok/3,gr-1)
		rt(90)
		f(bok/4,gr-1)
		lt(90)
		f(bok/3,gr-1)
		lt(90)
		f(bok/4,gr-1)
		rt(90)
		f(bok/3,gr-1)
		
def f2(bok,gr):
	if gr == 0:
		fd(bok/3)
		rt(90)
		fd(bok/3)
		lt(90)
		fd(bok/3)
		lt(90)
		fd(bok/3)
		rt(90)
		fd(bok/3)
	else:
		f2(bok/3,gr-1)
	
tracer(50,0)
f(300,3)
lt(90)
f(300,3)
lt(90)
f(300,3)
lt(90)
f(300,3)
lt(90)

raw_input()
		
	