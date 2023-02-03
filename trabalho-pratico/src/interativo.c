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