#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/queryscheck.h"
#include "../includes/querys.h"
#include "../includes/data.h"

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
