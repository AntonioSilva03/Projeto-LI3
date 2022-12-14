#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/parsedrivers.h"

struct drivers
{
    int id;
    char *name;
    char *birthdate;
    char gender;
    char *car_class;
    //char *licenseplate;
    char *city;
    char *accountcreation;
    char *accountstatus;
};

DRIVER *new_driverarray()
{
    DRIVER *driversarray = malloc(sizeof *driversarray * MAX_DRIVER);
    return driversarray;
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