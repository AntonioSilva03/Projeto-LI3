#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
// #include "../includes/data.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/getuserdata.h"
#include "../includes/getdriverdata.h"
#include "../includes/getridedata.h"
#include "../includes/calculos.h"
#include "../includes/estatisticas.h"

int query2est(DRIVER *driverarray, RIDE *ridearray, DRIVERMEDIA *avs)
{
    for (int i = 1; i <= maxdriver; i++)
    {
        if (driverisnull(driverarray, i) == 0)
        {
            avs[i].activity = "inactive\n";
            continue;
        }
        avs[i].avmedia = avs[i].somascore / avs[i].nviagens;
        avs[i].activity = get_accountstatusdriver(driverarray, i, "driver");
        avs[i].nome = get_namedriver(driverarray, i, "driver");
    }
    int t = 1;
    for (int i = 1; i <= maxdriver; i++)
    {
        if (strcmp(avs[i].activity, "active\n") == 0 && avs[i].avmedia == avs[i].avmedia)
        {
            avs[t] = avs[i];
            t++;
        }
    }
    for (int i = 1; i <= t; i++)
    {
        double tmp = avs[i].avmedia;
        DRIVERMEDIA aux = avs[i];
        int j = i - 1;
        while (tmp < avs[j].avmedia && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        while (tmp == avs[j].avmedia && datecomparisonchar(avs[j].datarecente, aux.datarecente, 0, 0, 0) < 0 && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        while (tmp == avs[j].avmedia && datecomparisonchar(avs[j].datarecente, aux.datarecente, 0, 0, 0) == 0 && aux.id > avs[j].id && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        avs[j + 1] = aux;
    }
    return t;
}
void query7est(DRIVER *driverarray, RIDE *ridearray, RIDE2 *lisboa, RIDE2 *braga, RIDE2 *porto, RIDE2 *faro, RIDE2 *setubal, RIDE2 *coimbra, RIDE2 *vila_real, CITYMEDIA *lisboaavs, CITYMEDIA *bragaavs, CITYMEDIA *portoavs, CITYMEDIA *faroavs, CITYMEDIA *setubalavs, CITYMEDIA *coimbraavs, CITYMEDIA *vila_realavs)
{
    int poslisboa = 0;
    int posbraga = 0;
    int posporto = 0;
    int posfaro = 0;
    int possetubal = 0;
    int poscoimbra = 0;
    int posvilareal = 0;
    int nlisboa = 0;
    int nbraga = 0;
    int nporto = 0;
    int nfaro = 0;
    int nsetubal = 0;
    int ncoimbra = 0;
    int nvilareal = 0;
    CITYMEDIA aux;
    for (int i = 1; i <= maxride; i++)
    {
        if (rideisnull(ridearray, i) == 0)
        {
            continue;
        }
        
        char *city = get_cityride(ridearray, i, "ride");
        char *activity = get_accountstatusdriver(driverarray, get_driverid(ridearray, i), "driver");
        if (strcmp(city, "Lisboa") == 0)
        {
            lisboa[poslisboa].id = i;
            lisboa[poslisboa].a = ridearray[i];
            if (strcmp(activity, "active\n") == 0)
            {
                aux.id = get_driverid(ridearray, lisboa[poslisboa].id);
                aux.avmedia = get_scoredriver(ridearray, lisboa[poslisboa].id);
                nlisboa += avs(driverarray, ridearray, lisboaavs, aux);
            }
            poslisboa++;
        }
        else if (strcmp(city, "Braga") == 0)
        {
            braga[posbraga].id = i;
            braga[posbraga].a = ridearray[i];
            if (strcmp(activity, "active\n") == 0)
            {
                aux.id = get_driverid(ridearray, braga[posbraga].id);
                aux.avmedia = get_scoredriver(ridearray, braga[posbraga].id);
                nbraga += avs(driverarray, ridearray, bragaavs, aux);
            }
            posbraga++;
        }
        else if (strcmp(city, "Porto") == 0)
        {
            porto[posporto].id = i;
            porto[posporto].a = ridearray[i];
            if (strcmp(activity, "active\n") == 0)
            {
                aux.id = get_driverid(ridearray, porto[posporto].id);
                aux.avmedia = get_scoredriver(ridearray, porto[posporto].id);
                nporto += avs(driverarray, ridearray, portoavs, aux);
            }
            posporto++;
        }
        else if (strcmp(city, "Faro") == 0)
        {
            faro[posfaro].id = i;
            faro[posfaro].a = ridearray[i];
            if (strcmp(activity, "active\n") == 0)
            {
                aux.id = get_driverid(ridearray, faro[posfaro].id);
                aux.avmedia = get_scoredriver(ridearray, faro[posfaro].id);
                nfaro += avs(driverarray, ridearray, faroavs, aux);
            }
            posfaro++;
        }
        else if (strcmp(city, "Setúbal") == 0)
        {
            setubal[possetubal].id = i;
            setubal[possetubal].a = ridearray[i];
            if (strcmp(activity, "active\n") == 0)
            {
                aux.id = get_driverid(ridearray, setubal[possetubal].id);
                aux.avmedia = get_scoredriver(ridearray, setubal[possetubal].id);
                nsetubal += avs(driverarray, ridearray, setubalavs, aux);
            }
            possetubal++;
        }
        else if (strcmp(city, "Coimbra") == 0)
        {
            coimbra[poscoimbra].id = i;
            coimbra[poscoimbra].a = ridearray[i];
            if (strcmp(activity, "active\n") == 0)
            {
                aux.id = get_driverid(ridearray, coimbra[poscoimbra].id);
                aux.avmedia = get_scoredriver(ridearray, coimbra[poscoimbra].id);
                ncoimbra += avs(driverarray, ridearray, coimbraavs, aux);
            }
            poscoimbra++;
        }
        else if (strcmp(city, "Vila Real") == 0)
        {
            vila_real[posvilareal].id = i;
            vila_real[posvilareal].a = ridearray[i];
            if (strcmp(activity, "active\n") == 0)
            {
                aux.id = get_driverid(ridearray, vila_real[posvilareal].id);
                aux.avmedia = get_scoredriver(ridearray, vila_real[posvilareal].id);
                nvilareal += avs(driverarray, ridearray, vila_realavs, aux);
            }
            posvilareal++;
        }
        free(city);
        free(activity);
    }
    calcavs(lisboaavs, nlisboa);
    calcavs(bragaavs, nbraga);
    calcavs(portoavs, nporto);
    calcavs(faroavs, nfaro);
    calcavs(setubalavs, nsetubal);
    calcavs(coimbraavs, ncoimbra);
    calcavs(vila_realavs, nvilareal);
}
int avs(DRIVER *driverarray, RIDE *ridearray, CITYMEDIA *avs, CITYMEDIA ride)
{
    if (avs[ride.id].activity != NULL)
    {
        avs[ride.id].avmedia += ride.avmedia;
        avs[ride.id].nviagens++;
        return 0;
    }
    avs[ride.id].id = ride.id;
    avs[ride.id].nome = get_namedriver(driverarray, avs[ride.id].id, "driver");
    avs[ride.id].avmedia = ride.avmedia;
    avs[ride.id].activity = get_accountstatusdriver(driverarray, avs[ride.id].id, "driver");
    avs[ride.id].nviagens = 1;
    return 1;
}
void calcavs(CITYMEDIA *avs, int counter)
{
    int ptr = 0;
    for (int i = 1; i <= maxdriver; i++)
    {
        if (avs[i].activity != NULL)
        {
            avs[ptr] = avs[i];
            ptr++;
        }
    }
    int pos = 0;
    while (avs[pos].nome != NULL)
    {
        avs[pos].avmedia = avs[pos].avmedia / avs[pos].nviagens;
        pos++;
    }
    for (int i = 0; i < maxdriver; i++)
    {
        if (i >= counter)
        {
            avs[i].nome = NULL;
            continue;
        }
        double tmp = avs[i].avmedia;
        CITYMEDIA aux = avs[i];
        int j = i - 1;
        while (j >= 0 && tmp < avs[j].avmedia)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        while (j >= 0 && tmp == avs[j].avmedia && aux.id < avs[j].id)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        avs[j + 1] = aux;
    }
}