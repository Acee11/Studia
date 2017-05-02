Flags = -std=gnu++11 -Wall -W -O2 -static
CPP = g++

zadC.out: zadC.o
	$(CPP) $(Flags) zadC.o -o zadC.out
	
zadC.o: zadC.cpp
	$(CPP) $(Flags) -c zadC.cpp -o zadC.o

clean:
	rm -rf *.o *.out
