#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/hashing.h"
#include "../includes/maxs.h"
#include "../includes/getuserdata.h"
#include <string.h>
#include <ctype.h>

int hashkey(char *key)
{
    long long hash = 0;
    double p = 5.13;
    long long m = pow(10, 9) + 9;
    for (int i = 0; i < strlen(key) - 1; i++)
    {
        if (i == 23)
        {
            break;
        }
        hash += tolower(key[i]) * pow(p, i);
    }
    hash = (hash % m) % maxride;
    return hash;
}
int hashsearch(USER *userhash, char *key)
{
    int index = hashkey(key);
    int aux;
    if (index - 1 < 0)
    {
        aux = maxride - 1;
    }
    else aux = index - 1;
    if (userisnull(userhash, index) == 0)
    {
        return -1;
    }
    while (userisnull(userhash, index) == 0 || strcmp(get_username(userhash, index), key) != 0)
    {
        if (index == aux)
        {
            return -1;
        }
        if (index + 1 == maxride)
            index = 0;
        else
            index++;
    }
    return index;
}