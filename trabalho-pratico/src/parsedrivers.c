#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../includes/parsedrivers.h"
#include "../includes/getdriverdata.h"
#include "../includes/calculos.h"

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
    DRIVER *driversarray = malloc(sizeof *driversarray * (maxdriver + 1));
    return driversarray;
}
void freedriverarray(DRIVER *driverarray)
{
    for (int i = 0; i <= maxdriver; i++)
    {
        if (driverisnull(driverarray, i) != 0)
        {
            free(driverarray[i]);
        }
    }
    free(driverarray);
}

int verificacaodrivers(char *line)
{
    if (line[0] == ';' || line[13] == ';')
    {
        return 0;
    }
    DRIVER driver = malloc(sizeof *driver);
    int context = 1;
    char *token = strtok(line, ";");
    while (token != NULL)
    {
        if (context == 1)
        {
        }
        else if (context == 2)
        {
            driver->name = strdup(token);
            if (strlen(driver->name) == 0 || driver->name[0] == '\0')
            {
                free(driver->name);
                free(line);
                free(driver);
                return 0;
            }
            free(driver->name);
        }
        else if (context == 3)
        {
            driver->birthdate = strdup(token);
            if (strlen(driver->birthdate) != 10 || driver->birthdate[2] != '/' || driver->birthdate[5] != '/')
            {
                free(driver->birthdate);
                free(line);
                free(driver);
                return 0;
            }
            int day = atoi(driver->birthdate);
            int month = atoi(driver->birthdate + 3);
            int year = atoi(driver->birthdate + 6);
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
            {
                free(driver->birthdate);
                free(line);
                free(driver);
                return 0;
            }
            free(driver->birthdate);
        }
        else if (context == 4)
        {
            char *aux = mystrupr(strdup(token));
            if (strcmp(aux, "BASIC") == 0 || strcmp(aux, "GREEN") == 0 || strcmp(aux, "PREMIUM") == 0)
            {
                free(aux);
                free(line);
                free(driver);
                return 0;
            }
            free(aux);
        }
        else if (context == 5)
        {
            driver->car_class = strdup(token);
            char *aux = mystrupr(driver->car_class);
            if (strcmp(aux, "BASIC") != 0 && strcmp(aux, "GREEN") != 0 && strcmp(aux, "PREMIUM") != 0)
            {
                free(driver->car_class);
                free(line);
                free(driver);
                return 0;
            }
            free(driver->car_class);
        }
        else if (context == 6)
        {
            if (strlen(token) != 8 || token[2] != '-' || token[5] != '-')
            {
                free(line);
                free(driver);
                return 0;
            }
        }
        else if (context == 7)
        {
            driver->city = strdup(token);
            if (strlen(driver->city) < 2)
            {
                free(driver->city);
                free(line);
                free(driver);
                return 0;
            }
            free(driver->city);
        }
        else if (context == 8)
        {
            driver->accountcreation = strdup(token);
            if (strlen(driver->accountcreation) != 10 || driver->accountcreation[2] != '/' || driver->accountcreation[5] != '/')
            {
                free(driver->accountcreation);
                free(line);
                free(driver);
                return 0;
            }
            int day = atoi(driver->accountcreation);
            int month = atoi(driver->accountcreation + 3);
            int year = atoi(driver->accountcreation + 6);
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
            {
                free(driver->accountcreation);
                free(line);
                free(driver);
                return 0;
            }
            free(driver->accountcreation);
        }
        else if (context == 9)
        {
            driver->accountstatus = strdup(token);
            char *aux = mystrupr(driver->accountstatus);
            if (strcmp(aux, "ACTIVE\n") != 0 && strcmp(aux, "INACTIVE\n") != 0)
            {
                free(driver->accountstatus);
                free(line);
                free(driver);
                return 0;
            }
            free(driver->accountstatus);
        }
        context++;
        token = strtok(NULL, ";");
    }
    free(driver);
    free(line);
    return 1;
}

void parsedrivers(FILE *drivers, DRIVER *driversarray)
{
    for (int i = 0; i <= maxdriver; i++)
    {
        driversarray[i] = NULL;
    }
    char str[BUFSIZ];
    int arraypos = 0;
    while (feof(drivers) != 1)
    {
        if (fgets(str, BUFSIZ, drivers) != 0)
        {
            DRIVER driver = malloc(sizeof *driver);
            char *line = strdup(str);
            if (arraypos > 0 && verificacaodrivers(line) == 0)
            {
                free(driver);
                continue;
            }
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
                    char *aux = mystrupr(strdup(token));
                    if (strcmp(aux, "BASIC") == 0)
                    {
                        driver->car_class = "basic";
                    }
                    else if (strcmp(aux, "GREEN") == 0)
                    {
                        driver->car_class = "green";
                    }
                    else if (strcmp(aux, "PREMIUM") == 0)
                    {
                        driver->car_class = "premium";
                    }
                    else driver->car_class = strdup(token);
                    free(aux);
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
                    char *aux = mystrupr(strdup(token));
                    if (strcmp(aux, "ACTIVE\n") == 0)
                    {
                        driver->accountstatus = "active\n";
                    }
                    else if (strcmp(aux, "INACTIVE\n") == 0)
                    {
                        driver->accountstatus = "inactive\n";
                    }
                    else
                        driver->accountstatus = strdup(token);
                    free(aux);
                }
                context++;
                token = strtok(NULL, ";");
            }
            if (arraypos > 0)
                driversarray[driver->id] = driver;

            else
                driversarray[0] = driver;
            arraypos++;
        }
    }
}