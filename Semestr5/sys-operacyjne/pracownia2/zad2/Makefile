CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra -I./include
PROG1 = zad2a
PROG2 = zad2b

all: $(PROG1).out $(PROG2).out

$(PROG1).out: $(PROG1).o mysemaphore.o
	$(CC) $(PROG1).o mysemaphore.o -o $(PROG1).out $(FLAGS) -lpthread

$(PROG1).o: $(PROG1).c
	$(CC) $(PROG1).c -c -o $(PROG1).o $(FLAGS)	

$(PROG2).out: $(PROG2).o
	$(CC) $(PROG2).o -o $(PROG2).out $(FLAGS) -lpthread

$(PROG2).o: $(PROG2).c
	$(CC) $(PROG2).c -c -o $(PROG2).o $(FLAGS)	

mysemaphore.o: mysemaphore.c ./include/mysemaphore.h
	$(CC) mysemaphore.c -c -o mysemaphore.o $(FLAGS)	

clean:
	rm *.o $(PROG1).out $(PROG2).out

