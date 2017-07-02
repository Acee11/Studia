Flags = -Wall -W -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c99
C = gcc
BIN = transport.out

transport: transport.o downloader.o window.o
	$(C) $(Flags) transport.o downloader.o window.o -o transport.out

transport.o: transport.c
	$(C) $(Flags) -c transport.c -o transport.o

downloader.o: downloader.c downloader.h
	$(C) $(Flags) -c downloader.c -o downloader.o

window.o: window.c window.h
	$(C) $(Flags) -c window.c -o window.o

clean:
	rm -rf *.o
distclean:
	rm -rf $(BIN)

