#ifndef setup_h
#define setup_h
#include <stdlib.h>
#include <stdio.h>
#include "parseusers.h"
#include "parsedrivers.h"
#include "parserides.h"
#include "structsaux.h"

int countlines(FILE *fp);
void pathsetup(char *datapath, char *pathuser, char *pathdriver, char *pathride);
void setdimensions(char *path);
void setuparraysaux(USER *userhash, USERDIST *userdist, DRIVERMEDIA *drivermedia);
void parsing(FILE *users, FILE *drivers, FILE *rides, USER *userarray, DRIVER *driverarray, RIDE *ridearray, USER *userhash, USERDIST *userdist, DRIVERMEDIA *drivermedia);
void handle(USER *userarray, USER *userhash, DRIVER *driverarray, RIDE *ridearray, int queryid, char query[], FILE *output, DRIVERMEDIA *drivermedia, USERDIST *userdist, RIDE2 *ride2, int sizequery2, CITYMEDIA *lisboaavs, CITYMEDIA *bragaavs, CITYMEDIA *portoavs, CITYMEDIA *faroavs, CITYMEDIA *setubalavs, CITYMEDIA *coimbraavs, CITYMEDIA *vila_realavs, RIDE2 *lisboa, RIDE2 *braga, RIDE2 *porto, RIDE2 *faro, RIDE2 *setubal, RIDE2 *coimbra, RIDE2 *vila_real);

#endif