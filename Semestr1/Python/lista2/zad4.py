from duze_cyfry import dajCyfre

def wypiszLiczbe(n):
	n = str(n)
	
	liczba = dajCyfre(int(n[0]))
	
	for i in range(len(n) - 1):
		buf = dajCyfre(int(n[i+1]))
		for j in range(5):
			liczba[j] += ' ' + buf[j] + ' '

	for i in liczba: print i
	
while(1):
	a = input()
	wypiszLiczbe(a)
