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
    for (int i = 1; i <= MAX_USER; i++)
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
    for (int i = 1; i <= MAX_DRIVER; i++)
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
    RIDE *rideaux = malloc(sizeof *rideaux * MAX_RIDE);
    rideaux = ridearray;
    USERDIST *dist = malloc(sizeof *dist * MAX_USER);
    int pos = 1;
    int disttot;
    for (int i = 1; i <= MAX_USER; i++)
    {
        disttot = 0;
        dist[pos].username = get_username(userarray, i);
        dist[pos].nome = get_nameuser(userarray, i, "user");
        for (int j = 1; j <= MAX_RIDE; j++)
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
    for (int i = MAX_USER; i > MAX_USER - N; i--)
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
void query6(RIDE *ridearray, char query[], FILE *output)
{
    double soma = 0, counter = 0;
    double distmedia;
    char *city;
    char *data1;
    char *data2;
    strtok(query, " ");
    city = strtok(NULL, " ");
    data1 = strtok(NULL, " ");
    data2 = strtok(NULL, "\n");
    for (int i = 1; i < MAX_RIDE; i++)
    {
        if (strcmp(get_cityride(ridearray, i, "ride"), city) == 0 && datecomparison(data1, get_date(ridearray, i)) >= 0 && datecomparison(data2, get_date(ridearray, i)) <= 0)
        {
            soma += get_distance(ridearray, i);
            counter++;
        }
    }
    distmedia = soma / counter;
    if (distmedia == distmedia)
    {
        fprintf(output, "%.3f\n", distmedia);
    }
    fclose(output);
}
void query7(FILE *output, CITYMEDIA *avs2 , int N)
{
    CITYMEDIA *avs = malloc(sizeof *avs * MAX_DRIVER);
    int pos2 = 0;
    while(avs2[pos2].nome != NULL)
    {
        pos2++;
    }
    pos2--;
    int pos3 = 0;
    for (int i = 0; i < pos2; i++)
    {
        if (strcmp(avs2[i].activity, "active\n") == 0)
        {
            avs[pos3] = avs2[i];
            pos3++;
        }
    }
    for (int i = 0; i < pos3; i++)
    {
        double tmp = avs[i].avmedia;
        CITYMEDIA aux = avs[i];
        int j = i - 1;
        while (tmp < avs[j].avmedia && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        while (tmp == avs[j].avmedia && aux.id < avs[j].id && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        avs[j + 1] = aux;
    }
    for (int i = pos3 - 1; i >= pos3 - N; i--)
    {
        fprintf(output, "%12.12d;%s;%.3f\n", avs[i].id, avs[i].nome, avs[i].avmedia);
    }
    avs = NULL;
    fclose(output);
    free(avs);
}

void query9(RIDE *ridearray, char query[], FILE *output, RIDE2 *ridecity)
{
    strtok(query, " ");
    char *data1 = strtok(NULL, " ");
    char *data2 = strtok(NULL, "\n");
    int pos = 0;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
        char *dataat = get_date(ridearray, i);
        if (datecomparison(dataat, data1) <= 0 && datecomparison(dataat, data2) >= 0 && get_tip(ridearray, i) > 0)
        {
            ridecity[pos].id = i;
            ridecity[pos].a = ridearray[i];
            pos++;
        }
        free(dataat);
    }
    if (pos == 0)
    {
        return;
    }
    for (int i = 0; i < pos; i++)
    {
        int tmp = get_distance(ridearray, ridecity[i].id);
        RIDE2 aux = ridecity[i];
        int j = i - 1;
        while (tmp > get_distance(ridearray, ridecity[j].id))
        {
            ridecity[j + 1] = ridecity[j];
            --j;
        }
        while (tmp == get_distance(ridearray, ridecity[j].id) && datecomparison(get_date(ridearray, ridecity[j].id), get_date(ridearray, aux.id)) > 0)
        {
            ridecity[j + 1] = ridecity[j];
            --j;
        }
        while (tmp == get_distance(ridearray, ridecity[j].id) && datecomparison(get_date(ridearray, ridecity[j].id), get_date(ridearray, aux.id)) == 0 && aux.id > ridecity[j].id)
        {
            ridecity[j + 1] = ridecity[j];
            --j;
        }
        ridecity[j + 1] = aux;
    }
    for (int i = 0; i < pos; i++)
    {
        fprintf(output, "%12.12d;%s;%d;%s;%.3f\n", ridecity[i].id, get_date(ridearray, ridecity[i].id), get_distance(ridearray, ridecity[i].id), get_cityride(ridearray, ridecity[i].id, "ride"), get_tip(ridearray, ridecity[i].id));
    }
    ridecity = NULL;
    fclose(output);
}