#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../includes/data.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/getuserdata.h"
#include "../includes/getdriverdata.h"
#include "../includes/getridedata.h"
#include "../includes/calculos.h"

int idade(char *bdate) // q1
{
    int res;
    int dia;
    int mes;
    int ano;
    sscanf(strtok(bdate, "/"), "%d", &dia);
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
    return res;
}
int datecomparison(char *date1, char *date2) // q2
{
    char *datea = strdup(date1);
    char *dateb = strdup(date2);
    int res;
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
        res = 1;
    else if (ano2 - ano1 < 0)
        res = -1;
    else
    {
        if (mes2 - mes1 > 0)
            res = 1;
        else if (mes2 - mes1 < 0)
            res = -1;
        else
        {
            if (dia2 - dia1 > 0)
                res = 1;
            else if (dia2 - dia1 < 0)
                res = -1;
            else
                res = 0;
        }
    }
    return res;
}
double av_mediauser(RIDE *ridearray, char *username) // q1
{
    double soma = 0;
    int counter = 0;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
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
    for (int i = 1; i <= MAX_RIDE; i++)
    {
        if (get_driverid(ridearray, i) == driver)
        {
            soma += get_scoredriver(ridearray, i);
            counter++;
        }
    }
    return soma / counter;
}
void av_media_data_recente(RIDE *ridearray, int driver1, int driver2, char **datarecente1, double *avmedia1, char **datarecente2, double *avmedia2)
{
    double soma1 = 0;
    int counter1 = 0;
    double soma2 = 0;
    int counter2 = 0;
    *datarecente1 = "01/01/1990";
    *datarecente2 = "01/01/1990";
    for (int i = 1; i <= MAX_RIDE; i += 2)
    {
        if (get_driverid(ridearray, i) == driver1)
        {
            soma1 += get_scoredriver(ridearray, i);
            counter1++;
            if (datecomparison(*datarecente1, get_date(ridearray, i)) > 0)
            {
                *datarecente1 = get_date(ridearray, i);
            }
        }
        else if (get_driverid(ridearray, i) == driver2)
        {
            soma2 += get_scoredriver(ridearray, i);
            counter2++;
            if (datecomparison(*datarecente2, get_date(ridearray, i)) > 0)
            {
                *datarecente2 = get_date(ridearray, i);
            }
        }
        if (get_driverid(ridearray, i + 1) == driver1)
        {
            soma1 += get_scoredriver(ridearray, i + 1);
            counter1++;
            if (datecomparison(*datarecente1, get_date(ridearray, i + 1)) > 0)
            {
                *datarecente1 = get_date(ridearray, i + 1);
            }
        }
        else if (get_driverid(ridearray, i + 1) == driver2)
        {
            soma2 += get_scoredriver(ridearray, i + 1);
            counter2++;
            if (datecomparison(*datarecente2, get_date(ridearray, i + 1)) > 0)
            {
                *datarecente2 = get_date(ridearray, i + 1);
            }
        }
    }
    *avmedia1 = soma1 / counter1;
    *avmedia2 = soma2 / counter2;
}
int num_viagensuser(RIDE *ridearray, char *username) // q1
{
    int counter = 0;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
        if (strcmp(get_user(ridearray, i), username) == 0)
            counter++;
    }
    return counter;
}
int num_viagensdriver(RIDE *ridearray, int driver) // q1
{
    int counter = 0;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
        if (get_driverid(ridearray, i) == driver)
            counter++;
    }
    return counter;
}
double total_gasto(DRIVER *driverarray, RIDE *ridearray, char *username) // q1
{
    double total = 0;
    double tottip = 0;
    char *carclass;
    int driver;
    int kmviagem;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
        char *useraux = get_user(ridearray, i);
        if (strcmp(useraux, username) == 0)
        {
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
        }
        free(useraux);
    }
    free(carclass);
    return total + tottip;
}
double total_auferido(DRIVER *driverarray, RIDE *ridearray, int driver) // q1
{
    double total = 0;
    double tottip = 0;
    char *carclass = get_carclass(driverarray, driver);
    int kmviagem;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
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
int dist_total(RIDE *ridearray, char *username) // q3
{
    int disttot = 0;
    char *user;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
        if (ridearray[i] != NULL)
        {
            user = get_user(ridearray, i);
            if (strcmp(username, user) == 0)
            {
                disttot += get_distance(ridearray, i);
                ridearray[i] = NULL;
            }
        }
    }
    free(user);
    return disttot;
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
        for (int i = 1; i <= MAX_RIDE; i++)
        {
            char *cityaux = get_cityride(ridearray, i, "ride");
            if (strcmp(cityaux, city) == 0)
            {
                soma += precoviagem(driverarray, get_driverid(ridearray, i), get_distance(ridearray, i));
                counter++;
            }
            free(cityaux);
        }
    }
    else if (city == NULL)
    {
        for (int i = 1; i <= MAX_RIDE; i++)
        {
            char *data = get_date(ridearray, i);
            if (datecomparison(data1, data) >= 0 && datecomparison(data2, data) <= 0)
            {
                soma += precoviagem(driverarray, get_driverid(ridearray, i), get_distance(ridearray, i));
                counter++;
            }
            free(data);
        }
    }
    return soma / counter;
}
double av_mediadrivercity(RIDE *ridearray, int driver, char *city) // q7
{
    double soma = 0;
    int counter = 0;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
        if (get_driverid(ridearray, i) == driver && strcmp(get_cityride(ridearray, i, "ride"), city) == 0)
        {
            soma += get_scoredriver(ridearray, i);
            counter++;
        }
    }
    return soma / counter;
}
