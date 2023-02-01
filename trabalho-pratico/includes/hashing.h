#ifndef hashing_h
#define hashing_h
#include <stdio.h>
#include <stdlib.h>
#include "../includes/parseusers.h"

int hashkey(char *key);
int hashsearch(USER *userhash, char *key);

#endif