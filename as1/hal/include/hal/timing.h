#ifndef TIMING_H
#define TIMING_H
#include <stdio.h> // fopen, fprintf, fclose, perror
#include <stdlib.h>  // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdbool.h>
#include <time.h>


static long long getTimeInMs(void);

static void sleepForMs(long long delayInMs);



#endif

