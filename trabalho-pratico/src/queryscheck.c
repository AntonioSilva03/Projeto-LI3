#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/queryscheck.h"
#include "../includes/querys.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
//#include "../includes/data.h"

void query1check(USER *userarray, DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output)
{
    int intID;
    char *ID = strtok(query, " ");
    ID = strtok(NULL, " ");
    char *userID = strtok(ID, "\n");
    if (sscanf(ID, "%d", &intID) == 1)
    {
        query1driver(driverarray, ridearray, intID, output);
    }
    else
    {
        query1user(userarray, driverarray, ridearray, userID, output);
    }
}
void query7check(CITYMEDIA *lisboaavs, CITYMEDIA *bragaavs , CITYMEDIA *portoavs , CITYMEDIA *faroavs , CITYMEDIA *setubalavs, char query[], FILE *output)
{
    int N;
    char *ID;
    char *city;
    strtok(query, " ");
    ID = strtok(NULL, " ");
    sscanf(ID, "%d", &N);
    city = strtok(NULL, "\n");
    if (strcmp(city, "Lisboa") == 0)
    {
        query7(output, lisboaavs, N);
    }
    else if (strcmp(city, "Braga") == 0)
    {
        query7(output, bragaavs, N);
    }
    else if (strcmp(city, "Porto") == 0)
    {
        query7(output, portoavs, N);
    }
    else if (strcmp(city, "Faro") == 0)
    {
        query7(output, faroavs, N);
    }
    else if (strcmp(city, "Setúbal") == 0)
    {
        query7(output, setubalavs, N);
    }
}
