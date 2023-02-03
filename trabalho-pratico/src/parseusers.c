#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/parseusers.h"
#include "../includes/calculos.h"
#include "../includes/hashing.h"

struct users
{
    char *username;
    char *name;
    char gender;
    char *birthdate;
    char *accountcreation;
    //char *paymethod;
    char *accountstatus;
};

USER *new_userarray()
{
    USER *usersarray = malloc(sizeof *usersarray * (maxuser + 1));
    return usersarray;
}

int verificacaousers(char *line)
{
    if (line[0] == ';')
    {
        return 0;
    }
    USER user = malloc(sizeof *user);
    int context = 1;
    char *token = strtok(line, ";");
    while (token != NULL)
    {
        if (context == 1)
        {
            user->username = strdup(token);
        }
        else if (context == 2)
        {
            user->name = strdup(token);
            if (strlen(user->name) == 0 || user->name[0] == '\0')
            {
                free(line);
                free(user);
                return 0;
            }
        }
        else if (context == 3)
        {
            if (strlen(token) != 1)
            {
                free(line);
                free(user);
                return 0;
            }
        }
        else if (context == 4)
        {
            user->birthdate = strdup(token);
            if (strlen(user->birthdate) != 10 || user->birthdate[2] != '/' || user->birthdate[5] != '/')
            {
                free(line);
                free(user);
                return 0;
            }
            int day = atoi(user->birthdate);
            int month = atoi(user->birthdate + 3);
            int year = atoi(user->birthdate + 6);
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
            {
                free(line);
                free(user);
                return 0;
            }
        }
        else if (context == 5)
        {
            user->accountcreation = strdup(token);
            if (strlen(user->accountcreation) != 10 || user->accountcreation[2] != '/' || user->accountcreation[5] != '/')
            {
                free(line);
                free(user);
                return 0;
            }
            int day = atoi(user->accountcreation);
            int month = atoi(user->accountcreation + 3);
            int year = atoi(user->accountcreation + 6);
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
            {
                free(line);
                free(user);
                return 0;
            }
        }
        else if (context == 6)
        {
            char *aux = mystrupr(token);
            if (strcmp(aux, "ACTIVE\n") == 0 || strcmp(aux, "INACTIVE\n") == 0)
            {
                free(line);
                free(user);
                return 0;
            }
        }
        else if (context == 7)
        {
            user->accountstatus = strdup(token);
            char *aux = mystrupr(user->accountstatus);
            if (strcmp(aux, "ACTIVE\n") != 0 && strcmp(aux, "INACTIVE\n") != 0)
            {
                free(line);
                free(user);
                return 0;
            }
        }
        context++;
        token = strtok(NULL, ";");
    }
    free(user);
    free(line);
    return 1;
}

void parseusers(FILE *users, USER *usersarray, USER *userhash)
{
    char str[BUFSIZ];
    int arraypos = 0;
    while (feof(users) != 1)
    {
        if (fgets(str, BUFSIZ, users) != 0)
        {
            USER user = malloc(sizeof *user);
            char *line = strdup(str);
            if (arraypos > 0 && verificacaousers(line) == 0)
            {
                usersarray[arraypos] = NULL;
                arraypos++;
                continue;
            }
            int context = 1;
            char *token = strtok(str, ";");
            while (token != NULL)
            {
                if (context == 1)
                {
                    user->username = strdup(token);
                }
                else if (context == 2)
                {
                    user->name = strdup(token);
                }
                else if (context == 3)
                {
                    char gender;
                    sscanf(token, "%c", &gender);
                    user->gender = gender;
                }
                else if (context == 4)
                {
                    user->birthdate = strdup(token);
                }
                else if (context == 5)
                {
                    user->accountcreation = strdup(token);
                }
                else if (context == 6)
                {
                }
                else if (context == 7)
                {
                    char *aux = mystrupr(strdup(token));
                    if (strcmp(aux, "ACTIVE\n") == 0)
                    {
                        user->accountstatus = "active\n";
                    }
                    else if (strcmp(aux, "INACTIVE\n") == 0)
                    {
                        user->accountstatus = "inactive\n";
                    }
                    else user->accountstatus = strdup(token);
                }
                context++;
                token = strtok(NULL, ";");
            }
            usersarray[arraypos] = user;
            int index = hashkey(user->username);
            while(userhash[index] != NULL)
            {
                if(index >= maxride) index = 0;
                else index++;
            }
            userhash[index] = user;
            arraypos++;
        }
    }
}
