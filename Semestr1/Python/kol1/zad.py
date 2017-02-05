from sets import *

def prostokat(a,b):
	print a * '*'
	for i in range(b-2):
		print '*' + (a-2) * ' ' + '*'
	print a * '*'
	
def schody(N, h, a, krok):
	for i in range(N):
		prostokat(a,h)
		a += krok

def f1(s, k, t):
	
	
print f1(["powylapywaly","niania","kek","doktor"])