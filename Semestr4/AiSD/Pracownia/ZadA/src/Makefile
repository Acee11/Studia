Flags = -std=gnu++11 -Wall -W -O2 -static
CPP = g++

zadA.out: zadA.o
	$(CPP) $(Flags) zadA.o -o zadA.out
	
zadA.o: zadA.cpp
	$(CPP) $(Flags) -c zadA.cpp -o zadA.o

clean:
	rm -rf *.o *.out
