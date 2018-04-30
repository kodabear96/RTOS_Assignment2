#Makefile for both Prg_1 and Prg_2 including packages SharedMemory whic his used by both programs and Timer/Threads wihich is used by Prg_1

CC = gcc
CFLAGS = -Wall -o2
# Wall enables all compiler's warning messages
# o2 - optimisation: that breaks wraparound arithmetic
.c.o:	
	$(CC) $(CFLAGS) -c $*.c #-c source file

all:	Prg_1 Prg_2 test clean 

SharedMemory.o:	SharedMemory.c SharedMemory.h
	$(CC) -c SharedMemory.c

Timer.o: Timer.c Timer.h
	$(CC) -c Timer.c 

Threads.o:	Threads.c Threads.h
	$(CC) -c Threads.c

Prg_1: SharedMemory.o Timer.o Threads.o Prg_1.o 
	$(CC) -o Prg_1 Prg_1.c SharedMemory.o Timer.o Threads.o  -lrt

Prg_2: SharedMemory.o Prg_2.o
	$(CC) -o Prg_2 Prg_2.c SharedMemory.o -lrt

clean:
	rm -rf *.o Prg_1 Prg_2

test: test1 test2

test1:
	./Prg_1
test2:
	./Prg_2
