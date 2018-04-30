#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

//Initialses threads, semaphores, mutexes and shared variables
void initialiseThreads();

//Thread A function: reads from file and passes to pipe
void *threadA(void *arg);

//Thread B function: reads from pipe and passes to global struct
void *threadB(void *arg);

//Thread C function: reads from global struct, filters out header and writes to src.txt file
void *threadC(void *arg);

//Initialse the pipe used by threads A & B
int initialisePipe();

//Run the threads - returns 1 if fail
int runThreads();

#endif
