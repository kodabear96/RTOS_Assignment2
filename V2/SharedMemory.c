#include "SharedMemory.h"

//CONSTANTS
const int SIZE = 8; //size of shared memory object - set to 8 bytes (size of a double)
const char *name = "shared"; //name of shared memory object
void *ptr; //pointer to shared memory object
int shm_fd;//shared memory file descriptor

//FUNCTIONS
void initialiseSharedMemory()
{
	/* create the shared memory object */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* truncate sets the size of the shared memory */
	ftruncate(shm_fd, SIZE);

	/* memory map the shared memory object */
	ptr = mmap (0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
}

void writeDoubleToMemory(double value)
{	
	//write to the shared memory object
	sprintf(ptr, "%lf", value);
}

const char* retrieveSharedMemory()
{
        /* open the shared memory object*/
	shm_fd = shm_open(name, O_RDONLY, 0666);

	/* memory map the shared memory object */
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	
	/* return the value of the ptr*/
	return ((char *)ptr);
}

void closeSharedMemory()
{
	/*remove shared memory object */
	shm_unlink(name);
}

