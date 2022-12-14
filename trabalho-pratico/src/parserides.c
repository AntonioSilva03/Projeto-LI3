#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/parserides.h"

struct rides
{
    int id;
    char *date;
    int driver;
    char *user;
    char *city;
    int distance;
    int score_user;
    int score_driver;
    double tip;
    //char *comment;
};

RIDE *new_ridearray()
{
    RIDE *ridesarray = malloc(sizeof *ridesarray * MAX_RIDE);
    return ridesarray;
}

void parserides(FILE *rides, RIDE *ridesarray)
{
    char str[BUFSIZ];
    int arraypos = 0;
    while (feof(rides) != 1)
    {
        if (fgets(str, BUFSIZ, rides) != 0)
        {
            RIDE ride = malloc(sizeof *ride);
            int context = 1;
            char *token = strtok(str, ";");
            while (token != NULL)
            {
                if (context == 1)
                {
                    int id;
                    sscanf(token, "%d", &id);
                    ride->id = id;
                }
                else if (context == 2)
                {
                    ride->date = strdup(token);
                }
                else if (context == 3)
                {
                    int driver;
                    sscanf(token, "%d", &driver);
                    ride->driver = driver;
                }
                else if (context == 4)
                {
                    ride->user = strdup(token);
                }
                else if (context == 5)
                {
                    ride->city = strdup(token);
                }
                else if (context == 6)
                {
                    int distance;
                    sscanf(token, "%d", &distance);
                    ride->distance = distance;
                }
                else if (context == 7)
                {
                    int scoreuser;
                    sscanf(token, "%d", &scoreuser);
                    ride->score_user = scoreuser;
                }
                else if (context == 8)
                {
                    int scoredriver;
                    sscanf(token, "%d", &scoredriver);
                    ride->score_driver = scoredriver;
                }
                else if (context == 9)
                {
                    double tip;
                    sscanf(token, "%lf", &tip);
                    ride->tip = tip;
                }
                context++;
                token = strtok(NULL, ";");
            }
            ridesarray[arraypos] = ride;
            arraypos++;
        }
    }
}