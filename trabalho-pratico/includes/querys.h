#ifndef querys_h
#define querys_h
#include <stdio.h>
#include <stdlib.h>
#include "parseusers.h"
#include "parsedrivers.h"
#include "parserides.h"
//#include "data.h"

void query1user(USER *userarray, DRIVER *driverarray, RIDE *ridearray, char *ID, FILE *output);
void query1driver(DRIVER *driverarray, RIDE *ridearray, int id, FILE *output);
void query2(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output);
void query3(USER *userarray, RIDE *ridearray, char query[], FILE *output);
void query4(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output);
void query5(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output);
void query6(RIDE *ridearray, char query[], FILE *output);
void query7(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output);
void query9(RIDE *ridearray, char query[], FILE *output);

#endif