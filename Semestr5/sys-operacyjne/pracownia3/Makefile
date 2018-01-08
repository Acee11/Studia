CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra -ggdb
PROG1 = malloc

all: $(PROG1).so test.out

test.out: test.c
	$(CC) test.c -o test.out $(FLAGS) -lpthread

$(PROG1).out: $(PROG1).o
	$(CC) $(PROG1).o  -o $(PROG1).out $(FLAGS)

$(PROG1).so: $(PROG1).c
	$(CC) $(PROG1).c -o $(PROG1).so -shared -fPIC $(FLAGS) -lpthread

$(PROG1).o: $(PROG1).c
	$(CC) $(PROG1).c -c -o $(PROG1).o -fPIC $(FLAGS)


clean:
	rm *.o $(PROG1).out

