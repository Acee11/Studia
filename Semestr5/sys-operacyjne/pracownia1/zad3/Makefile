CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra -I./include
PROG1 = zad3
PROG2 = reader
PROG3 = filter
PROG4 = printer
PROG5 = func_wrap

all: $(PROG1).out $(PROG2).out $(PROG3).out $(PROG4).out

$(PROG1).out: $(PROG1).o $(PROG5).o
	$(CC) $(PROG1).o $(PROG5).o -o $(PROG1).out $(FLAGS)

$(PROG1).o: $(PROG1).c
	$(CC) $(PROG1).c -c -o $(PROG1).o $(FLAGS)	

$(PROG2).out: $(PROG2).o $(PROG5).o
	$(CC) $(PROG2).o $(PROG5).o -o $(PROG2).out $(FLAGS)

$(PROG2).o: $(PROG2).c 
	$(CC) $(PROG2).c -c -o $(PROG2).o $(FLAGS)

$(PROG3).out: $(PROG3).o $(PROG5).o
	$(CC) $(PROG3).o $(PROG5).o -o $(PROG3).out $(FLAGS)

$(PROG3).o: $(PROG3).c
	$(CC) $(PROG3).c -c -o $(PROG3).o $(FLAGS)

$(PROG4).out: $(PROG4).o $(PROG5).o
	$(CC) $(PROG4).o $(PROG5).o -o $(PROG4).out $(FLAGS)

$(PROG4).o: $(PROG4).c
	$(CC) $(PROG4).c -c -o $(PROG4).o $(FLAGS)

$(PROG5).o: $(PROG5).c
	$(CC) $(PROG5).c -c -o $(PROG5).o $(FLAGS)

clean:
	rm *.o $(PROG1).out $(PROG2).out $(PROG3).out $(PROG4).out
