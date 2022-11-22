#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/querys.h"
#include "../includes/data.h"
#include "../includes/calculos.h"

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
        activity = strtok(get_accountstatus(userarray, NULL, i, "user"), "\n");
        if (strcmp(ID, username) == 0)
        {
            if (strcmp(activity, "active") == 0)
            {
                nome = get_name(userarray, NULL, i, "user");
                gender = get_gender(userarray, NULL, i, "user");
                idadee = idade(get_birthdate(userarray, NULL, i, "user"));
                avmedia = av_mediauser(ridearray, username);
                numviagens = num_viagensuser(ridearray, username);
                totalgasto = total_gasto(driverarray, ridearray, username);
                fprintf(output, "%s;%c;%d;%.3f;%d;%.3f\n", nome, gender, idadee, avmedia, numviagens, totalgasto);
            }
        }
    }
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
        if (get_id(driverarray, NULL, i, "driver") == id)
        {
            activity = strtok(get_accountstatus(NULL, driverarray, i, "driver"), "\n");
            if (strcmp(activity, "active") == 0)
            {
                nome = get_name(NULL, driverarray, i, "driver");
                gender = get_gender(NULL, driverarray, i, "driver");
                idadee = idade(get_birthdate(NULL, driverarray, i, "driver"));
                avmedia = av_mediadriver(ridearray, i);
                numviagens = num_viagensdriver(ridearray, i);
                totalauferido = total_auferido(driverarray, ridearray, i);
                fprintf(output, "%s;%c;%d;%.3f;%d;%.3f\n", nome, gender, idadee, avmedia, numviagens, totalauferido);
            }
        }
    }
}

typedef struct
{
    int id;
    char *nome;
    char *datarecente;
    double avmedia;
    char *activity;
} DRIVERMEDIA;

void query2(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output)
{
    int N;
    char *ID = strtok(query, " ");
    ID = strtok(NULL, "\n");
    sscanf(ID, "%d", &N);
    DRIVERMEDIA *avs = malloc(sizeof *avs * MAX_DRIVER);
    for (int i = 1; i <= MAX_DRIVER; i += 2)
    {
        avs[i].id = i;
        avs[i + 1].id = i + 1;
        avs[i].activity = get_accountstatus(NULL, driverarray, i, "driver");
        avs[i + 1].activity = get_accountstatus(NULL, driverarray, i + 1, "driver");
        avs[i].nome = get_name(NULL, driverarray, i, "driver");
        avs[i + 1].nome = get_name(NULL, driverarray, i + 1, "driver");
        av_media_data_recente(ridearray, i, i + 1, &avs[i].datarecente, &avs[i].avmedia, &avs[i + 1].datarecente, &avs[i + 1].avmedia);
    }
    int t = 1;
    for (int i = 1; i <= MAX_DRIVER; i++)
    {
        if (strcmp(avs[i].activity, "active\n") == 0)
        {
            avs[t] = avs[i];
            t++;
        }
    }
    for (int i = 1; i <= t; i++)
    {
        double tmp = avs[i].avmedia;
        DRIVERMEDIA aux = avs[i];
        int j = i - 1;
        while (tmp < avs[j].avmedia && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        while (tmp == avs[j].avmedia && datecomparison(avs[j].datarecente, aux.datarecente) < 0 && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        while (tmp == avs[j].avmedia && datecomparison(avs[j].datarecente, aux.datarecente) == 0 && aux.id > avs[j].id && j >= 0)
        {
            avs[j + 1] = avs[j];
            --j;
        }
        avs[j + 1] = aux;
    }
    for (int i = t; i > t - N; i--)
    {
        fprintf(output, "%12.12d;%s;%.3f\n", avs[i].id, avs[i].nome, avs[i].avmedia);
    }
}

typedef struct
{
    char *username;
    char *nome;
    int dist;
} USERDIST;

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
        dist[pos].nome = get_name(userarray, NULL, i, "user");
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
}
void query4(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output)
{
    double precomedio;
    char *city = strtok(query, " ");
    city = strtok(NULL, "\n");
    precomedio = preco_medio(driverarray, ridearray, city, NULL, NULL);
    fprintf(output, "%.3f\n", precomedio);
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
    fprintf(output, "%.3f\n", precomedio);
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
        if (strcmp(get_city(NULL, ridearray, i, "ride"), city) == 0 && datecomparison(data1, get_date(ridearray, i)) >= 0 && datecomparison(data2, get_date(ridearray, i)) <= 0)
        {
            soma += get_distance(ridearray, i);
            counter++;
        }
    }
    distmedia = soma / counter;
    fprintf(output, "%.3f\n", distmedia);
}

typedef struct
{
    int id;
    char *nome;
    double avmedia;
    char *activity;
} CITYMEDIA;

typedef struct
{
    int id;
    RIDE a;
} RIDE2;

void query7(DRIVER *driverarray, RIDE *ridearray, char query[], FILE *output)
{
    int N;
    char *ID;
    char *city;
    strtok(query, " ");
    ID = strtok(NULL, " ");
    sscanf(ID, "%d", &N);
    city = strtok(NULL, "\n");
    RIDE2 *cityviagens = malloc(sizeof *cityviagens * MAX_RIDE);
    CITYMEDIA *avs = malloc(sizeof *avs * MAX_USER);
    int pos = 0;
    for (int i = 1; i <= MAX_RIDE; i++)
    {
        if (strcmp(get_city(NULL, ridearray, i, "ride"), city) == 0)
        {
            cityviagens[pos].id = i;
            cityviagens[pos].a = ridearray[i];
            pos++;
        }
    }
    int pos2 = 0;
    double media;
    int counter;
    for (int i = 0; i < pos; i++)
    {
        media = 0;
        counter = 0;
        if (cityviagens[i].a != NULL)
        {
            avs[pos2].id = get_driverid(ridearray, cityviagens[i].id);
            avs[pos2].nome = get_name(NULL, driverarray, avs[pos2].id, "driver");
            avs[pos2].activity = get_accountstatus(NULL, driverarray, avs[pos2].id, "driver");
            media += get_scoredriver(ridearray, cityviagens[i].id);
            cityviagens[i].a = NULL;
            counter = 1;
            for (int j = i + 1; j < pos; j++)
            {
                if (cityviagens[j].a != NULL)
                {
                    if (get_driverid(ridearray, cityviagens[i].id) == get_driverid(ridearray, cityviagens[j].id))
                    {
                        media += get_scoredriver(ridearray, cityviagens[j].id);
                        cityviagens[j].a = NULL;
                        counter++;
                    }
                }
            }
            avs[pos2].avmedia = media / counter;
            pos2++;
        }
    }
    int pos3 = 0;
    for (int i = 0; i < pos2; i++)
    {
        if (strcmp(avs[i].activity, "active\n") == 0)
        {
            avs[pos3] = avs[i];
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
}