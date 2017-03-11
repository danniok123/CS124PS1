CC=clang

CFLAGS=-c -Wall -g

all: strassen

strassen: main.o
	$(CC) main.o -o strassen

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -f *.o strassen
