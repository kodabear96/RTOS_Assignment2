#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>

//initialises the shared memory for multiple programs to use
void initialiseSharedMemory();

// writes a double to the shared memory
void writeDoubleToMemory(double value);

//retrieves the data from shared memory in string form
const char* retrieveSharedMemory();

//close shared memory
void closeSharedMemory();

#endif
