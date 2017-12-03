CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra -I./include
PROG1 = zad4


all: $(PROG1).out

$(PROG1).out: $(PROG1).o
	$(CC) $(PROG1).o -o $(PROG1).out $(FLAGS) -lpthread

$(PROG1).o: $(PROG1).c
	$(CC) $(PROG1).c -c -o $(PROG1).o $(FLAGS)	

clean:
	rm *.o $(PROG1).out

