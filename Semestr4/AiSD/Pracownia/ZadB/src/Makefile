Flags = -std=gnu++11 -Wall -W -O2 -static
CPP = g++

zadB.out: zadB.o
	$(CPP) $(Flags) zadB.o -o zadB.out
	
zadB.o: zadB.cpp
	$(CPP) $(Flags) -c zadB.cpp -o zadB.o

clean:
	rm -rf *.o *.out
