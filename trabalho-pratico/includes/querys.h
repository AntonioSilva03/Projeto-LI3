#ifndef querys_h
#define querys_h
#include <stdio.h>
#include <stdlib.h>
#include "parseusers.h"
#include "parsedrivers.h"
#include "parserides.h"
#include "structsaux.h"
//#include "data.h"

void query1user(USER *userarray, DRIVER *driverarray, RIDE *ridearray, char *ID, FILE *output);
void query1driver(DRIVER *driverarray, RIDE *ridearray, int id, FILE *output);
void query2(char query[], FILE *output, DRIVERMEDIA *avs, int t);
void query3(USERDIST *userdist, char query[], FILE* output);
void query4(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output);
void query5(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output);
void query6(RIDE *ridearray, RIDE2 *cityviagens, char query[], FILE *output);
void query7(FILE *output, CITYMEDIA *avs , int N);
void query8(char query[], FILE *output, USER *userhash, DRIVER *driverarray, RIDE *ridearray);
void query9(RIDE *ridearray, char query[], FILE *output, RIDE2 *ride2);

#endif