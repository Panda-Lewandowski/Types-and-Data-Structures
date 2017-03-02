#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <stdlib.h>

int scan(FILE *f, int **Matr, int n);
void print_graph(FILE *out, int **Matr, int n, int *path, int p_l);

int find(int **Matr, int n, int *path, int *p_l);
int shir(int **Matr, int n, int num, int *Q, int *q_l, int *M, int *path, int *p_l);
int is_in_q(int *Q, int n, int i);

int** alloc_matr_rows(int n);
void free_matr_rows(int **data, int n);

#endif // HEAD_H
