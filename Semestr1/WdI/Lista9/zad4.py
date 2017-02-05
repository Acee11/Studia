import sys
sys.setrecursionlimit(1000000)
n = 8
stack = []
szach = {}
for i in range(n):
	for j in range(n):
		szach[(i,j)] = False
		
def mozliwosci(szach,i,j):
	res = []
	if (i-1,j+2) in szach and szach[(i-1,j+2)] == False:
		res.append((i-1,j+2))
	if (i+1,j+2) in szach and szach[(i+1,j+2)] == False:
		res.append((i+1,j+2))
	if (i-1,j-2) in szach and szach[(i-1,j-2)] == False:
		res.append((i-1,j-2))
	if (i+1,j-2) in szach and szach[(i+1,j-2)] == False:
		res.append((i+1,j-2))
	if (i-2,j-1) in szach and szach[(i-2,j-1)] == False:
		res.append((i-2,j-1))
	if (i+2,j-1) in szach and szach[(i+2,j-1)] == False:
		res.append((i+2,j-1))
	if (i-2,j+1) in szach and szach[(i-2,j+1)] == False:
		res.append((i-2,j+1))
	if (i+2,j+1) in szach and szach[(i+2,j+1)] == False:
		res.append((i+2,j+1))
	return res

def Dfs(i,j,c,res):
	szach[(i,j)] = True
	L = mozliwosci(szach,i,j)
	if L == [] and c == n*n:
		print res
	else:
		for x in mozliwosci(szach,i,j):
			Dfs(x[0],x[1],c+1,res + [(x[0],x[1])])
	szach[(i,j)] = False

"""
stack.append((0,0))
c = 1
res = []
while stack:
	if res != [] and szach[res[-1][0],res[-1][1]] == True:
		
		
	v = stack[-1]
	szach[v[0],v[1]] = True
	res.append(v)
	c+=1
	del stack[-1]
	L = mozliwosci(szach,v[0],v[1])
	
	if L == [] and c == n*n:
		print res
		break
	elif L == [] and c < n*n:
		c-=1
		szach[res[-1][0],res[-1][1]] = False
		del res[-1]
		continue
	for i in L:
		stack.append((i[0],i[1]))
"""
Dfs(3,3,1,[])
		