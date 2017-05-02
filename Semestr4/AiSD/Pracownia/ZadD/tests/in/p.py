f = open('4.in', 'a')
f.write("1\n")
f.write("500000\n")
for i in range(1, 500000):
	f.write("%d %d\n" %(i, i+1))

for i in range(1, 500000):
	f.write("%d %d\n" %(i, i+1))