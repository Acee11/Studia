from sets import *

def m(x,y,wiadra):
	res = [(wiadra[0],0), (0,wiadra[1]),  (x,wiadra[1]),   (wiadra[0],y)]
	if wiadra[0] <= y-wiadra[1]:
		res.append((0,wiadra[0]+wiadra[1]))
	elif wiadra[0] > y-wiadra[1]:
		res.append((wiadra[0]-(y-wiadra[1]), y))
		
	if wiadra[1] <= x-wiadra[0]:
		res.append((wiadra[0]+wiadra[1],0))
	elif wiadra[1] > x-wiadra[0]:
		res.append((x, wiadra[1]-(x-wiadra[0])))
	return res

def dfs(x,y,k,wiadra,mem):
	print wiadra
	if wiadra[0]==k or wiadra[1]==k:
		return True
	for i in m(x,y,wiadra):
		if i in mem:
			continue
		mem.add(i)
		if dfs(x,y,k,i,mem) == True:
			return True
	
dfs(5,8,3,(0,0),Set([]))