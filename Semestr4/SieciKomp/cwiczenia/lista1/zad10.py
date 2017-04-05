import time

n = 20
t = [0 for i in range(n)]
t[0] = 1

finished = False
tm = 0

while not finished:
	finished = True
	for i in range(n):
		if t[i] != 0:
			finished = False
			t[i] -= 1
			for j in range(i+1,n):
				t[j] += 1
				tm += 1
		#time.sleep(1)

print(tm)

