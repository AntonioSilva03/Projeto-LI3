#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/queryscheck.h"
#include "../includes/querys.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/estatisticas.h"
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
        if (lisboaavs[0].activity == NULL)
        {
            int poslisboa = 0;
            while (lisboa[poslisboa].a != NULL)
            {
                poslisboa++;
            }
            avs(driverarray, ridearray, lisboa, lisboaavs, poslisboa);
        }
        query7(output, lisboaavs, N);
    }
    else if (strcmp(city, "Braga") == 0)
    {
        if (bragaavs[0].activity == NULL)
        {
            int posbraga = 0;
            while (braga[posbraga].a != NULL)
            {
                posbraga++;
            }
            avs(driverarray, ridearray, braga, bragaavs, posbraga);
        }
        query7(output, bragaavs, N);
    }
    else if (strcmp(city, "Porto") == 0)
    {
        if (portoavs[0].activity == NULL)
        {
            int posporto = 0;
            while (porto[posporto].a != NULL)
            {
                posporto++;
            }
            avs(driverarray, ridearray, porto, portoavs, posporto);
        }
        query7(output, portoavs, N);
    }
    else if (strcmp(city, "Faro") == 0)
    {
        if (faroavs[0].activity == NULL)
        {
            int posfaro = 0;
            while (faro[posfaro].a != NULL)
            {
                posfaro++;
            }
            avs(driverarray, ridearray, faro, faroavs, posfaro);
        }
        query7(output, faroavs, N);
    }
    else if (strcmp(city, "Setúbal") == 0)
    {
        if (setubalavs[0].activity == NULL)
        {
            int possetubal = 0;
            while (setubal[possetubal].a != NULL)
            {
                possetubal++;
            }
            avs(driverarray, ridearray, setubal, setubalavs, possetubal);
        }
        query7(output, setubalavs, N);
    }
}
