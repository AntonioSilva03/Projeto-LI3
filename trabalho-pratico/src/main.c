#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/data.h"
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
        query3(userarray, ridearray, query, output);
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
    FILE *output = fopen("../Resultados/output.txt", "w");

    char line[BUFSIZ];
    FILE *input = fopen(argv[2], "r");
    while (feof(input) != 1)
    {
        if (fgets(line, BUFSIZ, input) != 0)
        {
            char query[BUFSIZ];
            strcpy(query, line);
            int queryid = getquery(query);
            handle(userarray, driverarray, ridearray, queryid, line, output);
        }
    }
    return 0;
}