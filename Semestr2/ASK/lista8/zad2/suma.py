suma = 0.0
for i in range(32769):
	for j in range(513):
		suma += float(i)/2048 + float(j) * 0.001621
suma /= float(32768 * 512)
print suma