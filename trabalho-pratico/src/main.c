#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../includes/data.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/queryscheck.h"
#include "../includes/querys.h"

int getquery(char query[])
{
    int queryid;
    char *token = strtok(query, " ");
    sscanf(token, "%d", &queryid);
    return queryid;
}
void handle(USER *userarray, DRIVER *driverarray, RIDE *ridearray, int queryid, char query[], FILE *output)
{
    switch (queryid)
    {
    case 1:
        query1check(userarray, driverarray, ridearray, query, output);
        break;
    case 2:
        query2(driverarray, ridearray, query, output);
        break;
    case 3:
        break;
    case 4:
        query4(driverarray, ridearray, query, output);
        break;
    case 5:
        query5(driverarray, ridearray, query, output);
        break;
    case 6:
        query6(ridearray, query, output);
        break;
    case 7:
        query7(driverarray, ridearray, query, output);
        break;
    case 8:
        break;
    case 9:
        query9(ridearray, query, output);
    default:
        break;
    }
}
int main(int argc, char *argv[])
{
    char pathuser[BUFSIZ];
    char fileuser[BUFSIZ] = "/users.csv";
    strcpy(pathuser, argv[1]);
    strcat(pathuser, fileuser);
    char pathdriver[BUFSIZ];
    char filedriver[BUFSIZ] = "/drivers.csv";
    strcpy(pathdriver, argv[1]);
    strcat(pathdriver, filedriver);
    char pathride[BUFSIZ];
    char fileride[BUFSIZ] = "/rides.csv";
    strcpy(pathride, argv[1]);
    strcat(pathride, fileride);

    FILE *users = fopen(pathuser, "r");
    FILE *drivers = fopen(pathdriver, "r");
    FILE *rides = fopen(pathride, "r");
    USER *userarray = new_userarray();
    DRIVER *driverarray = new_driverarray();
    RIDE *ridearray = new_ridearray();
    parseusers(users, userarray);
    parsedrivers(drivers, driverarray);
    parserides(rides, ridearray);

    char line[BUFSIZ];
    FILE *input = fopen(argv[2], "r");
    char *filename = malloc(BUFSIZ);
    int it = 1;
    while (feof(input) != 1)
    {
        if (fgets(line, BUFSIZ, input) != 0)
        {
            char filepath[BUFSIZ] = "../trabalho-pratico/Resultados/";
            snprintf(filename, BUFSIZ, "command%d_output.txt", it);
            strcat(filepath, filename);
            FILE *output = fopen(filepath, "w");
            char query[BUFSIZ];
            strcpy(query, line);
            int queryid = getquery(query);
            handle(userarray, driverarray, ridearray, queryid, line, output);
            it++;
        }
    }
    return 0;
}