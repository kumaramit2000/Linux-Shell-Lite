CC=gcc
myshell: main.o signal-handling.o read.o execute.o builtin.o syscomm.o  parse.o header.h
	$(CC)  -o myshell main.o signal-handling.o read.o execute.o builtin.o syscomm.o parse.o -I.

main.o: main.c read.o header.h
	$(CC)  -c main.c  -I.

signal-handling.o: signal-handling.c header.h
	$(CC) -c signal-handling.c -I.

parse.o: parse.c execute.o header.h
		$(CC) -c parse.c -I.


read.o: read.c execute.o header.h
	$(CC)  -c read.c  -I.

execute.o: execute.c builtin.o syscomm.o header.h
	$(CC)  -c execute.c  -I.

builtin.o: builtin.c header.h
	$(CC) -c builtin.c -I.

syscomm.o: syscomm.c header.h
	$(CC) -c syscomm.c -I.


.PHONY: clean

clean:
	rm -f *.o
