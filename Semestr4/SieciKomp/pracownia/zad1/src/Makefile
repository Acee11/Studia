Flags = -Wall -W -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c99
C = gcc
BIN = traceroute

traceroute: traceroute.o sending_func.o recv_func.o
	$(C) $(Flags) traceroute.o sending_func.o recv_func.o -o traceroute

traceroute.o: traceroute.c
	$(C) $(Flags) -c traceroute.c -o traceroute.o

sending_func.o: sending_func.c
	$(C) $(Flags) -c sending_func.c -o sending_func.o

recv_func.o: recv_func.c
	$(C) $(Flags) -c recv_func.c -o recv_func.o

clean:
	rm -rf *.o
distclean:
	rm -rf $(BIN)

