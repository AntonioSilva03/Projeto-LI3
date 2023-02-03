#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/querys.h"
// #include "../includes/data.h"
#include "../includes/parseusers.h"
#include "../includes/parsedrivers.h"
#include "../includes/parserides.h"
#include "../includes/getuserdata.h"
#include "../includes/getdriverdata.h"
#include "../includes/getridedata.h"
#include "../includes/calculos.h"
#include "../includes/structsaux.h"
#include "../includes/hashing.h"

void query1user(USER *userarray, DRIVER *driverarray, RIDE *ridearray, char *ID, FILE *output)
{
    char *nome;
    char gender;
    int idadee;
    double avmedia;
    int numviagens;
    double totalgasto;
    char *username;
    char *activity;
    for (int i = 1; i <= maxuser; i++)
    {
        if(userisnull(userarray, i) == 0)continue;
        username = get_username(userarray, i);
        activity = strtok(get_accountstatususer(userarray, i, "user"), "\n");
        if (strcmp(ID, username) == 0)
        {
            if (strcmp(activity, "active") == 0)
            {
                nome = get_nameuser(userarray, i, "user");
                gender = get_genderuser(userarray, i, "user");
                idadee = idade(get_birthdateuser(userarray, i, "user"));
                avmedia = av_mediauser(ridearray, username);
                numviagens = num_viagensuser(ridearray, username);
                totalgasto = total_gasto(driverarray, ridearray, username);
                if(interativo == 0)
                fprintf(output, "%s;%c;%d;%.3f;%d;%.3f\n", nome, gender, idadee, avmedia, numviagens, totalgasto);
                else printf("%s;%c;%d;%.3f;%d;%.3f\n\n", nome, gender, idadee, avmedia, numviagens, totalgasto);
                free(nome);
            }
        }
        free(username);
        free(activity);
    }
    if(interativo == 0) fclose(output);
}
void query1driver(DRIVER *driverarray, RIDE *ridearray, int id, FILE *output)
{
    char *nome;
    char gender;
    int idadee;
    double avmedia;
    int numviagens;
    double totalauferido;
    char *activity;
    for (int i = 1; i <= maxdriver; i++)
    {
        if(driverisnull(driverarray, i) == 0) continue;
        if (get_iddriver(driverarray, i, "driver") == id)
        {
            activity = strtok(get_accountstatusdriver(driverarray, i, "driver"), "\n");
            if (strcmp(activity, "active") == 0)
            {
                nome = get_namedriver(driverarray, i, "driver");
                gender = get_genderdriver(driverarray, i, "driver");
                idadee = idade(get_birthdatedriver(driverarray, i, "driver"));
                avmedia = av_mediadriver(ridearray, i);
                numviagens = num_viagensdriver(ridearray, i);
                totalauferido = total_auferido(driverarray, ridearray, i);
                if(interativo == 0)
                fprintf(output, "%s;%c;%d;%.3f;%d;%.3f\n", nome, gender, idadee, avmedia, numviagens, totalauferido);
                else printf("%s;%c;%d;%.3f;%d;%.3f\n\n", nome, gender, idadee, avmedia, numviagens, totalauferido);
                free(nome);
            }
            free(activity);
        }
    }
    if(interativo == 0) fclose(output);
}
void query2(char query[], FILE *output, DRIVERMEDIA *avs, int t)
{
    int N;
    char *ID = strtok(query, " ");
    ID = strtok(NULL, "\n");
    sscanf(ID, "%d", &N);
    // DRIVERMEDIA *avs = malloc(sizeof *avs * MAX_DRIVER);
    for (int i = t; i > t - N; i--)
    {
        if(interativo == 0)
        fprintf(output, "%12.12d;%s;%.3f\n", avs[i].id, avs[i].nome, avs[i].avmedia);
        else printf("%12.12d;%s;%.3f\n", avs[i].id, avs[i].nome, avs[i].avmedia);
    }
    if(interativo == 0) fclose(output);
    else printf("\n");
}
void query3(USERDIST *userdist, char query[], FILE* output)
{
    int N;
    char *ID = strtok(query, " ");
    ID = strtok(NULL, "\n");
    sscanf(ID, "%d", &N);
    for (int i = 0; i < N; i++)
    {
        if (interativo == 0)
        {
            fprintf(output, "%s;%s;%d\n", userdist[i].username, userdist[i].nome, userdist[i].dist);   
        }
        else
        {
            printf("%s;%s;%d\n", userdist[i].username, userdist[i].nome, userdist[i].dist);
        }
    }
    if(interativo == 0) fclose(output);
    else printf("\n");
}
void query4(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output)
{
    double precomedio;
    char *city = strtok(query, " ");
    city = strtok(NULL, "\n");
    precomedio = preco_medio(driverarray, ridearray, city, NULL, NULL);
    if (precomedio == precomedio)
    {
        if(interativo == 0)
        fprintf(output, "%.3f\n", precomedio);
        else printf("%.3f\n\n", precomedio);
    }
    if(interativo == 0) fclose(output);
}
void query5(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output)
{
    double precomedio;
    char *data1;
    char *data2;
    strtok(query, " ");
    data1 = strtok(NULL, " ");
    data2 = strtok(NULL, "\n");
    precomedio = preco_medio(driverarray, ridearray, NULL, data1, data2);
    if (precomedio == precomedio)
    {
        if(interativo == 0)
        fprintf(output, "%.3f\n", precomedio);
        else printf("%.3f\n\n", precomedio);
    }
    if(interativo == 0) fclose(output);
}
void query6(RIDE *ridearray, RIDE2 *cityviagens, char query[], FILE *output)
{
    DATA *datatok1 = malloc(sizeof *datatok1);
    DATA *datatok2 = malloc(sizeof *datatok2);
    double soma = 0, counter = 0;
    double distmedia;
    char *data1;
    char *data2;
    data1 = strtok(NULL, " ");
    data2 = strtok(NULL, "\n");
    char *datea = strdup(data1);
    char *dateb = strdup(data2);
    sscanf(strtok(datea, "/"), "%d", &datatok1->dia);
    sscanf(strtok(NULL, "/"), "%d", &datatok1->mes);
    sscanf(strtok(NULL, "/"), "%d", &datatok1->ano);
    sscanf(strtok(dateb, "/"), "%d", &datatok2->dia);
    sscanf(strtok(NULL, "/"), "%d", &datatok2->mes);
    sscanf(strtok(NULL, "/"), "%d", &datatok2->ano);
    free(datea);
    free(dateb);
    int pointer = 0;
    while (cityviagens[pointer].a != NULL)
    {
        DATA *dateaux = get_datatok(ridearray, cityviagens[pointer].id);
        if (datecomparison(datatok1, dateaux) >= 0 && datecomparison(datatok2, dateaux) <= 0)
        {
            soma += get_distance(ridearray, cityviagens[pointer].id);
            counter++;
        }
        free(dateaux);
        pointer++;
    }
    distmedia = soma / counter;
    if (distmedia == distmedia)
    {
        if(interativo == 0)
        fprintf(output, "%.3f\n", distmedia);
        else printf("%.3f\n\n", distmedia);
    }
    if(interativo == 0) fclose(output);
}
void query7(FILE *output, CITYMEDIA *avs, int N)
{
    int pos = 0;
    while (avs[pos].nome != NULL)
    {
        pos++;
    }
    for (int i = pos - 1; i >= pos - N; i--)
    {
        if(interativo == 0)
        fprintf(output, "%12.12d;%s;%.3f\n", avs[i].id, avs[i].nome, avs[i].avmedia);
        else printf("%12.12d;%s;%.3f\n", avs[i].id, avs[i].nome, avs[i].avmedia);
    }
    if(interativo == 0) fclose(output);
    else printf("\n");
}
typedef struct
{
    int rideid;
    int driverid;
    char *contadriver;
    char *contauser;
    char *namedriver;
    char *user;
    char *nameuser;
} GENDER;
void query8(char query[], FILE *output, USER *userhash, DRIVER *driverarray, RIDE *ridearray)
{
    int idadee;
    char gen;
    char *aux;
    strtok(query, " ");
    aux = strtok(NULL, " ");
    sscanf(aux, "%c", &gen);
    aux = strtok(NULL, "\n");
    sscanf(aux, "%d", &idadee);
    GENDER *genderarr = malloc(sizeof *genderarr * maxuser);
    int pos = 0;
    for (int i = 1; i <= maxride; i++)
    {
        if(rideisnull(ridearray, i) == 0 || get_genderdriver(driverarray, get_driverid(ridearray, i), "driver") != gen) continue;
        int driverid = get_driverid(ridearray, i);
        char *driveracc = get_accountcreationdriver(driverarray, driverid, "driver");
        char *driverstatus = get_accountstatusdriver(driverarray, driverid, "driver");
        if (strcmp(driverstatus, "active\n") != 0 || idade(driveracc) < idadee)
        {
            free(driverstatus);
            free(driveracc);
            continue;
        }
        free(driverstatus);
        char *user = get_user(ridearray, i);
        int index = hashsearch(userhash, user);
        if (index == -1)
        {
            free(driveracc);
            free(user);
            continue;
        }
        if (get_genderuser(userhash, index, "user") == gen)
        {
            char *useracc = get_accountcreationuser(userhash, index, "user");
            char *userstatus = get_accountstatususer(userhash, index, "user");
            if (strcmp(userstatus, "active\n") == 0 && idade(useracc) >= idadee)
            {
                genderarr[pos].rideid = i;
                genderarr[pos].driverid = driverid;
                genderarr[pos].contadriver = strdup(driveracc);
                genderarr[pos].contauser = strdup(useracc);
                genderarr[pos].namedriver = get_namedriver(driverarray, driverid, "driver");
                genderarr[pos].user = strdup(user);
                genderarr[pos].nameuser = get_nameuser(userhash, index, "user");
                pos++;
            }
            free(useracc);
            free(userstatus);
        }
        free(driveracc);
        free(user);
    }
    for (int i = 0; i < pos; i++)
    {
        GENDER aux = genderarr[i];
        int j = i - 1;
        while (j >= 0 && datecomparisonchar(aux.contadriver, genderarr[j].contadriver, 0, 0, 0) > 0)
        {
            genderarr[j + 1] = genderarr[j];
            --j;
        }
        while (j >= 0 && datecomparisonchar(aux.contadriver, genderarr[j].contadriver, 0, 0, 0) == 0 && datecomparisonchar(aux.contauser, genderarr[j].contauser, 0, 0, 0) > 0)
        {
            genderarr[j + 1] = genderarr[j];
            --j;
        }
        while (j >= 0 && datecomparisonchar(aux.contadriver, genderarr[j].contadriver, 0, 0, 0) == 0 && datecomparisonchar(aux.contadriver, genderarr[j].contadriver, 0, 0, 0) == 0 && aux.rideid < genderarr[j].rideid)
        {
            genderarr[j + 1] = genderarr[j];
            --j;
        }
        genderarr[j + 1] = aux;
    }
    for (int i = 0; i < pos; i++)
    {
        if(interativo == 0)
        fprintf(output, "%12.12d;%s;%s;%s\n", genderarr[i].driverid, genderarr[i].namedriver, genderarr[i].user, genderarr[i].nameuser);
        else printf("%12.12d;%s;%s;%s\n", genderarr[i].driverid, genderarr[i].namedriver, genderarr[i].user, genderarr[i].nameuser);
    }
    free(genderarr);
    if(interativo == 0) fclose(output);
    else printf("\n");
}
void query9(RIDE *ridearray, char query[], FILE *output, RIDE2 *ridecity)
{
    strtok(query, " ");
    char *data1 = strtok(NULL, " ");
    char *data2 = strtok(NULL, "\n");
    char *datea = strdup(data1);
    char *dateb = strdup(data2);
    DATA *datatok1 = malloc(sizeof *datatok1);
    DATA *datatok2 = malloc(sizeof *datatok2);
    sscanf(strtok(datea, "/"), "%d", &datatok1->dia);
    sscanf(strtok(NULL, "/"), "%d", &datatok1->mes);
    sscanf(strtok(NULL, "/"), "%d", &datatok1->ano);
    sscanf(strtok(dateb, "/"), "%d", &datatok2->dia);
    sscanf(strtok(NULL, "/"), "%d", &datatok2->mes);
    sscanf(strtok(NULL, "/"), "%d", &datatok2->ano);
    free(datea);
    free(dateb);
    int pos = 0;
    for (int i = 1; i <= maxride; i++)
    {
        if(rideisnull(ridearray, i) == 0) continue;
        if (get_tip(ridearray, i) > 0)
        {
            DATA *dataat = get_datatok(ridearray, i);
            if (datecomparison(datatok1, dataat) >= 0 && datecomparison(datatok2, dataat) <= 0)
            {
                ridecity[pos].id = i;
                ridecity[pos].a = ridearray[i];
                pos++;
            }
            free(dataat);
        }
    }
    if (pos == 0)
    {
        return;
    }
    for (int i = 0; i < pos; i++)
    {
        int tmp = get_distance(ridearray, ridecity[i].id);
        RIDE2 aux = ridecity[i];
        DATA *dateat = get_datatok(ridearray, aux.id);
        int j = i - 1;
        while (j>=0 && tmp > get_distance(ridearray, ridecity[j].id))
        {
            ridecity[j + 1] = ridecity[j];
            --j;
        }
        DATA *dateaux = NULL;
        if (j >= 0)
            dateaux = get_datatok(ridearray, ridecity[j].id);
        while (j >= 0 && tmp == get_distance(ridearray, ridecity[j].id) && datecomparison(dateat, dateaux) < 0)
        {
            free(dateaux);
            dateaux = NULL;
            ridecity[j + 1] = ridecity[j];
            --j;
            if (j >= 0)
                dateaux = get_datatok(ridearray, ridecity[j].id);
        }
        while (j >= 0 && tmp == get_distance(ridearray, ridecity[j].id) && datecomparison(dateat, dateaux) == 0 && aux.id > ridecity[j].id)
        {
            free(dateaux);
            dateaux = NULL;
            ridecity[j + 1] = ridecity[j];
            --j;
            if (j >= 0)
                dateaux = get_datatok(ridearray, ridecity[j].id);
        }
        ridecity[j + 1] = aux;
        free(dateat);
        if (dateaux)
            free(dateaux);
    }
    for (int i = 0; i < pos; i++)
    {
        if(interativo == 0)
        fprintf(output, "%12.12d;%s;%d;%s;%.3f\n", ridecity[i].id, get_date(ridearray, ridecity[i].id), get_distance(ridearray, ridecity[i].id), get_cityride(ridearray, ridecity[i].id, "ride"), get_tip(ridearray, ridecity[i].id));
        else printf("%12.12d;%s;%d;%s;%.3f\n", ridecity[i].id, get_date(ridearray, ridecity[i].id), get_distance(ridearray, ridecity[i].id), get_cityride(ridearray, ridecity[i].id, "ride"), get_tip(ridearray, ridecity[i].id));
    }
    ridecity = NULL;
    if(interativo == 0) fclose(output);
    else printf("\n");
}