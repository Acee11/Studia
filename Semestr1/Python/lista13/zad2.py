def NWD(a,b):
	while(b):
		r = a%b
		a = b
		b = r
	return a
def NWW(a,b):
	return (a*b)/NWD(a,b)
			

class Frac:
	def __init__(self,n=1,d=1):
		self.l = n
		self.m = d
		
	def skroc(self):
		if self.m == 0:
			return
		c = NWD(self.l, self.m)
		self.l /= c
		self.m /= c
		
	def __add__(self,a):
		if self.m == 0 or a.m == 0:
			print "Error: NaN"
			return self
		mian = NWW(self.m, a.m)
		c = Frac((self.l*(mian / self.m)) + ((a.l*(mian / a.m))),mian)
		return c
		
	def __iadd__(self,a):
		if self.m == 0 or a.m == 0:
			print "Error: NaN"
			return self
		self = self + a
		return self
		
	def __sub__(self,a):
		if self.m == 0 or a.m == 0:
			print "Error: NaN"
			return self
		mian = NWW(self.m, a.m)
		c = Frac((self.l*(mian / self.m)) - ((a.l*(mian / a.m))),mian)
		return c
		
	def __isub__(self,a):
		if self.m == 0 or a.m == 0:
			print "Error: NaN"
			return self
		self = self - a
		return self
		
	def __mul__(self,a):
		if self.m == 0 or a.m == 0:
			print "Error: NaN"
			return self
		c = Frac(self.l * a.l, self.m * a.m)
		return c
	
	def __imul__(self,a):
		if self.m == 0 or a.m == 0:
			print "Error: NaN"
			return self
		self = self * a
		return self
		
	def __div__(self,a):
		if self.m == 0 or a.m == 0:
			print "Error: NaN"
			return self
		return self * Frac(a.m, a.l)
		
	def __idiv__(self,a):
		if self.m == 0 or a.m == 0:
			print "Error: NaN"
			return self
		self = self / a
		return self
		
	def __eq__(self,a):
		if self.m == 0 and a.m == 0:
			return self.l == a.l
		elif self.m == 0 and a.m !=0 or self.m != 0 and a.m ==0:
			return False
		return self.l*a.m == self.m*a.l
		
	def __str__(self):
		if self.m == 0:
			if self.l == -1:
				return '-oo'
			elif self.l == 1:
				return 'oo'
			elif self.l == 0:
				return 'NaN'
		return str(self.l) + '/' + str(self.m)
		
	def __repr__(self):
		return "Frac(%s,%s)" % (repr(self.l),repr(self.m))
		
		
a = Frac(-1,0)
b = Frac(0,0)
c = Frac(10,5)
print a,b,c
a /= b
c += a
print a,b,c
a.skroc()
print [a,b,c]

		
		