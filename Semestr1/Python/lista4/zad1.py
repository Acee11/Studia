import turtle
from math import *

def square(n):
	turtle.fd(n)
	turtle.lt(90)
	turtle.fd(n)
	turtle.lt(90)
	turtle.fd(n)
	turtle.lt(90)
	turtle.fd(n)
	turtle.lt(90)
	turtle.fd(n)

def func(n,a,kolor1,kolor2):
	stepR = (kolor2[0]-kolor1[0]) / ((n * (n+1))/2.0)
	stepG = (kolor2[1]-kolor1[1]) / ((n * (n+1))/2.0)
	stepB = (kolor2[2]-kolor1[2]) / ((n * (n+1))/2.0)
	
	colR = kolor1[0]
	colG = kolor1[1]
	colB = kolor1[2]
	
	counter = n
	
	turtle.fill(True)
	turtle.fillcolor([colR,colG,colB])
	
	for i in range(n*(n+1)/2):
		if(i==counter):
			turtle.lt(90)
			turtle.fd(a)
			n -= 1
			counter += n
		turtle.fill(True)
		turtle.fillcolor([colR,colG,colB])
		square(a)
		turtle.fill(False)
		
		colR += stepR
		colG += stepG
		colB += stepB
		
		
	

def gradient(n,kolor1,kolor2):
	stepR = (kolor2[0]-kolor1[0]) / (n * 1.0)
	stepG = (kolor2[1]-kolor1[1]) / (n * 1.0)
	stepB = (kolor2[2]-kolor1[2]) / (n * 1.0)
	
	colR = kolor1[0]
	colG = kolor1[1]
	colB = kolor1[2]
	
	for i in range(n):
		turtle.fill(True)
		turtle.color([colR,colG,colB])
		turtle.fd(100)
		turtle.rt(180)
		turtle.fd(100)
		turtle.lt(90)
		turtle.fd(1)
		turtle.lt(90)
		turtle.fill(False)
		
		colR += stepR
		colG += stepG
		colB += stepB





turtle.speed('fastest')

func(18,20,(1,1,0),(1,0.1,0.5))

raw_input()