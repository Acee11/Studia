program = []
etykiety = {}
c = 1
for x in open('program.pygo'):
	L = x.split()
	if L[0][0] == '_':
		etykiety[L[0]] = c
	c += 1
	

for x in open('program.pygo'):
	L = x.split()
	if L[0][0] == '_':
		L = L[1:]
	if len(L) == []:
		program.append( () )
	elif len(L) >= 2 and L[1] == '=':
		program.append( ('=', L[0], ' '.join(L[2:])) )
	elif L[0] == 'if':
		if L[-1] in etykiety:
			program.append( ('if', ' '.join(L[1:-2]), etykiety[L[-1]]-1 ) )
		else:
			program.append( ('if', ' '.join(L[1:-2]), int(L[-1]) -1 ) )
	elif L[0] == 'goto':
		if L[1] in etykiety:
			program.append( ('goto',etykiety[L[1]]-1) )
		else:
			program.append( ('goto', int(L[1]) - 1) )
	elif L[0] == 'print':
		program.append( ('print', ' '.join(L[1:])) )
	else:
		program.append( () )
	c += 1
     
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
		if eval(warunek, dane):
			pc = nowePC
		else:
			pc += 1
	elif instr[0] == 'goto':
		pc = instr[1]  
	elif instr[0] == 'print':
		print eval(instr[1],dane)
		pc += 1
	else:
		print 'Nieznana instrukcja', instr
		pc += 1    
                
