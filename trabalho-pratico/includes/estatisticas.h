#ifndef estatisticas_h
#define estatisticas_h
#include <stdio.h>
#include <stdlib.h>
#include "parseusers.h"
#include "parsedrivers.h"
#include "parserides.h"
#include "structsaux.h"

int query2est(DRIVER *driverarray, RIDE *ridearray,  DRIVERMEDIA *avs);
void query7est(DRIVER *driverarray, RIDE *ridearray, RIDE2 *lisboa, RIDE2 *braga, RIDE2 *porto, RIDE2 *faro, RIDE2 *setubal, CITYMEDIA *lisboaavs, CITYMEDIA *bragaavs, CITYMEDIA *portoavs, CITYMEDIA *faroavs, CITYMEDIA *setubalavs);
void avs(DRIVER *driverarray, RIDE *ridearray, RIDE2 *cityviagens, CITYMEDIA *avs, int pos);

#endif