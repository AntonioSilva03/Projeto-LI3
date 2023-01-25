#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/parserides.h"
#include "../includes/getridedata.h"

struct rides
{
    int id;
    char *date;
    DATA *datatok;
    int driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    double tip;
    double precoviagem;
    // char *comment;
};

int rideisnull(RIDE *ridearray, int pos)
{
    if (ridearray[pos] == NULL)
        return 0;
    return 1;
}
int get_idride(RIDE *ridearray, int pos, char *type) // ride
{
    int id;
    id = ridearray[pos]->id;
    return id;
}
char *get_date(RIDE *ridearray, int pos) // ride
{
    char *date;
    date = strdup(ridearray[pos]->date);
    return date;
}
DATA *get_datatok(RIDE *ridearray, int pos)
{
    DATA *data = malloc(sizeof *data);
    data->dia = ridearray[pos]->datatok->dia;
    data->mes = ridearray[pos]->datatok->mes;
    data->ano = ridearray[pos]->datatok->ano;
    return data;
}
int get_driverid(RIDE *ridearray, int pos) // ride
{
    int driverid;
    driverid = ridearray[pos]->driver;
    return driverid;
}
char *get_user(RIDE *ridearray, int pos) // ride
{
    char *user;
    user = strdup(ridearray[pos]->user);
    return user;
}
char *get_cityride(RIDE *ridearray, int pos, char *type)
{
    char *city;
    city = strdup(ridearray[pos]->city);
    return city;
}
int get_distance(RIDE *ridearray, int pos) // ride
{
    int distance;
    distance = ridearray[pos]->distance;
    return distance;
}
int get_scoreuser(RIDE *ridearray, int pos) // ride
{
    int scoreuser;
    scoreuser = ridearray[pos]->score_user;
    return scoreuser;
}
int get_scoredriver(RIDE *ridearray, int pos) // ride
{
    int scoredriver;
    scoredriver = ridearray[pos]->score_driver;
    return scoredriver;
}
double get_tip(RIDE *ridearray, int pos) // ride
{
    double tip;
    tip = ridearray[pos]->tip;
    return tip;
}
double get_precoviagem(RIDE *ridearray, int pos)
{
    double preco;
    preco = ridearray[pos]->precoviagem;
    return preco;
}