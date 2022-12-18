#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
//#include "../includes/data.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/getuserdata.h"
#include "../includes/getdriverdata.h"
#include "../includes/getridedata.h"
#include "../includes/calculos.h"
#include "../includes/estatisticas.h"

int query2est(DRIVER *driverarray, RIDE *ridearray,  DRIVERMEDIA *avs)
{
    for (int i = 1; i <= MAX_DRIVER; i += 2)
    {
        avs[i].id = i;
        avs[i + 1].id = i + 1;
        avs[i].activity = get_accountstatusdriver(driverarray, i, "driver");
        avs[i + 1].activity = get_accountstatusdriver(driverarray, i + 1, "driver");
        avs[i].nome = get_namedriver(driverarray, i, "driver");
        avs[i + 1].nome = get_namedriver(driverarray, i + 1, "driver");
        av_media_data_recente(ridearray, i, i + 1, &avs[i].datarecente, &avs[i].avmedia, &avs[i + 1].datarecente, &avs[i + 1].avmedia);
    }
    int t = 1;
    for (int i = 1; i <= MAX_DRIVER; i++)
    {
        if (strcmp(avs[i].activity, "active\n") == 0)
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
        while (tmp == avs[j].avmedia && datecomparison(avs[j].datarecente, aux.datarecente) < 0 && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        while (tmp == avs[j].avmedia && datecomparison(avs[j].datarecente, aux.datarecente) == 0 && aux.id > avs[j].id && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        avs[j + 1] = aux;
    }
    return t;
}
void query7est(DRIVER *driverarray, RIDE *ridearray, RIDE2 *lisboa, RIDE2 *braga, RIDE2 *porto, RIDE2 *faro, RIDE2 *setubal, CITYMEDIA *lisboaavs, CITYMEDIA *bragaavs, CITYMEDIA *portoavs, CITYMEDIA *faroavs, CITYMEDIA *setubalavs)
{
    int poslisboa = 0;
    int posbraga = 0;
    int posporto = 0;
    int posfaro = 0;
    int possetubal = 0;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
        if (strcmp(get_cityride(ridearray, i, "ride"), "Lisboa") == 0)
        {
            lisboa[poslisboa].id = i;
            lisboa[poslisboa].a = ridearray[i];
            poslisboa++;
        }
        else if (strcmp(get_cityride(ridearray, i, "ride"), "Braga") == 0)
        {
            braga[posbraga].id = i;
            braga[posbraga].a = ridearray[i];
            posbraga++;
        }
        else if (strcmp(get_cityride(ridearray, i, "ride"), "Porto") == 0)
        {
            porto[posporto].id = i;
            porto[posporto].a = ridearray[i];
            posporto++;
        }
        else if (strcmp(get_cityride(ridearray, i, "ride"), "Faro") == 0)
        {
            faro[posfaro].id = i;
            faro[posfaro].a = ridearray[i];
            posfaro++;
        }
        else if (strcmp(get_cityride(ridearray, i, "ride"), "Setúbal") == 0)
        {
            setubal[possetubal].id = i;
            setubal[possetubal].a = ridearray[i];
            possetubal++;
        }
    }
    avs(driverarray, ridearray, lisboa, lisboaavs, poslisboa);
    avs(driverarray, ridearray, braga, bragaavs, posbraga);
    avs(driverarray, ridearray, porto, portoavs, posporto);
    avs(driverarray, ridearray, faro, faroavs, posfaro);
    avs(driverarray, ridearray, setubal, setubalavs, possetubal);
}
void avs(DRIVER *driverarray, RIDE *ridearray, RIDE2 *cityviagens, CITYMEDIA *avs, int pos)
{
    int pos2 = 0;
    double media;
    int counter;
    for (int i = 0; i < pos; i++)
    {
        media = 0;
        counter = 0;
        if (cityviagens[i].a != NULL)
        {
            avs[pos2].id = get_driverid(ridearray, cityviagens[i].id);
            avs[pos2].nome = get_namedriver(driverarray, avs[pos2].id, "driver");
            avs[pos2].activity = get_accountstatusdriver(driverarray, avs[pos2].id, "driver");
            media += get_scoredriver(ridearray, cityviagens[i].id);
            cityviagens[i].a = NULL;
            counter = 1;
            for (int j = i + 1; j < pos; j++)
            {
                if (cityviagens[j].a != NULL)
                {
                    if (get_driverid(ridearray, cityviagens[i].id) == get_driverid(ridearray, cityviagens[j].id))
                    {
                        media += get_scoredriver(ridearray, cityviagens[j].id);
                        cityviagens[j].a = NULL;
                        counter++;
                    }
                }
            }
            avs[pos2].avmedia = media / counter;
            pos2++;
        }
    }
}