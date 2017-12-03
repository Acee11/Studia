CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra -I./include -g
PROG = zad3

all: $(PROG).out

$(PROG).out: $(PROG).o mybarrier.o
	$(CC) $(PROG).o mybarrier.o -o $(PROG).out $(FLAGS) -lpthread

$(PROG).o: $(PROG).c
	$(CC) $(PROG).c -c -o $(PROG).o $(FLAGS)	

mybarrier.o: mybarrier.c ./include/mybarrier.h
	$(CC) mybarrier.c -c -o mybarrier.o $(FLAGS)	

clean:
	rm *.o $(PROG).out

