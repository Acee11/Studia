CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra

all: zad1a.out zad1b.out

zad1a.out: zad1a.o
	$(CC) zad1a.o -o zad1a.out $(FLAGS)

zad1a.o: zad1a.c
	$(CC) zad1a.c -c -o zad1a.o $(FLAGS)	

zad1b.out: zad1b.o
	$(CC) zad1b.o -o zad1b.out $(FLAGS)

zad1b.o: zad1b.c
	$(CC) zad1b.c -c -o zad1b.o $(FLAGS)	

clean:
	rm *.o zad1a.out zad1b.out

