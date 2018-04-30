//this program reads the information from the shared memory used in prog1 and outputs this information from the memory to the terminal

#include "SharedMemory.h"

int main()
{
	//1. retrieve data from shared memory
	const char* time = retrieveSharedMemory();

	//2. print data
	printf("Time taken for Prg_1: %s seconds\n", time);
	
	//3. close shared memory
	closeSharedMemory();
	
	return EXIT_SUCCESS;
}
