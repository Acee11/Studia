Flags = -Wall -Wreturn-type -pedantic -pedantic-errors -Wundef -O3

zad13.o:
	gcc -c $(Flags) zad13.c -o zad13.o
precalc.o:
	gcc -c $(Flags) precalc.c -o precalc.o
main:  zad13.o precalc.o zad13.c
	gcc $(Flags) -o main	zad13.o precalc.o
clean:
	rm -rf *.o zad13