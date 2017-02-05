def kolko(n):
	r = (n-(n%2 != 0))/2
	for y in range(r, -r-1, -1):
		l1 = 0
		l2 = 0
		for x in range(-r, r+1, 1):
			if(y*y + x*x <= r*r): 
				l1 += 1
			else:
				l2 += 1
		print((l2/2)*' ' + l1*'*' + (l2/2)*' ')
			
			
while(1):
	a = input()
	kolko(a)