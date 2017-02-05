main: Makefile main.o stack.o
	g++ -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11 -o main main.o stack.o

stack.o: Makefile stack.cpp stack.h
	g++ -c -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11 stack.cpp -o stack.o



main.o: Makefile main.cpp stack.h
	g++ -c -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11 main.cpp -o main.o