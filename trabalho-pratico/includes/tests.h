#ifndef tests_h
#define tests_h
#include <stdlib.h>
#include <stdio.h>

void checkresults(FILE *output, FILE *test, int it);
void compare(FILE *output, char *testpath, char *filename, int it);

#endif