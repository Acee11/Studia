from math import *
from time import *

def isPrime(n):
	for i in range(2,int(sqrt(n)),1):
		if(n%i == 0): return False
		
	return True
	

	
seven = "7777777"

licznik = 0

for i in range(4):  # 0 1 2 3
	
	n = 2
	
	if (i == 0): n = 1
	

	digit = [9,9,9]
	
	while(digit[0] != 0):
		temp = ""
	
		for j in range(3 - i): # 0 1 2
			temp += str(digit[j])
			
		temp += seven
			
		for j in range(3-i,3): 
			temp += str(digit[j])

		
		digit[2] -= n
		if(digit[2] == -1):
			digit[1] -= 1
			digit[2] = 9
			if(digit[1] == -1):
				digit[0] -= 1
				digit[1] = 9
		

	
		
		if isPrime(int(temp)): licznik += 1
		
print licznik
		
		
		
			
		
	
	
		
	