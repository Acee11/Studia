Flags = -std=c++11 -Wall -pedantic -Wextra -W -O2 -static -lm
CPP = g++

zadF.out: zadF.o
	$(CPP) $(Flags) zadF.o -o zadF.out
	
zadF.o: zadF.cpp
	$(CPP) $(Flags) -c zadF.cpp -o zadF.o


clean:
	rm -rf *.o *.out
