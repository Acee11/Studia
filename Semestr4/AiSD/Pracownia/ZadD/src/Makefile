Flags = -std=c++11 -Wall -pedantic -Wextra -W -O2 -static -lm
CPP = g++

zadD.out: zadD.o
	$(CPP) $(Flags) zadD.o -o zadD.out
	
zadD.o: zadD.cpp
	$(CPP) $(Flags) -c zadD.cpp -o zadD.o

clean:
	rm -rf *.o *.out
