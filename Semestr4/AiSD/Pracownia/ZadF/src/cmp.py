rel_path = '../tests/'

for i in range(1,31):
	f1 = open(rel_path + 'out/' + str(i) + '.out', 'r')
	f2 = open(rel_path + 'myout/' + str(i) + '.out', 'r')
	for c, (e1,e2) in enumerate(zip(f1,f2)):
		if e1.strip() != e2.strip():
			print('File:',i,'Line number:',c,'val1:',e1.strip(),'val2:',e2.strip())