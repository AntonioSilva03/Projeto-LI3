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

char *mystrupr(char *str);
int idade(char *bdate);
int datecomparison(DATA *data1, DATA *data2);
int datecomparisonchar(char *date1, char *date2, int dia, int mes, int ano);
double av_mediauser(RIDE *ridearray, char *username);
double av_mediadriver(RIDE *ridearray, int driver);
int num_viagensuser(RIDE *ridearray, char *username);
int num_viagensdriver(RIDE *ridearray, int driver);
double total_gasto(DRIVER *driverarray, RIDE *ridearray, char *username);
double total_auferido(DRIVER *driverarray, RIDE *ridearray, int driver);
int dist_total(RIDE *ridearray, char *username);
double precoviagem(DRIVER *driverarray, int driverid, int dist);
double preco_medio(DRIVER *driverarray, RIDE *ridearray, char *city, char *data1, char *data2);
double av_mediadrivercity(RIDE *ridearray, int driver, char *city);

#endif