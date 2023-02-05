#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "../includes/data.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/getuserdata.h"
#include "../includes/getdriverdata.h"
#include "../includes/getridedata.h"
#include "../includes/calculos.h"
#include "ctype.h"

char *mystrupr(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = toupper((unsigned char)str[i]);
        i++;
    }
    return str;
}

int idade(char *bdate) // q1
{
    int res;
    int dia;
    int mes;
    int ano;
    char *bdatee = strdup(bdate);
    sscanf(strtok(bdatee, "/"), "%d", &dia);
    sscanf(strtok(NULL, "/"), "%d", &mes);
    sscanf(strtok(NULL, "/"), "%d", &ano);
    res = REFANO - ano;
    if (mes > REFMES)
    {
        res--;
    }
    else if (mes == REFMES)
    {
        if (dia > REFDIA)
        {
            res--;
        }
    }
    free(bdatee);
    return res;
}
int datecomparison(DATA *data1, DATA *data2) // q2
{
    if (data2->ano - data1->ano > 0)
        return 1;
    else if (data2->ano - data1->ano < 0)
        return -1;
    else
    {
        if (data2->mes - data1->mes > 0)
            return 1;
        else if (data2->mes - data1->mes < 0)
            return -1;
        else
        {
            if (data2->dia - data1->dia > 0)
                return 1;
            else if (data2->dia - data1->dia < 0)
                return -1;
            else
                return 0;
        }
    }
}
int datecomparisonchar(char *date1, char *date2, int dia, int mes, int ano) // q2
{
    if (date1 == NULL)
    {
        char *dateb = strdup(date2);
        int dia1;
        int mes1;
        int ano1;
        sscanf(strtok(dateb, "/"), "%d", &dia1);
        sscanf(strtok(NULL, "/"), "%d", &mes1);
        sscanf(strtok(NULL, "/"), "%d", &ano1);
        free(dateb);
        if (ano1 - ano > 0)
            return 1;
        else if (ano1 - ano < 0)
            return -1;
        else
        {
            if (mes1 - mes > 0)
                return 1;
            else if (mes1 - mes < 0)
                return -1;
            else
            {
                if (dia1 - dia > 0)
                    return 1;
                else if (dia1 - dia < 0)
                    return -1;
                else
                    return 0;
            }
        }
    }
    else
    {
        char *datea = strdup(date1);
        char *dateb = strdup(date2);
        int dia1;
        int mes1;
        int ano1;
        sscanf(strtok(datea, "/"), "%d", &dia1);
        sscanf(strtok(NULL, "/"), "%d", &mes1);
        sscanf(strtok(NULL, "/"), "%d", &ano1);
        free(datea);
        int dia2;
        int mes2;
        int ano2;
        sscanf(strtok(dateb, "/"), "%d", &dia2);
        sscanf(strtok(NULL, "/"), "%d", &mes2);
        sscanf(strtok(NULL, "/"), "%d", &ano2);
        free(dateb);
        if (ano2 - ano1 > 0)
            return 1;
        else if (ano2 - ano1 < 0)
            return -1;
        else
        {
            if (mes2 - mes1 > 0)
                return 1;
            else if (mes2 - mes1 < 0)
                return -1;
            else
            {
                if (dia2 - dia1 > 0)
                    return 1;
                else if (dia2 - dia1 < 0)
                    return -1;
                else
                    return 0;
            }
        }
    }
}
double av_mediauser(RIDE *ridearray, char *username) // q1
{
    double soma = 0;
    int counter = 0;
    for (int i = 1; i <= maxride; i++)
    {
        if(rideisnull(ridearray, i) == 0) continue;
        char *useraux = get_user(ridearray, i);
        if (strcmp(useraux, username) == 0)
        {
            soma += get_scoreuser(ridearray, i);
            counter++;
        }
        free(useraux);
    }
    return soma / counter;
}
double av_mediadriver(RIDE *ridearray, int driver) // q1
{
    double soma = 0;
    int counter = 0;
    for (int i = 1; i <= maxride; i++)
    {
        if(rideisnull(ridearray, i) == 0) continue;
        if (get_driverid(ridearray, i) == driver)
        {
            soma += get_scoredriver(ridearray, i);
            counter++;
        }
    }
    return soma / counter;
}
int num_viagensuser(RIDE *ridearray, char *username) // q1
{
    int counter = 0;
    for (int i = 1; i <= maxride; i++)
    {
        if(rideisnull(ridearray, i) == 0) continue;
        char *user = get_user(ridearray, i);
        if (strcmp(user, username) == 0)
        {
            counter++;
        }
        free(user);
    }
    return counter;
}
int num_viagensdriver(RIDE *ridearray, int driver) // q1
{
    int counter = 0;
    for (int i = 1; i <= maxride; i++)
    {
        if(rideisnull(ridearray, i) == 0) continue;
        if (get_driverid(ridearray, i) == driver)
            counter++;
    }
    return counter;
}
double total_gasto(DRIVER *driverarray, RIDE *ridearray, char *username) // q1
{
    double total = 0;
    double tottip = 0;
    int driver;
    int kmviagem;
    for (int i = 1; i <= maxride; i++)
    {
        if(rideisnull(ridearray, i) == 0) continue;
        char *useraux = get_user(ridearray, i);
        if (strcmp(useraux, username) == 0)
        {
            char *carclass;
            driver = get_driverid(ridearray, i);
            kmviagem = get_distance(ridearray, i);
            tottip += get_tip(ridearray, i);
            carclass = get_carclass(driverarray, driver);
            if (strcmp(carclass, "basic") == 0)
            {
                total += 3.25 + (0.62 * kmviagem);
            }
            else if (strcmp(carclass, "green") == 0)
            {
                total += 4.0 + (0.79 * kmviagem);
            }
            else if (strcmp(carclass, "premium") == 0)
            {
                total += 5.20 + (0.94 * kmviagem);
            }
            free(carclass);
        }
        free(useraux);
    }
    return total + tottip;
}
double total_auferido(DRIVER *driverarray, RIDE *ridearray, int driver) // q1
{
    double total = 0;
    double tottip = 0;
    char *carclass = get_carclass(driverarray, driver);
    int kmviagem;
    for (int i = 1; i <= maxride; i++)
    {
        if(rideisnull(ridearray, i) == 0) continue;
        if (get_driverid(ridearray, i) == driver)
        {
            kmviagem = get_distance(ridearray, i);
            tottip += get_tip(ridearray, i);
            if (strcmp(carclass, "basic") == 0)
            {
                total += 3.25 + (0.62 * kmviagem);
            }
            else if (strcmp(carclass, "green") == 0)
            {
                total += 4.0 + (0.79 * kmviagem);
            }
            else if (strcmp(carclass, "premium") == 0)
            {
                total += 5.20 + (0.94 * kmviagem);
            }
        }
    }
    free(carclass);
    return total + tottip;
}
double precoviagem(DRIVER *driverarray, int driverid, int dist) // q4
{
    double preco = 0;
    char *carclass = get_carclass(driverarray, driverid);
    if (strcmp(carclass, "basic") == 0)
    {
        preco = 3.25 + (0.62 * dist);
    }
    else if (strcmp(carclass, "green") == 0)
    {
        preco = 4.0 + (0.79 * dist);
    }
    else if (strcmp(carclass, "premium") == 0)
    {
        preco = 5.20 + (0.94 * dist);
    }
    free(carclass);
    return preco;
}
double preco_medio(DRIVER *driverarray, RIDE *ridearray, char *city, char *data1, char *data2) // q4 e q5
{
    double soma = 0;
    int counter = 0;
    if (data1 == NULL && data2 == NULL)
    {
        for (int i = 1; i <= maxride; i++)
        {
            if(rideisnull(ridearray, i) == 0) continue;
            char *cityaux = get_cityride(ridearray, i, "ride");
            if (strcmp(cityaux, city) == 0)
            {
                soma += get_precoviagem(ridearray, i);
                counter++;
            }
            free(cityaux);
        }
    }
    else if (city == NULL)
    {
        DATA *datatok1 = malloc(sizeof *datatok1);
        DATA *datatok2 = malloc(sizeof *datatok2);
        char *datea = strdup(data1);
        sscanf(strtok(datea, "/"), "%d", &datatok1->dia);
        sscanf(strtok(NULL, "/"), "%d", &datatok1->mes);
        sscanf(strtok(NULL, "/"), "%d", &datatok1->ano);
        char *dateb = strdup(data2);
        sscanf(strtok(dateb, "/"), "%d", &datatok2->dia);
        sscanf(strtok(NULL, "/"), "%d", &datatok2->mes);
        sscanf(strtok(NULL, "/"), "%d", &datatok2->ano);
        for (int i = 1; i <= maxride; i++)
        {
            if(rideisnull(ridearray, i) == 0) continue;
            DATA *data = get_datatok(ridearray, i);
            if (datecomparison(datatok1, data) >= 0 && datecomparison(datatok2, data) <= 0)
            {
                soma += get_precoviagem(ridearray, i);
                counter++;
            }
            free(data);
        }
        free(datea);
        free(dateb);
    }
    return soma / counter;
}
