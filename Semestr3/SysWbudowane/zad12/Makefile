Flags = -Wall -Wreturn-type -pedantic -pedantic-errors -Wundef -O3

zad12.o:
	gcc -c $(Flags) zad12.c -o zad12.o
main:  zad12.o zad12.c
	gcc $(Flags) -o main	zad12.o
clean:
	rm -rf *.o main