from sets import Set
from time import *
from random import *

curr_state = [Set(['wilk','koza','kapusta','przewoznik']),Set([])]
bad = [ 
[Set(['wilk','koza']),Set(['przewoznik','kapusta'])],
[Set(['przewoznik','kapusta']),Set(['wilk','koza'])],
[Set(['kapusta','koza']),Set(['przewoznik','wilk'])],
[Set(['przewoznik','wilk']),Set(['kapusta','koza'])],
[Set(['wilk','koza','kapusta']),Set(['przewoznik'])]]  


def moves(state):
	res = []
	
	if 'przewoznik' in state[0]:
		nstate = [Set(state[0])-Set(['przewoznik']),Set(state[1])|Set(['przewoznik'])]
		res.append(nstate)
		for i in nstate[0]:
			res.append([Set(nstate[0])-Set([i]),Set(nstate[1])|Set([i])])
	
	elif 'przewoznik' in state[1]:
		nstate = [Set(state[0])|Set(['przewoznik']),Set(state[1])-Set(['przewoznik'])]
		res.append(nstate)
		for i in nstate[1]:
			res.append([Set(nstate[0])|Set([i]),Set(nstate[1])-Set([i])])
	return res
	
mem = []
def dfs(state,mem,flag):
	print state
	if len(state[1]) == 4:
		return True
	for i in moves(state):
		if i not in bad and i not in mem:
			mem.append(i)
			flag = dfs(i,mem,flag)
			if flag == True:
				return True
				
def dfsrnd(state,flag):
	print state
	if len(state[1]) == 4:
		return True
	while(flag==False):
		c = choice(moves(state))
		if c not in bad:
			flag = dfsrnd(c,flag)
				
			

dfsrnd(curr_state,False)
	

	