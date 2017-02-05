n = 4
S = (n*((n*n)+1))/2
sumaK = [0 for i in range(n)]
sumaW = [0 for i in range(n)]
diag1 = 0
diag2 = 0
mozliwosci = {}
for i in range(1,(n*n)+1):
	mozliwosci[i] = False

kwadrat = [[0 for i in range(n)] for j in range(n)]
x = 0
y = 0
i = 1
while(True)
	if  x == n:
		x = 0
		y +=1
		continue
	if x == -1:
		y -= 1
		x = n - 1
	if y == n:
		break
	if kwadrat[y][x] != 0:
		sumaK -= kwadrat[y][x]
		sumaW -= kwadrat[y][x]
		kwadrat[y][x] = 0
		
	if i > n*n:
		if x == 0:
			i = kwadrat [y-1][n-1] + 1
			y -= 1
			x = n-1
			continue
		i  = kwadrat[y][x-1] + 1
		x -= 1
		continue
			
		
	if used[i] == True:
		i+=1
		continue
	if x == n-1 and sumaW[x] + i > S:
		i = kwadrat[y][x-1] + 1 
		x -= 1
		continue
	if y == n-1 and sumaK[y] + i > S:
		i = kwadrat[y-1][x] + 1
		y -= 1
		continue
	if
			
		
