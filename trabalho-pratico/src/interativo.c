#include <stdlib.h>
#include <stdio.h>
#include "../includes/interativo.h"
#include <string.h>

void iniciointerativo()
{
    printf("\n");
    printf("Bem-vindo ao modo interativo.\n");
    printf("\n");
    printf("Antes de começar introduza um caminho para a pasta de dados:\n");
    printf("Caminho: ");
}

char *getfilepath()
{
    char *path = malloc(500);
    if (scanf("%s", path))
        return path;
    else
        return NULL;
}

void menu()
{
    printf("\nMenu:\n\n");
    int input;
    printf("Ver instruções de execução(1)\n");
    printf("Executar querys(2)\n\n");
    if(scanf("%d", &input))
    {
        if (input == 1)
        {
            instrucoes();
            return;
        }
        else if(input == 2)
            return;
        else menu();
    }
}
void instrucoes()
{
    printf("\nInstruções:\n\n");
    printf("Query 1: 1 'ID de condutor' ou 1 'Username de utilizador' // Apresenta um resumo do perfil de um condutor ou utilizador.\n");
    printf("Query 2: 2 'N' // Sendo N um número, lista os N condutores com maior avaliação média.\n");
    printf("Query 3: 3 'N' // Sendo N um número, lista os N condutores com maior distância viajada.\n");
    printf("Query 4: 4 'Cidade' // Dada uma cidade, apresenta o preço médio de uma viagem nessa cidade.\n");
    printf("Query 5: 5 'data1' 'data2' // Dadas duas datas, apresenta o preço médio das viagens nesse intervalo de tempo.\n");
    printf("Query 6: 6 'Cidade' 'data1' 'data2' // Dada uma cidade e duas datas apresenta o preço medio das viagens nessa cidade nesse intervalo de tempo.\n");
    printf("Query 7: 7 'N' 'Cidade' // Dado um número e uma cidade apresenta o top N condutores com maior avaliação média nessa cidade.\n");
    printf("Query 8: 8 'Género' 'N' // Dado um género M ou F e um número, apresenta todas as viagens em que o condutor e o utilizador são desse género e tem contas com N ou mais anos.\n");
    printf("Query 9: 9 'data1' 'data2' // Dadas duas datas, apresenta todas as viagens em que o utilizador deu gorjeta, nesse período de tempo.\n");
    printf("\n");
}
char *execucao(char line[])
{
    if (fgets(line, BUFSIZ, stdin))
    {
        if (strcmp(line, "0\n") == 0)
        {
            return NULL;
        }
        else
        {
            printf("\n");
            return line;
        }
    }
    printf("\n");
    return NULL;
}

void fiminterativo()
{
    printf("A limpar dados e a sair...\n");
}