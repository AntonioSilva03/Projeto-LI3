#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/tests.h"
#include "../includes/maxs.h"

void checkresults(FILE *output, FILE *test, int it)
{
    int ch1 = fgetc(output);
    int ch2 = fgetc(test);
    while(ch1 != EOF && ch2 != EOF)
    {
        if (ch1 != ch2)
        {
            printf("Test %d not passed\n", it);
            return;
        }
        ch1 = fgetc(output);
        ch2 = fgetc(test);
    }
    if(ch1 == EOF && ch2 == EOF) printf("Test %d passed\n", it);
    else printf("Test %d not passed\n", it);
    fclose(output);
    fclose(test);
}

void compare(FILE *output, char *testpath, char *filename, int it)
{
    char testpath2[BUFSIZ];
    strcpy(testpath2, testpath);
    strcat(testpath2, "/");
    strcat(testpath2, filename);
    FILE *test = fopen(testpath2, "r");
    if(test == NULL)
    {
        printf("Caminho para file de testes inválido\n");
        testes = 0;
        return;
    }
    checkresults(output, test, it);
}