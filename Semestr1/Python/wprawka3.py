def pochodna(Wielomian):
	wynik = []
	tmp = len(Wielomian) - 1
	for i in range(len(Wielomian)-1):
		wynik.append(Wielomian[i] * tmp)
		tmp -= 1

	return wynik

def f(wielomian,x):
	wynik = wielomian[0]
	for i in range(1,len(wielomian)):
		wynik *= x
		wynik += wielomian[i]

	return wynik
	

def mzerpochodnej(Pochodna,od,do,dokladnosc):
	wynik = []
	while(od <= do):
		y1 = f(Pochodna,od)
		y2 = f(Pochodna,od + dokladnosc)

		if(y2 < 0 and y1 > 0):
			tmp = [((od+od+dokladnosc)/2.0),1]
			wynik.append(tmp) # 1(maksimum)

		if(y1 < 0 and y2 > 0):
			tmp = [((od+od+dokladnosc)/2.0),-1]
			wynik.append(tmp) # -1(minimum)
		od += dokladnosc

	return wynik
	

def ekstr(Wielomian):
	pochodna1 = pochodna(Wielomian)
	mzer = mzerpochodnej(pochodna(Wielomian),-100,100,0.01)
		
	lista_max = []
	lista_min = []

	minimum = ""
	maximum = ""
	
	if (len(mzer) % 2 == 0):
		maximum = "oo"
		minimum = "-oo"
		
		
	elif (Wielomian[0] < 0):
		minimum = "-oo"
		for i in range(len(mzer)):
			if(mzer[i][1] == 1):
				lista_max.append(mzer[i][0])
		
		maximum = lista_max[0]
		for i in lista_max:
			if(f(Wielomian,i) > f(Wielomian,maximum)): maximum = i

			
	elif(Wielomian[0] > 0):
		maximum = "oo"
		for i in range(len(mzer)):
			if(mzer[i][1] == -1):
				lista_min.append(mzer[i][0])
		minimum = lista_min[0]
		for i in lista_min:
			if(f(Wielomian,i) < f(Wielomian,minimum)): minimum = i

	if(minimum != "-oo"):
		minimum = round(minimum,2)
		
	if(maximum != "oo"):
		maximum = round(maximum,2)

	return minimum,maximum
		
	

		

def miejscazerowe(Wielomian, od, do, dokladnosc):
	wynik = []
	while(od <= do):
		x = Wielomian[0]
		for i in range(1,len(Wielomian)):
			x *= od
			x += Wielomian[i]
                print x, (dokladnosc/len(Wielomian))/100.0
		if(x < (dokladnosc/len(Wielomian))/100.0 and x > -(dokladnosc/len(Wielomian))/100.0):
			wynik.append(od)
		od += dokladnosc

	return wynik
	

wielomian = [1,3,-2,5,-3]




print(ekstr(wielomian))




