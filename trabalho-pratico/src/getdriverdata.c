#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/getdriverdata.h"
#include "../includes/getdriverdata.h"

struct drivers
{
    int id;
    char *name;
    char *birthdate;
    char gender;
    char *car_class;
    // char *licenseplate;
    char *city;
    char *accountcreation;
    char *accountstatus;
};

int get_iddriver(DRIVER *driverarray, int pos, char *type) // driver
{
    int id;
    id = driverarray[pos]->id;
    return id;
}
char *get_namedriver(DRIVER *driverarray, int pos, char *type) // driver
{
    char *name;
    name = strdup(driverarray[pos]->name);
    return name;
}
char *get_birthdatedriver(DRIVER *driverarray, int pos, char *type) // driver
{
    char *birthdate;
    birthdate = strdup(driverarray[pos]->birthdate);
    return birthdate;
}
char get_genderdriver(DRIVER *driverarray, int pos, char *type) // driver
{
    char gender;
    gender = driverarray[pos]->gender;
    return gender;
}
char *get_carclass(DRIVER *driverarray, int pos) // driver
{
    char *carcalss;
    carcalss = strdup(driverarray[pos]->car_class);
    return carcalss;
}
char *get_citydriver(DRIVER *driverarray, int pos, char *type) // driver and rides
{
    char *city;
    city = strdup(driverarray[pos]->city);
    return city;
}
char *get_accountcreationdriver(DRIVER *driverarray, int pos, char *type) // driver
{
    char *acccreation;
    acccreation = strdup(driverarray[pos]->accountcreation);
    return acccreation;
}
char *get_accountstatusdriver(DRIVER *driverarray, int pos, char *type) // driver
{
    char *accstatus;
    accstatus = strdup(driverarray[pos]->accountstatus);
    return accstatus;
}