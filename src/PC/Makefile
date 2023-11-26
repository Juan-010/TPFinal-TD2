#Variables
CC = gcc
CFLAGS = -Wall -Werror -g
#Rules
all: main

main: main.o termset.o
	$(CC) $(CFLAGS) -o main main.o termset.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
termset.o: termset.c
	$(CC) $(CFLAGS) -c termset.c
	
clean:
	rm -f *.o main
