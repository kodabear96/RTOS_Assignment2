#ifndef SAVETIME_H
#define SAVETIME_H

#include <sys/time.h>
#include "SharedMemory.h"

//saves current time as time start
void startTimer();

//saves current time as time end
void endTimer();

//calculates difference in sec between start/end
double calculateTime(struct timeval startTime, struct timeval endTime);

//save time difference to shared memory
void saveTime();

#endif
