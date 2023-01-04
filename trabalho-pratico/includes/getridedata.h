#ifndef getridedata_h
#define getridedata_h
#include "parserides.h"

int get_idride(RIDE *ridearray, int pos, char *type); //ride
char *get_date(RIDE *ridearray, int pos); //ride
DATA *get_datatok(RIDE *ridearray, int pos);
int get_driverid(RIDE *ridearray, int pos); //ride
char *get_user(RIDE *ridearray, int pos); //ride
char *get_cityride(RIDE *ridearray, int pos, char *type); //ride
int get_distance(RIDE *ridearray, int pos); //ride
int get_scoreuser(RIDE *ridearray, int pos); //ride
int get_scoredriver(RIDE *ridearray, int pos); //ride
double get_tip(RIDE *ridearray, int pos); //ride
double get_precoviagem(RIDE *ridearray, int pos);
//char *get_comment(RIDE *ridearray, int pos); //ride

#endif