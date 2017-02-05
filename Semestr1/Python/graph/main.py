directions = {}

g = input()

for i in range(g):
	v = input()
	conn_num = []
	connections = []
	for j in range(v):
		tmp = []
		vertex_index,conn_num[j] = input()
		for h in range(conn_num[j]):
			t = input()
			tmp.append(t)
		connections.append(tmp)
	
	for i in connections:
		print i
	
	while(True):
		start_vert,mode = input()
		

			