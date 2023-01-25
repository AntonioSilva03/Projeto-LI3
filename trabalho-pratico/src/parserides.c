#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/parserides.h"
#include "../includes/structsaux.h"
#include "../includes/calculos.h"
#include <ctype.h>

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

DATA *putdata(char *datastr)
{
    DATA *data = malloc(sizeof *data);
    int dia;
    int mes;
    int ano;
    char *date = strdup(datastr);
    sscanf(strtok(date, "/"), "%d", &dia);
    sscanf(strtok(NULL, "/"), "%d", &mes);
    sscanf(strtok(NULL, "/"), "%d", &ano);
    data->dia = dia;
    data->mes = mes;
    data->ano = ano;
    free(date);
    return data;
}
void scoremedia(DRIVERMEDIA *drivermedia, RIDE ride)
{
    if (ride->driver <= maxdriver)
    {
        drivermedia[ride->driver].nviagens++;
        drivermedia[ride->driver].somascore += ride->score_driver;
        if (datecomparisonchar(drivermedia[ride->driver].datarecente, ride->date, 0, 0, 0) > 0)
        {
            drivermedia[ride->driver].datarecente = ride->date;
        }
    }
}
RIDE *new_ridearray()
{
    RIDE *ridesarray = malloc(sizeof *ridesarray * maxride);
    return ridesarray;
}
int verificacaorides(char *line)
{
    if (line[0] == ';' || line[13] == ';' || line[38] == ';')
    {
        return 0;
    }
    RIDE ride = malloc(sizeof *ride);
    int context = 1;
    char *token = strtok(line, ";");
    while (token != NULL)
    {
        if (context == 1)
        {
            ride->id = atoi(token);
            if (ride->id <= 0)
            {
                return 0;
            }
        }
        else if (context == 2)
        {
            ride->date = strdup(token);
            if (strlen(ride->date) != 10 || ride->date[2] != '/' || ride->date[5] != '/')
            {
                return 0;
            }
            int day = atoi(ride->date);
            int month = atoi(ride->date + 3);
            int year = atoi(ride->date + 6);
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
            {
                return 0;
            }
        }
        else if (context == 3)
        {
            ride->driver = atoi(token);
            if (ride->driver <= 0)
            {
                return 0;
            }
        }
        else if (context == 4)
        {
        }
        else if (context == 5)
        {
            for (int i = 0; token[i]; i++)
            {
                if (isdigit(token[i]))
                {
                    return 0;
                }
            }
        }
        else if (context == 6)
        {
            for (int i = 0; token[i]; i++)
            {
                if (!isdigit(token[i]))
                {
                    return 0;
                }   
            }
            if (atoi(token) != atof(token))
            {
                return 0;
            }
            ride->distance = atoi(token);
            if (ride->distance <= 0)
                return 0;
        }
        else if (context == 7)
        {
            for (int i = 0; token[i]; i++)
            {
                if (!isdigit(token[i]))
                {
                    return 0;
                }   
            }
            ride->score_user = atoi(token);
            if (ride->score_user <= 0)
                return 0;
        }
        else if (context == 8)
        {
            for (int i = 0; token[i]; i++)
            {
                if (!isdigit(token[i]))
                {
                    return 0;
                }   
            }
            ride->score_driver = atoi(token);
            if (ride->score_driver <= 0)
                return 0;
        }
        else if (context == 9)
        {
            for (int i = 0; token[i]; i++)
            {
                if (!isdigit(token[i]) && token[i] != '.')
                {
                    return 0;
                }   
            }
            ride->tip = atof(token);
            if (ride->tip < 0)
                return 0;
        }
        context++;
        token = strtok(NULL, ";");
    }
    free(ride);
    free(line);
    return 1;
}
void parserides(FILE *rides, RIDE *ridesarray, DRIVERMEDIA *drivermedia, DRIVER *driverarray)
{
    for (int i = 0; i <= maxride; i++)
    {
        ridesarray[i] = NULL;
    }
    char str[BUFSIZ];
    int arraypos = 0;
    while (feof(rides) != 1)
    {
        if (fgets(str, BUFSIZ, rides) != 0)
        {
            RIDE ride = malloc(sizeof *ride);
            char *line = strdup(str);
            if (arraypos > 0 && verificacaorides(line) == 0)
            {
                arraypos++;
                continue;
            }
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
            if (arraypos > 0)
            {
                ride->datatok = putdata(ride->date);
                ride->precoviagem = precoviagem(driverarray, ride->driver, ride->distance);
                            scoremedia(drivermedia, ride);
            }
            if (arraypos > 0)
                ridesarray[ride->id] = ride;
            else
                ridesarray[0] = ride;
            arraypos++;
        }
    }
}