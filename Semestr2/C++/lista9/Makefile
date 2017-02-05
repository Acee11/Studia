
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11
CPP = g++

main : main.cpp fifteen.o
	$(CPP) $(Flags) -o main main.cpp fifteen.o 

main.o : main.cpp
	$(CPP) -c $(Flags) -o main.o main.cpp 

solve : Makefile   solve.o fifteen.o 
	$(CPP) $(Flags) -o solve   solve.o fifteen.o 

solve.o : Makefile   solve.cpp   fifteen.h move.h 
	$(CPP) -c $(Flags) solve.cpp -o  solve.o

fifteen.o : Makefile   fifteen.cpp   fifteen.h move.h 
	$(CPP) -c $(Flags) fifteen.cpp -o  fifteen.o

clean:
	rm -rf *.o main solve



