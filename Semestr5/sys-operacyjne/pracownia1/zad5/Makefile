CC = gcc
FLAGS = -std=gnu11 -Wall -Wextra -L./lib -I./lib -I./include
PROG1 = zad5a
PROG2 = zad5b

all: $(PROG1).out $(PROG2).out


$(PROG1).out: $(PROG1).o libstr.so
	$(CC) $(PROG1).o -o $(PROG1).out -Wl,-rpath=./lib $(FLAGS) -lstr

$(PROG1).o: $(PROG1).c
	$(CC) $(PROG1).c -c -o $(PROG1).o $(FLAGS)


$(PROG2).out: $(PROG2).o
	$(CC) $(PROG2).o -o $(PROG2).out $(FLAGS) -ldl

$(PROG2).o: $(PROG2).c
	$(CC) $(PROG2).c -c -o $(PROG2).o $(FLAGS)


libstr.so: strcnt.o strdrop.o
	$(CC) strcnt.o strdrop.o -o ./lib/libstr.so -shared -fPIC $(FLAGS)

strcnt.o: strcnt.c
	$(CC) strcnt.c -c -o strcnt.o $(FLAGS)	

strdrop.o: strdrop.c
	$(CC) strdrop.c -c -o strdrop.o $(FLAGS)	

clean:
	rm *.o $(PROG1).out $(PROG2).out ./lib/*
