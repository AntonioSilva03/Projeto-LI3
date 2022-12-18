#ifndef structsaux_h
#define structsaux_h
#include <stdio.h>
#include <stdlib.h>
#include "parseusers.h"
#include "parsedrivers.h"
#include "parserides.h"

typedef struct
{
    int id;
    char *nome;
    char *datarecente;
    double avmedia;
    char *activity;
} DRIVERMEDIA; // query2

typedef struct
{
    char *username;
    char *nome;
    int dist;
} USERDIST; // query3

typedef struct
{
    int id;
    char *nome;
    double avmedia;
    char *activity;
} CITYMEDIA; //query7

typedef struct
{
    int id;
    RIDE a;
} RIDE2; //query7 query9

#endif