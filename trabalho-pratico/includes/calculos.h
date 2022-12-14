#ifndef calculos_h
#define calculos_h
#define REFDIA 9
#define REFMES 10
#define REFANO 2022
#include <stdio.h>
#include <stdlib.h>
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
//#include "data.h"

int idade(char *bdate);
int datecomparison(char *date1, char *date2);
double av_mediauser(RIDE *ridearray, char *username);
double av_mediadriver(RIDE *ridearray, int driver);
void av_media_data_recente(RIDE *ridearray, int driver1, int driver2, char **datarecente1, double *avmedia1, char **datarecente2, double *avmedia2);
int num_viagensuser(RIDE *ridearray, char *username);
int num_viagensdriver(RIDE *ridearray, int driver);
double total_gasto(DRIVER *driverarray, RIDE *ridearray, char *username);
double total_auferido(DRIVER *driverarray, RIDE *ridearray, int driver);
int dist_total(RIDE *ridearray, char *username);
double precoviagem(DRIVER *driverarray, int driverid, int dist);
double preco_medio(DRIVER *driverarray, RIDE *ridearray, char *city, char *data1, char *data2);
double av_mediadrivercity(RIDE *ridearray, int driver, char *city);

#endif