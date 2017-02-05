def koperta(n):
	print ((2 * n + 1) * '*')
	for i in range(n - 1):
		print('*' + i * ' ' + '*' + (2*n - 3 - 2*i) * ' ' + '*' + i * ' ' + '*')
		
	print ('*' + (n-1) * ' ' + '*' + (n-1) * ' ' + '*')
	
	for i in range(n - 2, -1, -1):
		print('*' + i * ' ' + '*' + (2*n - 3 - 2*i) * ' ' + '*' + i * ' ' + '*')
	print ((2 * n + 1) * '*')
	
while(1):
	a = input()
	koperta(a)
	