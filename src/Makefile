#Variables
CC = gcc
CFLAGS = -Wall -Werror -g
LIBS = -lwiringPi
ASM = as
ASMFLAGS = -g
#Rules
all: main

main: main.o sequence.o util.o setDelay.o
	$(CC) $(CFLAGS) -o main main.o sequence.o util.o setDelay.o $(LIBS)
util.o: util.c
	$(CC) $(CFLAGS) -I/home/pi/TD2/TPF/inc -c util.c 
sequence.o: sequence.c
	$(CC) $(CFLAGS) -I/home/pi/TD2/TPF/inc -c sequence.c
main.o: main.c
	$(CC) $(CFLAGS) -I/home/pi/TD2/TPF/inc -c main.c
	
setDelay.o: setDelay.s
	$(ASM) $(ASMFLAGS) -o setDelay.o setDelay.s

clean:
	rm -f *.o main
