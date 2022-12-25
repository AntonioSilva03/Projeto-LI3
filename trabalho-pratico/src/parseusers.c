#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/parseusers.h"

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
    USER *usersarray = malloc(sizeof *usersarray * maxuser);
    return usersarray;
}

void parseusers(FILE *users, USER *usersarray)
{
    char str[BUFSIZ];
    int arraypos = 0;
    while (feof(users) != 1)
    {
        if (fgets(str, BUFSIZ, users) != 0)
        {
            USER user = malloc(sizeof *user);
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
                    user->accountstatus = strdup(token);
                }
                context++;
                token = strtok(NULL, ";");
            }
            usersarray[arraypos] = user;
            arraypos++;
        }
    }
}
