Flags = -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c++11
CPP = g++

main : Makefile   main.o rectangle.o triangle.o circle.o surface.o
	$(CPP) $(Flags) -o main   main.o rectangle.o triangle.o circle.o surface.o

main.o : main.cpp   rectangle.h circle.h triangle.h surface.h
	$(CPP) -c $(Flags) main.cpp -o main.o

rectangle.o: rectangle.cpp
	$(CPP) -c $(Flags) rectangle.cpp -o rectangle.o

triangle.o: triangle.cpp
	$(CPP) -c $(Flags) triangle.cpp -o triangle.o	

circle.o: circle.cpp
	$(CPP) -c $(Flags) circle.cpp -o circle.o		

surface.o: surface.cpp
	$(CPP) -c $(Flags) surface.cpp -o surface.o			

clean:
	rm -rf *.o main