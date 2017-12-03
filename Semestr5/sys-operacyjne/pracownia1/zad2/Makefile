CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra
PROG = zad2

all: $(PROG).out

$(PROG).out: $(PROG).o
	$(CC) $(PROG).o -o $(PROG).out $(FLAGS)

$(PROG).o: $(PROG).c
	$(CC) $(PROG).c -c -o $(PROG).o $(FLAGS)	

clean:
	rm *.o $(PROG).out

