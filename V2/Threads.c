#include "Threads.h"

//CONSTANTS
#define LINELENGTH 256 //256 is ideal text file line length

//STRUCTS
struct LineData //shared by both thread B & thread C
{
  char strLine[LINELENGTH];
};

//GLOBALS
pthread_mutex_t Mutex; // Mutex lock using for shared variables e.g. lineData
sem_t Semaphore_Write, Semaphore_Read, Semaphore_Justify; // Semaphores that control threads
pthread_t threadIdA, threadIdB, threadIdC; //Thread Ids

int fileDescriptor[2]; //Array to store file descriptor
struct LineData lineData; //storage struct used by threads B & C

int endOfFile;// signals threads to finish (0 - hasn't been reached, 1 - has been)

//FUNCTIONS
void initialiseThreads() {

  /* Initialise mutex lock */
  pthread_mutex_init(&Mutex, NULL);

  /* Initialise semaphores and set to 0 */
  sem_init(&Semaphore_Write, 0, 0);
  sem_init(&Semaphore_Read, 0, 0);
  sem_init(&Semaphore_Justify, 0, 0);

  /* Create thread attributes */
  pthread_attr_t attr;

  /* Initialise thread attributes */
  pthread_attr_init(&attr);

  /* Create threads */
  pthread_create(&threadIdA, &attr, &threadA, NULL);
  pthread_create(&threadIdB, &attr, &threadB, NULL);
  pthread_create(&threadIdC, &attr, &threadC, NULL);

  /* Destroy thread attributes */
  pthread_attr_destroy(&attr);
	
  /* Initialise thread ending variable */
  endOfFile = 0;
}

void *threadA(void *arg) {
  /* Wait for Semaphore_Write */
  sem_wait(&Semaphore_Write);

  /* Mutex lock program */
  pthread_mutex_lock(&Mutex);

  /* Print thread information */
  printf("Thread A running\n");

  /* Open data.txt file */
    FILE* file=fopen("data.txt", "r");

    if (file != NULL) {

      char strLine[LINELENGTH];
      /* while not end of file: read a line */
      while (fgets(strLine, sizeof strLine, file) != NULL) 
	{
	    printf("Original File: %s",strLine);

	    /* write line to pipe */
            write(fileDescriptor[1], strLine, LINELENGTH);
	    
	    /* Release mutex lock */
	    pthread_mutex_unlock(&Mutex);

	    /* Signal Semaphore_Read - starts thread B */
	    sem_post(&Semaphore_Read);

	    /* Wait for Semaphore_Write */
	    sem_wait(&Semaphore_Write);

	    /* Mutex lock program */
	    pthread_mutex_lock(&Mutex);
	    
	     /* Print thread information */
	    printf("Thread A running again!\n");
	}
       /* close the file */
      fclose(file);

      /* Signal that the end of file was reached */
      endOfFile = 1; 

      printf("Thread A says end of file!\n");
    }

  /* Release mutex lock */
  pthread_mutex_unlock(&Mutex);

  /* Signal thread B */
  sem_post(&Semaphore_Read);

  return EXIT_SUCCESS;
}

void *threadB(void *arg) {
  /* Wait for Semaphore_Read */
    sem_wait(&Semaphore_Read);

    static char collectFromPipe[LINELENGTH];
	
  /* While file has not ended */
  while (endOfFile != 1){
    
    /* Mutex lock program */
    pthread_mutex_lock(&Mutex);

    /* Print thread information */
    printf("Thread B running\n");

    /* Read from pipe */
    read(fileDescriptor[0], collectFromPipe, LINELENGTH);
    printf("Passed through pipe: %s", collectFromPipe);

    /* Write new data to global variable */
    strcpy(lineData.strLine, collectFromPipe);

    /* Release mutex lock */
    pthread_mutex_unlock(&Mutex);

    /* Signal Thread C */
    sem_post(&Semaphore_Justify);
    
    /* Wait for Semaphore_Read */
    sem_wait(&Semaphore_Read);
  }
  printf("Thread B says end of file!\n");
   /* Signal Thread C */
   sem_post(&Semaphore_Justify);

  return EXIT_SUCCESS;
}

void *threadC(void *arg) {
  
    /* Wait for Semaphore_Justify */
  sem_wait(&Semaphore_Justify);

/* Open new file or overwite existing */
  FILE* file=fopen("src.txt", "w");
    if (file == NULL)
    {
      printf("Error opening file!\n");
      return;
    }

/* signal to define when the header has been reached */
  int endOfHeader = 0;
  
  while (endOfFile != 1){

  /* Mutex lock program */
  pthread_mutex_lock(&Mutex);

  /* Print thread information */
  printf("Thread C running\n");
  printf("Passed through global: %s", lineData.strLine);

  if(endOfHeader == 1)
{
/* Write line to file */
    fprintf(file, "%s", lineData.strLine);
}

/* if "End_Header" has been reached trigger the flag */
  if(endOfHeader == 0 && strstr(lineData.strLine, "end_header") != NULL)
{
  endOfHeader = 1;
}

  /* Release mutex lock */
  pthread_mutex_unlock(&Mutex);

   /* Signal sempahore A */
   sem_post(&Semaphore_Write);
    
  /* Wait for Semaphore_Justify */
  sem_wait(&Semaphore_Justify);
     
  }
printf("Thread C says end of file!\n");
/* Close the file */
	fclose(file);
  return EXIT_SUCCESS;
}

int initialisePipe()
{
         /* Create pipe */
	 if (pipe(fileDescriptor) == -1) {
	   errno = -1;
	   perror("Pipe creation failed");
	   return EXIT_FAILURE;
	 }
	return EXIT_SUCCESS;
}

int runThreads()
{
	/* Signal Thread A to start */
	 sem_post(&Semaphore_Write);

	 /* Wait for thread termination and status */
	 void *threadResult;
	 if (pthread_join(threadIdA, &threadResult)) {
	   errno = *((int *)threadResult);
	   perror("Thread A failed");
	   return EXIT_FAILURE;
	 } else if (pthread_join(threadIdB, &threadResult)) {
	   errno = *((int *)threadResult);
	   perror("Thread B failed");
	   return EXIT_FAILURE;
	 } else if (pthread_join(threadIdC, &threadResult)) {
	   errno = *((int *)threadResult);
	   perror("Thread C failed");
	   return EXIT_FAILURE;
	 }
	 free(threadResult);
	 return EXIT_SUCCESS;
}
