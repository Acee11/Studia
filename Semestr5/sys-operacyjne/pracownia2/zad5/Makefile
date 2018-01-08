CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra -g
PROG1 = zad5


all: $(PROG1).out

$(PROG1).out: $(PROG1).o mylist.o mysynclist.o
	$(CC) $(PROG1).o mylist.o mysynclist.o -o $(PROG1).out $(FLAGS) -lpthread

$(PROG1).o: $(PROG1).c
	$(CC) $(PROG1).c -c -o $(PROG1).o $(FLAGS)	

mylist.o: mylist.c ./include/mylist.h
	$(CC) mylist.c -c -o mylist.o $(FLAGS)	

mysynclist.o: mysynclist.c ./include/mysynclist.h
	$(CC) mysynclist.c -c -o mysynclist.o $(FLAGS)	

clean:
	rm *.o $(PROG1).out

