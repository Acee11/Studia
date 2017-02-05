Flags = -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11

main: case_insensitive.o main.o 
	g++ $(Flags) case_insensitive.o functions.o main.o -o main
main.o: main.cpp 
	g++ $(Flags) -c main.cpp -o main.o
case_insensitive.o: case_insensitive.cpp
	g++ $(Flags) -c case_insensitive.cpp -o case_insensitive.o




