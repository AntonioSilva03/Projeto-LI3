#ifndef parseusers_h
#define parseusers_h
#define MAX_USER 100000
#include <stdio.h>
#include <stdlib.h>

typedef struct users *USER;

USER *new_userarray();

void parseusers(FILE *users, USER *userarray);

#endif