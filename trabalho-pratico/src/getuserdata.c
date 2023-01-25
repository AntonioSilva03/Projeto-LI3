#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/getuserdata.h"
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
int userisnull(USER *userarray, int pos)
{
    if (userarray[pos] == NULL)
        return 0;
    return 1;
}
char *get_username(USER *userarray, int pos) //user
{
    char *username;
    username = strdup(userarray[pos]->username);
    return username;
}
char *get_nameuser(USER *userarray, int pos, char *type) //user
{
    char *name;
    name = strdup(userarray[pos]->name);
    return name;
}
char get_genderuser(USER *userarray, int pos, char *type) //user
{
    char gender;
    gender = userarray[pos]->gender;
    return gender;
}
char *get_birthdateuser(USER *userarray, int pos, char *type) //user
{
    char *birthdate;
    birthdate = strdup(userarray[pos]->birthdate);
    return birthdate;
}
char *get_accountcreationuser(USER *userarray, int pos, char *type) //user
{
    char *acccreation;
    acccreation = strdup(userarray[pos]->accountcreation);
    return acccreation;
}
char *get_accountstatususer(USER *userarray, int pos, char *type) //user
{
    char *accstatus;
    accstatus = strdup(userarray[pos]->accountstatus);
    return accstatus;
}