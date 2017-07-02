for i in range(1, 40):
	print(i)
	f = open("../tests/out/"+str(i)+".out", 'r')
	a = open("../tests/myans/"+str(i)+".out", 'r')
	for s,ans in zip(f, a):
		print(s , ans)