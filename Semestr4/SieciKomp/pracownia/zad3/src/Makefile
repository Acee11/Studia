Flags = -Wall -W -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c99
C = gcc
BIN = transport.out

transport: transport.o
	$(C) $(Flags) transport.o -o transport.out

transport.o: transport.c
	$(C) $(Flags) -c transport.c -o transport.o


clean:
	rm -rf *.o
distclean:
	rm -rf $(BIN)

