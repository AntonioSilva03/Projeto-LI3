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
#include "../includes/getuserdata.h"
#include "../includes/interativo.h"
#include "../includes/setup.h"
#include "../includes/tests.h"

int maxuser = 100000;
int maxdriver = 10000;
int maxride = 1000000;
int interativo = 0;
int testes = 0;

int getquery(char query[])
{
    int queryid;
    char *token = strtok(query, " ");
    sscanf(token, "%d", &queryid);
    return queryid;
}
int main(int argc, char *argv[])
{
    char *datapath;
    char *pathuser = malloc(500);
    char *pathdriver = malloc(500);
    char *pathride = malloc(500);
    FILE *users;
    FILE *drivers;
    FILE *rides;
    if(strcmp(argv[0], "./programa-testes") == 0)
    {
        testes = 1;
    }
    if (argc == 1)
    {
        interativo = 1;
        iniciointerativo();
        datapath = getfilepath();
        if (datapath == NULL)
        {
            printf("Nenhum caminho valido introduzido.\n");
            return 0;
        }
        printf("\n");
        printf("A carregar ficheiros de dados...\n");
        pathsetup(datapath, pathuser, pathdriver, pathride);
        users = fopen(pathuser, "r");
        drivers = fopen(pathdriver, "r");
        rides = fopen(pathride, "r");
        setdimensions(pathuser);
    }
    else
    {
        datapath = argv[1];
        pathsetup(datapath, pathuser, pathdriver, pathride);
        users = fopen(pathuser, "r");
        drivers = fopen(pathdriver, "r");
        rides = fopen(pathride, "r");
        setdimensions(pathuser);
    }
    USER *userarray = new_userarray();
    DRIVER *driverarray = new_driverarray();
    RIDE *ridearray = new_ridearray();
    USER *userhash = malloc(sizeof *userhash * (maxride + 1));
    USERDIST *userdist = malloc(sizeof *userdist * (maxride + 1));
    DRIVERMEDIA *drivermedia = malloc(sizeof *drivermedia * (maxdriver + 1));

    RIDE2 *ride2 = malloc(sizeof *ride2 * (maxride + 1));
    CITYMEDIA *citymedia = malloc(sizeof *citymedia * (maxuser + 1));

    RIDE2 *lisboa = malloc(sizeof *lisboa * (maxride + 1));
    RIDE2 *braga = malloc(sizeof *braga * (maxride + 1));
    RIDE2 *porto = malloc(sizeof *porto * (maxride + 1));
    RIDE2 *faro = malloc(sizeof *faro * (maxride + 1));
    RIDE2 *setubal = malloc(sizeof *setubal * (maxride + 1));
    RIDE2 *coimbra = malloc(sizeof *coimbra * (maxride + 1));
    RIDE2 *vila_real = malloc(sizeof *vila_real * (maxride + 1));
    CITYMEDIA *lisboaavs = malloc(sizeof *lisboaavs * (maxdriver + 1));
    CITYMEDIA *bragaavs = malloc(sizeof *bragaavs * (maxdriver + 1));
    CITYMEDIA *portoavs = malloc(sizeof *portoavs * (maxdriver + 1));
    CITYMEDIA *faroavs = malloc(sizeof *faroavs * (maxdriver + 1));
    CITYMEDIA *setubalavs = malloc(sizeof *setubalavs * (maxdriver + 1));
    CITYMEDIA *coimbraavs = malloc(sizeof *coimbraavs * (maxdriver + 1));
    CITYMEDIA *vila_realavs = malloc(sizeof *vila_realavs * (maxdriver + 1));
    if (argc == 1)
    {
        setuparraysaux(userhash, userdist, drivermedia);
        parsing(users, drivers, rides, userarray, driverarray, ridearray, userhash, userdist, drivermedia);
        printf("A criar estatísticas de dados...\n");

        int sizequery2 = query2est(driverarray, ridearray, drivermedia);
        query3est(userhash, userdist, ridearray);
        query7est(driverarray, ridearray, lisboa, braga, porto, faro, setubal, coimbra, vila_real, lisboaavs, bragaavs, portoavs, faroavs, setubalavs, coimbraavs, vila_realavs);
        menu();
        char line[BUFSIZ];
        printf("\nIntroduza query ou 0 para sair: ");
        while(execucao(line) != NULL)
        {
            char aux[BUFSIZ];
            strcpy(aux, line);
            int queryid = getquery(aux);
            handle(userarray, userhash, driverarray, ridearray, queryid, line, NULL, drivermedia, userdist, ride2, sizequery2, lisboaavs, bragaavs, portoavs, faroavs, setubalavs, coimbraavs, vila_realavs, lisboa, braga, porto, faro, setubal, coimbra, vila_real);
        }
        fiminterativo();
        goto frees;
        return 0;
    }
    setuparraysaux(userhash, userdist, drivermedia);
    parsing(users, drivers, rides, userarray, driverarray, ridearray, userhash, userdist, drivermedia);

    char line[BUFSIZ];
    FILE *input = fopen(argv[2], "r");
    char *filename = malloc(BUFSIZ);
    int it = 1;

    int sizequery2 = query2est(driverarray, ridearray, drivermedia);
    query3est(userhash, userdist, ridearray);
    query7est(driverarray, ridearray, lisboa, braga, porto, faro, setubal, coimbra, vila_real, lisboaavs, bragaavs, portoavs, faroavs, setubalavs, coimbraavs, vila_realavs);
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
            handle(userarray, userhash, driverarray, ridearray, queryid, line, output, drivermedia, userdist, ride2, sizequery2, lisboaavs, bragaavs, portoavs, faroavs, setubalavs, coimbraavs, vila_realavs, lisboa, braga, porto, faro, setubal, coimbra, vila_real);
            if (testes == 1)
            {
                FILE *outputtestes = fopen(filepath, "r");
                compare(outputtestes, argv[3], filename, it);
            }
            it++;
        }
    }
    frees:
    freeuserarray(userarray);
    freedriverarray(driverarray);
    freeridearray(ridearray);
    free(userhash);
    free(drivermedia);
    free(userdist);
    free(ride2);
    free(citymedia);
    free(lisboa);
    free(braga);
    free(porto);
    free(faro);
    free(setubal);
    free(coimbra);
    free(vila_real);
    free(lisboaavs);
    free(bragaavs);
    free(portoavs);
    free(faroavs);
    free(setubalavs);
    free(coimbraavs);
    free(vila_realavs);
    return 0;
}