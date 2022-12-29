#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "../includes/data.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/queryscheck.h"
#include "../includes/querys.h"
#include "../includes/structsaux.h"
#include "../includes/estatisticas.h"
#include "../includes/maxs.h"

int maxuser = 100000;
int maxdriver = 10000;
int maxride = 1000000;

int getquery(char query[])
{
    int queryid;
    char *token = strtok(query, " ");
    sscanf(token, "%d", &queryid);
    return queryid;
}
void handle(USER *userarray, DRIVER *driverarray, RIDE *ridearray, int queryid, char query[], FILE *output, DRIVERMEDIA *drivermedia, USERDIST *userdist, RIDE2 *ride2, int sizequery2, CITYMEDIA *lisboaavs, CITYMEDIA *bragaavs , CITYMEDIA *portoavs , CITYMEDIA *faroavs , CITYMEDIA *setubalavs, RIDE2 *lisboa, RIDE2 *braga, RIDE2 *porto, RIDE2 *faro, RIDE2 *setubal)
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
        break;
    case 4:
        query4(driverarray, ridearray, query, output);
        break;
    case 5:
        query5(driverarray, ridearray, query, output);
        break;
    case 6:
        query6check(ridearray, query, output, lisboa, braga, porto, faro, setubal);
        break;
    case 7:
        query7check(driverarray, ridearray, lisboaavs, bragaavs, portoavs, faroavs, setubalavs, query, output, lisboa, braga, porto, faro, setubal);
        break;
    case 8:
        break;
    case 9:
        query9(ridearray, query, output, ride2);
    default:
        break;
    }
}
void estatisticas2(DRIVER *driverarray, RIDE *ridearray, DRIVERMEDIA *drivermedia, int *sizequery2)
{
    *sizequery2 = query2est(driverarray, ridearray, drivermedia);
}
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

    FILE *usersaux = fopen(pathuser, "r");
    int lines = countlines(usersaux);
    if (lines > maxuser + 2)
    {
        maxuser = maxuser * 10;
        maxdriver = maxdriver * 10;
        maxride = maxride * 10;
    }
    fclose(usersaux);
    FILE *users = fopen(pathuser, "r");
    FILE *drivers = fopen(pathdriver, "r");
    FILE *rides = fopen(pathride, "r");
    USER *userarray = new_userarray();
    DRIVER *driverarray = new_driverarray();
    RIDE *ridearray = new_ridearray();
    DRIVERMEDIA *drivermedia = malloc(sizeof *drivermedia * maxdriver);
    for (int i = 1; i <= maxdriver; i++)
    {
        drivermedia[i].id = i;
        drivermedia[i].datarecente = "01/01/1990";
        drivermedia[i].somascore = 0;
        drivermedia[i].nviagens = 0;
    }
    parseusers(users, userarray);
    fclose(users);
    parsedrivers(drivers, driverarray);
    fclose(drivers);
    parserides(rides, ridearray, drivermedia);
    fclose(rides);

    char line[BUFSIZ];
    FILE *input = fopen(argv[2], "r");
    char *filename = malloc(BUFSIZ);
    int it = 1;

    USERDIST *userdist = malloc(sizeof *userdist * maxuser);
    RIDE2 *ride2 = malloc(sizeof *ride2 * maxride);
    CITYMEDIA *citymedia = malloc(sizeof *citymedia * maxuser);

    RIDE2 *lisboa = malloc(sizeof *lisboa * maxride);
    RIDE2 *braga = malloc(sizeof *braga * maxride);
    RIDE2 *porto = malloc(sizeof *porto * maxride);
    RIDE2 *faro = malloc(sizeof *faro * maxride);
    RIDE2 *setubal = malloc(sizeof *setubal * maxride);
    CITYMEDIA *lisboaavs = malloc(sizeof *lisboaavs * maxdriver);
    CITYMEDIA *bragaavs = malloc(sizeof *bragaavs * maxdriver);
    CITYMEDIA *portoavs = malloc(sizeof *portoavs * maxdriver);
    CITYMEDIA *faroavs = malloc(sizeof *faroavs * maxdriver);
    CITYMEDIA *setubalavs = malloc(sizeof *setubalavs * maxdriver);

    int sizequery2;
    estatisticas2(driverarray, ridearray, drivermedia, &sizequery2);
    query7est(driverarray, ridearray, lisboa, braga, porto, faro, setubal, lisboaavs, bragaavs, portoavs, faroavs, setubalavs);
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
            handle(userarray, driverarray, ridearray, queryid, line, output, drivermedia, userdist, ride2, sizequery2, lisboaavs, bragaavs, portoavs, faroavs, setubalavs, lisboa, braga, porto, faro, setubal);
            it++;
        }
    }
    free(drivermedia);
    free(userdist);
    free(ride2);
    free(citymedia);
    free(lisboa);
    free(braga);
    free(porto);
    free(faro);
    free(setubal);
    free(lisboaavs);
    free(bragaavs);
    free(portoavs);
    free(faroavs);
    free(setubalavs);
    return 0;
}