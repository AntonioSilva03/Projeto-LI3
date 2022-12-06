#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/data.h"

struct users
{
    char *username;
    char *name;
    char gender;
    char *birthdate;
    char *accountcreation;
    char *paymethod;
    char *accountstatus;
};

struct drivers
{
    int id;
    char *name;
    char *birthdate;
    char gender;
    char *car_class;
    char *licenseplate;
    char *city;
    char *accountcreation;
    char *accountstatus;
};

struct rides
{
    int id;
    char *date;
    int driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    double tip;
    char *comment;
};

USER *new_userarray()
{
    USER *usersarray = malloc(sizeof *usersarray * MAX_USER);
    return usersarray;
}

DRIVER *new_driverarray()
{
    DRIVER *driversarray = malloc(sizeof *driversarray * MAX_DRIVER);
    return driversarray;
}

RIDE *new_ridearray()
{
    RIDE *ridesarray = malloc(sizeof *ridesarray * MAX_RIDE);
    return ridesarray;
}

void parseusers(FILE *users, USER *usersarray)
{
    char str[BUFSIZ];
    int arraypos = 0;
    while (feof(users) != 1)
    {
        if (fgets(str, BUFSIZ, users) != 0)
        {
            USER user = malloc(sizeof *user);
            int context = 1;
            char *token = strtok(str, ";");
            while (token != NULL)
            {
                if (context == 1)
                {
                    user->username = strdup(token);
                }
                else if (context == 2)
                {
                    user->name = strdup(token);
                }
                else if (context == 3)
                {
                    char gender;
                    sscanf(token, "%c", &gender);
                    user->gender = gender;
                }
                else if (context == 4)
                {
                    user->birthdate = strdup(token);
                }
                else if (context == 5)
                {
                    user->accountcreation = strdup(token);
                }
                else if (context == 6)
                {
                    user->paymethod = strdup(token);
                }
                else if (context == 7)
                {
                    user->accountstatus = strdup(token);
                }
                context++;
                token = strtok(NULL, ";");
            }
            usersarray[arraypos] = user;
            arraypos++;
        }
    }
}

void parsedrivers(FILE *drivers, DRIVER *driversarray)
{
    char str[BUFSIZ];
    int arraypos = 0;
    while (feof(drivers) != 1)
    {
        if (fgets(str, BUFSIZ, drivers) != 0)
        {
            DRIVER driver = malloc(sizeof *driver);
            int context = 1;
            char *token = strtok(str, ";");
            while (token != NULL)
            {
                if (context == 1)
                {
                    int id;
                    sscanf(token, "%d", &id);
                    driver->id = id;
                }
                else if (context == 2)
                {
                    driver->name = strdup(token);
                }
                else if (context == 3)
                {
                    driver->birthdate = strdup(token);
                }
                else if (context == 4)
                {
                    char gender;
                    sscanf(token, "%c", &gender);
                    driver->gender = gender;
                }
                else if (context == 5)
                {
                    driver->car_class = strdup(token);
                }
                else if (context == 6)
                {
                    driver->licenseplate = strdup(token);
                }
                else if (context == 7)
                {
                    driver->city = strdup(token);
                }
                else if (context == 8)
                {
                    driver->accountcreation = strdup(token);
                }
                else if (context == 9)
                {
                    driver->accountstatus = strdup(token);
                }
                context++;
                token = strtok(NULL, ";");
            }
            driversarray[arraypos] = driver;
            arraypos++;
        }
    }
}

void parserides(FILE *rides, RIDE *ridesarray)
{
    char str[BUFSIZ];
    int arraypos = 0;
    while (feof(rides) != 1)
    {
        if (fgets(str, BUFSIZ, rides) != 0)
        {
            RIDE ride = malloc(sizeof *ride);
            int context = 1;
            char *token = strtok(str, ";");
            while (token != NULL)
            {
                if (context == 1)
                {
                    int id;
                    sscanf(token, "%d", &id);
                    ride->id = id;
                }
                else if (context == 2)
                {
                    ride->date = strdup(token);
                }
                else if (context == 3)
                {
                    int driver;
                    sscanf(token, "%d", &driver);
                    ride->driver = driver;
                }
                else if (context == 4)
                {
                    ride->user = strdup(token);
                }
                else if (context == 5)
                {
                    ride->city = strdup(token);
                }
                else if (context == 6)
                {
                    int distance;
                    sscanf(token, "%d", &distance);
                    ride->distance = distance;
                }
                else if (context == 7)
                {
                    int scoreuser;
                    sscanf(token, "%d", &scoreuser);
                    ride->score_user = scoreuser;
                }
                else if (context == 8)
                {
                    int scoredriver;
                    sscanf(token, "%d", &scoredriver);
                    ride->score_driver = scoredriver;
                }
                else if (context == 9)
                {
                    double tip;
                    sscanf(token, "%lf", &tip);
                    ride->tip = tip;
                }
                else if (context == 10)
                {
                    ride->comment = strdup(token);
                }
                context++;
                token = strtok(NULL, ";");
            }
            ridesarray[arraypos] = ride;
            arraypos++;
        }
    }
}



char *get_username(USER *userarray, int pos) //user
{
    char *username;
    username = strdup(userarray[pos]->username);
    return username;
}
char *get_name(USER *userarray, DRIVER *driverarray, int pos, char *type) //user and driver
{
    char *name;
    if (strcmp(type, "driver") == 0)
    {
        name = strdup(driverarray[pos]->name);
    }
    else
    {
        name = strdup(userarray[pos]->name);
    }
    return name;
}
char get_gender(USER *userarray, DRIVER *driverarray, int pos, char *type) //user and driver
{
    char gender;
    if (strcmp(type, "driver") == 0)
    {
        gender = driverarray[pos]->gender;
    }
    else
    {
        gender = userarray[pos]->gender;
    }
    return gender;
}
char *get_birthdate(USER *userarray, DRIVER *driverarray, int pos, char *type) //user and driver
{
    char *birthdate;
    if (strcmp(type, "driver") == 0)
    {
        birthdate = strdup(driverarray[pos]->birthdate);
    }
    else
    {
        birthdate = strdup(userarray[pos]->birthdate);
    }
    return birthdate;
}
char *get_accountcreation(USER *userarray, DRIVER *driverarray, int pos, char *type) //user and driver
{
    char *acccreation;
    if (strcmp(type, "driver") == 0)
    {
        acccreation = strdup(driverarray[pos]->accountcreation);
    }
    else
    {
        acccreation = strdup(userarray[pos]->accountcreation);
    }
    return acccreation;
}
char *get_paymethod(USER *userarray, int pos) //user
{
    char *paymethod;
    paymethod = strdup(userarray[pos]->paymethod);
    return paymethod;
}
char *get_accountstatus(USER *userarray, DRIVER *driverarray, int pos, char *type) //user and driver
{
    char *accstatus;
    if (strcmp(type, "driver") == 0)
    {
        accstatus = strdup(driverarray[pos]->accountstatus);
    }
    else
    {
        accstatus = strdup(userarray[pos]->accountstatus);
    }
    return accstatus;
}
int get_id(DRIVER *driverarray, RIDE *ridearray, int pos, char *type) //driver and ride
{
    int id;
    if (strcmp(type, "driver") == 0)
    {
        id = driverarray[pos]->id;
    }
    else
    {
        id = ridearray[pos]->id;
    }
    return id;
}
char *get_carclass(DRIVER *driverarray, int pos) //driver
{
    char *carcalss;
    carcalss = strdup(driverarray[pos]->car_class);
    return carcalss;
}
char *get_licenseplate(DRIVER *driverarray, int pos) //driver
{
    char *licenseplate;
    licenseplate = strdup(driverarray[pos]->licenseplate);
    return licenseplate;
}
char *get_city(DRIVER *driverarray, RIDE *ridearray, int pos, char *type) //driver and rides
{
    char *city;
    if (strcmp(type, "driver") == 0)
    {
        city = strdup(driverarray[pos]->city);
    }
    else
    {
        city = strdup(ridearray[pos]->city);
    }
    return city;
}
char *get_date(RIDE *ridearray, int pos) //ride
{
    char *date;
    date = strdup(ridearray[pos]->date);
    return date;
}
int get_driverid(RIDE *ridearray, int pos) //ride
{
    int driverid;
    driverid = ridearray[pos]->driver;
    return driverid;
}
char *get_user(RIDE *ridearray, int pos) //ride
{
    char *user;
    user = strdup(ridearray[pos]->user);
    return user;
}
int get_distance(RIDE *ridearray, int pos) //ride
{
    int distance;
    distance = ridearray[pos]->distance;
    return distance;
}
int get_scoreuser(RIDE *ridearray, int pos) //ride
{
    int scoreuser;
    scoreuser = ridearray[pos]->score_user;
    return scoreuser;
}
int get_scoredriver(RIDE *ridearray, int pos) //ride
{
    int scoredriver;
    scoredriver = ridearray[pos]->score_driver;
    return scoredriver;
}
double get_tip(RIDE *ridearray, int pos) //ride
{
    double tip;
    tip = ridearray[pos]->tip;
    return tip;
}
char *get_comment(RIDE *ridearray, int pos) //ride
{
    char *comment;
    comment = strdup(ridearray[pos]->comment);
    return comment;
}