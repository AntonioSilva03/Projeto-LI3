#ifndef interativo_h
#define interativo_h
#include <stdlib.h>
#include <stdio.h>

void iniciointerativo();
char *getfilepath();
void menu();
void instrucoes();
char *execucao(char line[]);
void fiminterativo();

#endif