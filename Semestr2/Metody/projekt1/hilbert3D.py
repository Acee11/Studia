from math import sin,cos,radians
from sys import argv

Xp = 1
Xm = 2
Yp = 3
Ym = 4
Zp = 5
Zm = 6

F = [
{
	1 : 1,
	2 : 2,
	3 : 5,
	4 : 6,
	5 : 4,
	6 : 3
},	#X w gore

{
	1 : 1,
	2 : 2,
	3 : 6,
	4 : 5,
	5 : 3,
	6 : 4
},	#X w dol
{
	1 : 6,
	2 : 5,
	3 : 3,
	4 : 4,
	5 : 1,
	6 : 2
},	#Y w lewo

{
	1 : 5,
	2 : 6,
	3 : 3,
	4 : 4,
	5 : 2,
	6 : 1
},	#Y w prawo

{
	1 : 3,
	2 : 4,
	3 : 2,
	4 : 1,
	5 : 5,
	6 : 6
},	#Z w lewo

{
	1 : 4,
	2 : 3,
	3 : 1,
	4 : 2,
	5 : 5,
	6 : 6
	
}	#Z w prawo
]

Sl = {
	1 : 'X+',
	2 : 'X-',
	3 : 'Y+',
	4 : 'Y-',
	5 : 'Z+',
	6 : 'Z-'
}

# X1 = 1	X2 = 2	Y1 = 3	Y2 = 4	Z1 = 5	Z2 = 6



def draw(pkt):
	pkt = (pkt[0], pkt[1]*cosinusfi - pkt[2]*sinusfi, pkt[1]*sinusfi + pkt[2]*cosinusfi)			  # obrot wzgledem osi OX(ukladu obiektu)
	pkt = ((pkt[0] * cosinuspsi) - (pkt[1] * sinusfi * sinuspsi) + (pkt[2]* cosinusfi * sinuspsi), # ------------------ OY ---------------
	 (pkt[0] * sinusfi * sinuspsi) + (pkt[1] * (cosinuspsi + cosinusfi * cosinusfi * (1 - cosinuspsi))) + (pkt[2] * sinusfi * cosinusfi * (1 - cosinuspsi)),
	 (-pkt[0] * cosinusfi * sinuspsi) + (pkt[1] * cosinusfi * sinusfi * (1 - cosinuspsi)) + (pkt[2] * (cosinuspsi + sinusfi * sinusfi * (1 - cosinuspsi))))

	pkt = (pkt[0] + Ox, pkt[1] + Oy, pkt[2] + Oz) # przeniesienie punktu z ukladu obiektu do ukladu swiata

	X = ((-d * (pkt[0])) / (pkt[2] - d)) # rzutowanie na plaszczyzne
	Y = ((-d * (pkt[1])) / (pkt[2] - d)) # -------------------------
	print str(X) + ' ' + str(Y) + ' ' + 'lineto'

def obrot(cp,step):
	if step == Xp:
		cp = (cp[0] + j, cp[1] ,cp[2])
	elif step == Xm:
		cp = (cp[0] - j, cp[1], cp[2])
	elif step == Yp:
		cp = (cp[0], cp[1] + j, cp[2])
	elif step == Ym:
		cp = (cp[0], cp[1] - j, cp[2])
	elif step == Zp:
		cp = (cp[0], cp[1], cp[2] + j)
	elif step == Zm:
		cp = (cp[0], cp[1], cp[2] - j)
	return cp


def hilbert(n,stack,cp):
	if n == 1:
		S = [4,2,3,5,4,1,3]
		while(stack):
			p = stack.pop(-1)
	 		for i in xrange(len(S)):
	 			S[i] = F[p-1][S[i]]
		for step in S:
			print cp
			cp = obrot(cp,step)
			draw(cp)

		return cp
	else:
		cp = hilbert(n-1,stack + [3,1],cp)

		step = Ym
		for i in xrange(len(stack)-1, -1, -1):
			step = F[stack[i]-1][step]
		cp = obrot(cp, step)
		draw(cp)

		cp = hilbert(n-1, stack + [2,4],cp)

		step = Xm
		for i in xrange(len(stack)-1, -1, -1):
			step = F[stack[i]-1][step]
		cp = obrot(cp, step)
		draw(cp)

		cp = hilbert(n-1, stack + [2,4],cp)

		step = Yp
		for i in xrange(len(stack)-1, -1, -1):
			step = F[stack[i]-1][step]
		cp = obrot(cp, step)
		draw(cp)

		cp = hilbert(n-1,stack + [5,5],cp)

		step = Zp
		for i in xrange(len(stack)-1, -1, -1):
			step = F[stack[i]-1][step]
		cp = obrot(cp, step)
		draw(cp)

		cp = hilbert(n-1,stack + [5,5],cp)

		step = Ym
		for i in xrange(len(stack)-1, -1, -1):
			step = F[stack[i]-1][step]
		cp = obrot(cp, step)
		draw(cp)

		cp = hilbert(n-1,stack + [1,3],cp)

		step = Xp
		for i in xrange(len(stack)-1, -1, -1):
			step = F[stack[i]-1][step]
		cp = obrot(cp, step)
		draw(cp)

		cp = hilbert(n-1,stack + [1,3],cp)

		step = Yp
		for i in xrange(len(stack)-1, -1, -1):
			step = F[stack[i]-1][step]
		cp = obrot(cp, step)
		draw(cp)

		cp = hilbert(n-1,stack + [4,2],cp)
		return cp



n = int(argv[1]) # rzad krzywej
ROZMIAR = float(argv[2]) # rozmiar obrazka
BOK = float(argv[3]) # dlugosc krawedzi szescianu
d = float(argv[4]) # odleglosc obserwatora od plaszczyzny rzutu

Ox = float(argv[5]) # ----------- x -----------------------------------
Oy = float(argv[6]) # wspolrzedna y srodku ukladu wspolrzednych obiektu
Oz = float(argv[7]) # ----------- z -----------------------------------

fi = float(argv[8]) # kat obrotu ukladu wspolrzednych obiektu wzgledem osi OX
psi = float(argv[9]) # --------------------------------------------------- OY

sinusfi = sin(radians(fi))
sinuspsi = sin(radians(psi))
cosinusfi = cos(radians(fi))
cosinuspsi = cos(radians(psi))

j = BOK / ((2**n)-1) #jednoska
d = -d


pp = (BOK, BOK, 0)
start = (pp[0], pp[1], pp[2])



print '%!PS-Adobe-2.0 EPSF-2.0'
print '%%BoundingBox: ' + str(-ROZMIAR/2.0) + ' ' + str(-ROZMIAR/2.0) + ' ' + str(ROZMIAR/2.0) + ' ' + str(ROZMIAR/2.0)
print 'newpath'


# | | | ustalenie punktu
# v v v  startowego

start = (start[0], start[1]*cosinusfi - start[2]*sinusfi, start[1]*sinusfi + start[2]*cosinusfi) 
 
start = ((start[0] * cosinuspsi) - (start[1] * sinusfi * sinuspsi) + (start[2]* cosinusfi * sinuspsi),
(start[0] * sinusfi * sinuspsi) + (start[1] * (cosinuspsi + cosinusfi * cosinusfi * (1 - cosinuspsi))) + (start[2] * sinusfi * cosinusfi * (1 - cosinuspsi)),
(-start[0] * cosinusfi * sinuspsi) + (start[1] * cosinusfi * sinusfi * (1 - cosinuspsi)) + (start[2] * (cosinuspsi + sinusfi * sinusfi * (1 - cosinuspsi))))

start = (start[0] + Ox, start[1] + Oy, start[2] + Oz)
X = ((-d * (start[0])) / (start[2] - d)) 
Y = ((-d * (start[1])) / (start[2] - d))
print str(X) + ' ' + str(Y) + ' ' + 'moveto'

# | | |  rysowanie
# v v v  krzywej

hilbert(n,[],(BOK, BOK,0))
print 'stroke\nshowpage'