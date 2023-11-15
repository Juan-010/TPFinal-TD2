#Variables
CC = gcc
CFLAGS = -Wall -Werror -g
LIBS = -lwiringPi

#Rules
all: main

main: main.o sequence.o util.o
	$(CC) $(CFLAGS) -o main main.o sequence.o util.o $(LIBS)
util.o: util.c
	$(CC) $(CFLAGS) -I/home/pi/TD2/TPF/inc -c util.c 
sequence.o: sequence.c
	$(CC) $(CFLAGS) -I/home/pi/TD2/TPF/inc -c sequence.c
main.o: main.c
	$(CC) $(CFLAGS) -I/home/pi/TD2/TPF/inc -c main.c

clean:
	rm -f *.o main
