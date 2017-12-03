CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra -I./include
PROG = zad1

all: $(PROG).out

$(PROG).out: $(PROG).o mysemaphore.o
	$(CC) $(PROG).o mysemaphore.o -o $(PROG).out $(FLAGS) -lpthread

$(PROG).o: $(PROG).c
	$(CC) $(PROG).c -c -o $(PROG).o $(FLAGS)	

mysemaphore.o: mysemaphore.c ./include/mysemaphore.h
	$(CC) mysemaphore.c -c -o mysemaphore.o $(FLAGS)	

clean:
	rm *.o $(PROG).out

