#Makefile

CC = gcc
CFLAGS = -Wall -o2
# Wall enables all compiler's warning messages
#o2 - optimisation: that breaks wraparound arithmetic
.c.o:	
	$(CC) $(CFLAGS) -c $*.c #-c source file

all:	Prg_1 Prg_2 clean test

Prg_1: Prg_1.o
	$(CC) -o Prg_1 Prg_1.c -lrt

Prg_2: Prg_2.o
	$(CC) -o Prg_2 Prg_2.c -lrt

clean:
	rm -rf *.o core 

test: test1 test2

test1:
	./Prg_1
test2:
	./Prg_2
