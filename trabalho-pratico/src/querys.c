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
                fprintf(output, "%s;%c;%d;%.3f;%d;%.3f\n", nome, gender, idadee, avmedia, numviagens, totalgasto);
                free(nome);
            }
        }
        free(username);
        free(activity);
    }
    fclose(output);
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
                fprintf(output, "%s;%c;%d;%.3f;%d;%.3f\n", nome, gender, idadee, avmedia, numviagens, totalauferido);
                free(nome);
            }
            free(activity);
        }
    }
    fclose(output);
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
        fprintf(output, "%12.12d;%s;%.3f\n", avs[i].id, avs[i].nome, avs[i].avmedia);
    }
    fclose(output);
}
void query3(USER *userarray, RIDE *ridearray, char query[], FILE *output)
{
    int N;
    char *ID = strtok(query, " ");
    ID = strtok(NULL, "\n");
    sscanf(ID, "%d", &N);
    RIDE *rideaux = malloc(sizeof *rideaux * maxride);
    rideaux = ridearray;
    USERDIST *dist = malloc(sizeof *dist * maxuser);
    int pos = 1;
    int disttot;
    for (int i = 1; i <= maxuser; i++)
    {
        disttot = 0;
        dist[pos].username = get_username(userarray, i);
        dist[pos].nome = get_nameuser(userarray, i, "user");
        for (int j = 1; j <= maxride; j++)
        {
            if (rideaux[j] != NULL)
            {
                if (strcmp(get_user(rideaux, j), dist[pos].username) == 0)
                {
                    disttot += get_distance(rideaux, j);
                    rideaux[j] = NULL;
                }
            }
        }
        dist[pos].dist = disttot;
        pos++;
    }
    for (int i = 1; i < pos; i++)
    {
        int tmp = dist[i].dist;
        USERDIST aux = dist[i];
        int j = i - 1;
        while (tmp < dist[j].dist && j >= 0)
        {
            dist[j + 1] = dist[j];
            --j;
        }
        dist[j + 1] = aux;
    }
    for (int i = maxuser; i > maxuser - N; i--)
    {
        fprintf(output, "%s;%s;%d\n", dist[i].username, dist[i].nome, dist[i].dist);
    }
    fclose(output);
}
void query4(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output)
{
    double precomedio;
    char *city = strtok(query, " ");
    city = strtok(NULL, "\n");
    precomedio = preco_medio(driverarray, ridearray, city, NULL, NULL);
    if (precomedio == precomedio)
    {
        fprintf(output, "%.3f\n", precomedio);
    }
    fclose(output);
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
        fprintf(output, "%.3f\n", precomedio);
    }
    fclose(output);
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
        fprintf(output, "%.3f\n", distmedia);
    }
    fclose(output);
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
        fprintf(output, "%12.12d;%s;%.3f\n", avs[i].id, avs[i].nome, avs[i].avmedia);
    }
    fclose(output);
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
        while (tmp > get_distance(ridearray, ridecity[j].id))
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
        fprintf(output, "%12.12d;%s;%d;%s;%.3f\n", ridecity[i].id, get_date(ridearray, ridecity[i].id), get_distance(ridearray, ridecity[i].id), get_cityride(ridearray, ridecity[i].id, "ride"), get_tip(ridearray, ridecity[i].id));
    }
    ridecity = NULL;
    fclose(output);
}