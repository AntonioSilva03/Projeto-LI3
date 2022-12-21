#ifndef parserides_h
#define parserides_h
#define MAX_RIDE 1000000
#include <stdio.h>
#include <stdlib.h>

typedef struct rides *RIDE;

#include "structsaux.h"

RIDE *new_ridearray();

void scoremedia(DRIVERMEDIA *drivermedia, RIDE ride);
void parserides(FILE *rides, RIDE *ridearray, DRIVERMEDIA *drivermedia);

#endif