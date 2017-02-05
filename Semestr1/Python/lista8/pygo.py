program = []
etykiety = {}



p = 0

L = []

for x in open('program.pygo'):
	L1 = x.split()
	if L1[0][0] == '_':
		etykiety[L1[0]] = c
		L1= L1[1:]
	L.append(L1)


for x in L:
	L2 = x.split()
	if len(L2) == []:
		program.append( () )
	if L[0][0] == '_':
		L2 = L2[1:]
		
		
	elif len(L2) >= 2 and L2[1] == '=':
		program.append( ('=', L2[0], ' '.join(L2[2:])) )
	elif L2[0] == 'if':
		if L2[-1][0] == '_':
			program.append( ('if', ' '.join(L2[1:-2]), etykiety[L2[-1]]-1 ) )
		else:
			program.append( ('if', ' '.join(L2[1:-2]), int(L2[-1]) -1 ) )
	elif L2[0] == 'goto':
		if L2[1][0] == '_':
			program.append( ('goto', etykiety[L2[1]]-1) )
		else:
			program.append( ('goto', int(L2[1]) - 1) )
	elif L2[0] == 'print':
		program.append( ('print', ' '.join(L2[1:])) )
	else:
		program.append( () )
	print L2
     
pc = 0
dane = {}

while pc < len(program):
	instr = program[pc]
	if instr == ():
		pc += 1
	elif instr[0] == '=':
		zmienna, wyr = instr[1:]
		dane[zmienna] = eval(wyr, dane)
		pc += 1
	elif instr[0] == 'if':
		warunek, nowePC = instr[1:]
		if type(nowePC) != int:
			nowePC = etykiety[nowePC]
		if eval(warunek, dane):
			pc = nowePC
		else:
			pc += 1
	elif instr[0] == 'goto':
		if(type(instr[1]) == int):
			pc = instr[1]
		else:
			pc = etykiety[instr[1]]
	elif instr[0] == 'print':
		print eval(instr[1],dane)
		pc += 1
	else:
		print 'Nieznana instrukcja', instr
		pc += 1    
                
