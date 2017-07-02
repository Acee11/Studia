Flags = -Wall -W -Wreturn-type -pedantic -pedantic-errors -Wundef -std=c99
C = gcc
BIN = router.out

router: router.o routing_table.o
	$(C) $(Flags) router.o routing_table.o -o router.out

router.o: router.c
	$(C) $(Flags) -c router.c -o router.o

routing_table.o: routing_table.c routing_table.h
	$(C) $(Flags) -c routing_table.c -o routing_table.o

clean:
	rm -rf *.o
distclean:
	rm -rf $(BIN)

