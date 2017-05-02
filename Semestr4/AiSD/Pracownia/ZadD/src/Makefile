Flags = -std=gnu++11 -Wall -W -O2 -static
CPP = g++

zadD.out: zadD.o
	$(CPP) $(Flags) zadD.o -o zadD.out
	
zadD.o: zadD.cpp
	$(CPP) $(Flags) -c zadD.cpp -o zadD.o

clean:
	rm -rf *.o *.out
