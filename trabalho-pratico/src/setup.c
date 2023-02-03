#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/setup.h"
#include "../includes/maxs.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/structsaux.h"
#include "../includes/getuserdata.h"
#include "../includes/queryscheck.h"
#include "../includes/querys.h"

int countlines(FILE *fp)
{
    int ch = 0;
    int lines = 0;

    if (fp == NULL)
        return 0;

    lines++;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }
    return lines;
}
void pathsetup(char *datapath, char *pathuser, char *pathdriver, char *pathride)
{
    char fileuser[500] = "/users.csv";
    char filedriver[500] = "/drivers.csv";
    char fileride[500] = "/rides.csv";
    strcpy(pathuser, datapath);
    strcat(pathuser, fileuser);
    strcpy(pathdriver, datapath);
    strcat(pathdriver, filedriver);
    strcpy(pathride, datapath);
    strcat(pathride, fileride);
}
void setdimensions(char *path)
{
    FILE *file = fopen(path, "r");
    int lines = countlines(file);
    if (lines > maxuser + 2)
    {
        maxuser = maxuser * 10;
        maxdriver = maxdriver * 10;
        maxride = maxride * 10;
    }
}
void setuparraysaux(USER *userhash, USERDIST *userdist, DRIVERMEDIA *drivermedia)
{
    for (int i = 0; i < maxride; i++)
    {
        userhash[i] = NULL;
        userdist[i].username = NULL;
    }
    for (int i = 1; i <= maxdriver; i++)
    {
        drivermedia[i].id = i;
        drivermedia[i].datarecente = "01/01/1990";
        drivermedia[i].somascore = 0;
        drivermedia[i].nviagens = 0;
    }
}
void parsing(FILE *users, FILE *drivers, FILE *rides, USER *userarray, DRIVER *driverarray, RIDE *ridearray, USER *userhash, USERDIST *userdist, DRIVERMEDIA *drivermedia)
{
    parseusers(users, userarray, userhash);
    fclose(users);
    for (int i = 0; i < maxride; i++)
    {
        if(userisnull(userhash, i) == 0)continue;
        userdist[i].username = get_username(userhash, i);
        userdist[i].nome = get_nameuser(userhash, i, "user");
        userdist[i].viagemrecente = "01/01/1990";
    }
    parsedrivers(drivers, driverarray);
    fclose(drivers);
    parserides(rides, ridearray, drivermedia, driverarray);
    fclose(rides);
}
void handle(USER *userarray, USER *userhash, DRIVER *driverarray, RIDE *ridearray, int queryid, char query[], FILE *output, DRIVERMEDIA *drivermedia, USERDIST *userdist, RIDE2 *ride2, int sizequery2, CITYMEDIA *lisboaavs, CITYMEDIA *bragaavs, CITYMEDIA *portoavs, CITYMEDIA *faroavs, CITYMEDIA *setubalavs, CITYMEDIA *coimbraavs, CITYMEDIA *vila_realavs, RIDE2 *lisboa, RIDE2 *braga, RIDE2 *porto, RIDE2 *faro, RIDE2 *setubal, RIDE2 *coimbra, RIDE2 *vila_real)
{
    switch (queryid)
    {
    case 1:
        query1check(userarray, driverarray, ridearray, query, output);
        break;
    case 2:
        query2(query, output, drivermedia, sizequery2);
        break;
    case 3:
        query3(userdist, query, output);
        break;
    case 4:
        query4(driverarray, ridearray, query, output);
        break;
    case 5:
        query5(driverarray, ridearray, query, output);
        break;
    case 6:
        query6check(ridearray, query, output, lisboa, braga, porto, faro, setubal, coimbra, vila_real);
        break;
    case 7:
        query7check(driverarray, ridearray, lisboaavs, bragaavs, portoavs, faroavs, setubalavs, coimbraavs, vila_realavs, query, output, lisboa, braga, porto, faro, setubal, coimbra, vila_real);
        break;
    case 8:
        query8(query, output, userhash, driverarray, ridearray);
        break;
    case 9:
        query9(ridearray, query, output, ride2);
    default:
        break;
    }
}