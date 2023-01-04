#ifndef parseusers_h
#define parseusers_h
//#define MAX_USER 100000
#include <stdio.h>
#include <stdlib.h>
#include "../includes/maxs.h"

typedef struct users *USER;

typedef struct
{
    int dia;
    int mes;
    int ano;
} DATA;

USER *new_userarray();

void parseusers(FILE *users, USER *userarray);

#endif