#ifndef parsedrivers_h
#define parsedrivers_h
#define MAX_DRIVER 10000
#include <stdio.h>
#include <stdlib.h>

typedef struct drivers *DRIVER;

DRIVER *new_driverarray();

void parsedrivers(FILE *drivers, DRIVER *driverarray);

#endif