#include "Timer.h"
#include "Threads.h"

int main()
{
	//1. start timer
	 startTimer();

	//2. initialise all components
	 if (initialisePipe() == EXIT_FAILURE) return EXIT_FAILURE;

	 initialiseThreads();

	//3. run program
	 if (runThreads() == EXIT_FAILURE) return EXIT_FAILURE;

	//4. stop timer
	 endTimer();

	//5. write to memory
	 saveTime();

	 return EXIT_SUCCESS;
}




