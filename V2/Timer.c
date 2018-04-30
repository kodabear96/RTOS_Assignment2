#include "Timer.h"

//GLOBALS
struct timeval startTime ,endTime; //start and end time

//FUNCTIONS
void startTimer()
{
	 /* get start time */
	 gettimeofday(&startTime , NULL);
}

void endTimer()
{
	/* get end time */
	 gettimeofday(&endTime , NULL);
}

double calculateTime(struct timeval startTime, struct timeval endTime)
{
	/* retrieve total seconds and milliseconds and add together */
	 double totalSeconds= endTime.tv_sec - startTime.tv_sec;
	 double totalMicroSeconds = endTime.tv_usec - startTime.tv_usec;
	/* milliseconds are divided by 10^-6 to convert to seconds */
	return  (totalSeconds + totalMicroSeconds/((double)1000000));
}

void saveTime()
{
	/* 1. create shared memory */
	initialiseSharedMemory();
	
	/* 2. calculate time */
	double totalTime = calculateTime(startTime, endTime);

	/* 3. write time to shared memory */
	writeDoubleToMemory(totalTime);
}
