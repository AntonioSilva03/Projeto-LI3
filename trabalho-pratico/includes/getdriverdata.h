#ifndef getdriverdata_h
#define getdriverdata_h
#include "parsedrivers.h"

int driverisnull(DRIVER *driverarray, int pos);
int get_iddriver(DRIVER *driverarray, int pos, char *type);
char *get_namedriver(DRIVER *driverarray, int pos, char *type);
char *get_birthdatedriver(DRIVER *driverarray, int pos, char *type);
char get_genderdriver(DRIVER *driverarray, int pos, char *type);
char *get_carclass(DRIVER *driverarray, int pos);
char *get_accountcreationdriver(DRIVER *driverarray, int pos, char *type);
char *get_accountstatusdriver(DRIVER *driverarray, int pos, char *type);

#endif