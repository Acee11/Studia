CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra -I./include
PROG1 = zad6


all: $(PROG1).out

$(PROG1).out: $(PROG1).o mysemaphore.o
	$(CC) $(PROG1).o mysemaphore.o -o $(PROG1).out $(FLAGS) -lpthread

$(PROG1).o: $(PROG1).c
	$(CC) $(PROG1).c -c -o $(PROG1).o $(FLAGS)

mysemaphore.o: mysemaphore.c ./include/mysemaphore.h
	$(CC) mysemaphore.c -c -o mysemaphore.o $(FLAGS)	

clean:
	rm *.o $(PROG1).out

