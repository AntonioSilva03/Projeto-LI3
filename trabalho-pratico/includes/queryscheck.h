#ifndef queryscheck_h
#define queryscheck_h
#include <stdio.h>
#include <stdlib.h>
#include "parseusers.h"
#include "parsedrivers.h"
#include "parserides.h"
//#include "data.h"

void query1check(USER *userarray, DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output);

#endif