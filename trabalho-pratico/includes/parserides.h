#ifndef parserides_h
#define parserides_h
#define MAX_RIDE 1000000
#include <stdio.h>
#include <stdlib.h>

typedef struct rides *RIDE;

RIDE *new_ridearray();

void parserides(FILE *rides, RIDE *ridearray);

#endif