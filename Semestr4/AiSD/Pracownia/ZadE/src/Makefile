Flags = -std=c++11 -Wall -pedantic -Wextra -W -O2 -static -lm
CPP = g++

zadE.out: zadE.o
	$(CPP) $(Flags) zadE.o -o zadE.out
	
zadE.o: zadE.cpp
	$(CPP) $(Flags) -c zadE.cpp -o zadE.o


clean:
	rm -rf *.o *.out
