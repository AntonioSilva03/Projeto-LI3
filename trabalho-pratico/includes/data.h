#ifndef data_h
#define data_h
#define MAX_USER 100000
#define MAX_DRIVER 10000
#define MAX_RIDE 1000000
#include <stdio.h>
#include <stdlib.h>

typedef struct users *USER;
typedef struct drivers *DRIVER;
typedef struct rides *RIDE;

USER *new_userarray();
DRIVER *new_driverarray();
RIDE *new_ridearray();

void parseusers(FILE *users, USER *userarray);
void parsedrivers(FILE *drivers, DRIVER *driverarray);
void parserides(FILE *rides, RIDE *ridearray);

char *get_username(USER *userarray, int pos); //user
char *get_name(USER *userarray, DRIVER *driverarray, int pos, char *type); //user and driver
char get_gender(USER *userarray, DRIVER *driverarray, int pos, char *type); //user and driver
char *get_birthdate(USER *userarray, DRIVER *driverarray, int pos, char *type); //user and driver
char *get_accountcreation(USER *userarray, DRIVER *driverarray, int pos, char *type); //user and driver
char *get_paymethod(USER *userarray, int pos); //user
char *get_accountstatus(USER *userarray, DRIVER *driverrray, int pos, char *type); //user and driver
int get_id(DRIVER *driverarray, RIDE *ridearray, int pos, char *type); //driver and ride
char *get_carclass(DRIVER *driverarray, int pos); //driver
char *get_licenseplate(DRIVER *driverarray, int pos); //driver
char *get_city(DRIVER *driverarray, RIDE *ridearray, int pos, char *type); //driver and ride
char *get_date(RIDE *ridearray, int pos); //ride
int get_driverid(RIDE *ridearray, int pos); //ride
char *get_user(RIDE *ridearray, int pos); //ride
int get_distance(RIDE *ridearray, int pos); //ride
int get_scoreuser(RIDE *ridearray, int pos); //ride
int get_scoredriver(RIDE *ridearray, int pos); //ride
double get_tip(RIDE *ridearray, int pos); //ride
char *get_comment(RIDE *ridearray, int pos); //ride

#endif