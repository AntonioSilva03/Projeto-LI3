#ifndef getuserdata_h
#define getuserdata_h
#include "parseusers.h"

char *get_username(USER *userarray, int pos); //user
char *get_nameuser(USER *userarray, int pos, char *type); //user
char get_genderuser(USER *userarray, int pos, char *type); //user
char *get_birthdateuser(USER *userarray, int pos, char *type); //user
char *get_accountcreationuser(USER *userarray, int pos, char *type); //user
char *get_accountstatususer(USER *userarray, int pos, char *type); //user


#endif