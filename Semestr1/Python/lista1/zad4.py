from los import losujFragment

def losujHaslo(n):
	haslo = ""
	while(len(haslo) != n):
		tempFrag = losujFragment()
		
		if((len(haslo) + len(tempFrag) <= n) & (len(haslo) + len(tempFrag) != n - 1)):
			haslo += tempFrag

	return haslo

for i in range(10):
	print(losujHaslo(8))
	


for i in range(10):
	print(losujHaslo(12))