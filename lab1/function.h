#ifndef FUNCTION_H
#define FUNCTION_H

#include "chislo.h"

//multiplication.c
int multiplicate(struct chislo *chislo1,struct chislo chislo2);
//read_chislo.c
int read_chislo(struct chislo *chislo, int type);
int set_array_back(int *chislo);
//output.c
void print_instruction(void);
void print_error(const int ERROR);
void print_array(const int mass[],const int size);
void print_chislo(struct chislo chislo);
//utils.c
void set_array_null(int *A,int len);
int count(char c,char *ch1);
int check_simbol(char s);

#endif // FUNCTION_H

