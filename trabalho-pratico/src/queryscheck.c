#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/queryscheck.h"
#include "../includes/querys.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/estatisticas.h"
#include "../includes/getdriverdata.h"
#include "../includes/getridedata.h"
// #include "../includes/data.h"

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
void query6check(RIDE *ridearray, char query[], FILE *output, RIDE2 *lisboa, RIDE2 *braga, RIDE2 *porto, RIDE2 *faro, RIDE2 *setubal)
{
    char *city;
    strtok(query, " ");
    city = strtok(NULL, " ");
    if (strcmp("Lisboa", city) == 0)
    {
        query6(ridearray, lisboa, query, output);
    }
    else if (strcmp("Braga", city) == 0)
    {
        query6(ridearray, braga, query, output);
    }
    else if (strcmp("Porto", city) == 0)
    {
        query6(ridearray, porto, query, output);
    }
    else if (strcmp("Faro", city) == 0)
    {
        query6(ridearray, faro, query, output);
    }
    else if (strcmp("Setúbal", city) == 0)
    {
        query6(ridearray, setubal, query, output);
    }
}
void query7check(DRIVER *driverarray, RIDE *ridearray, CITYMEDIA *lisboaavs, CITYMEDIA *bragaavs, CITYMEDIA *portoavs, CITYMEDIA *faroavs, CITYMEDIA *setubalavs, char query[], FILE *output, RIDE2 *lisboa, RIDE2 *braga, RIDE2 *porto, RIDE2 *faro, RIDE2 *setubal)
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
