#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct IA
{
    int i;
    int Nk;

    struct IA *next;
};
unsigned long long tick(void);
int summtrix(float *matr1, float *matr2, float *matr3,int n,int m);
int time_test(int fill);
int create_matrix(float *matr, int n, int m, int fill, int *count);
int matrTolist(float *matr, int n, int m, struct IA *IA);
int matrInput(int n, int m, float *Matr, float *A, int *JA, struct IA *IA, int *lenA);
void matrDefault(float *Matr, int n, int m,float *A, int *JA, struct IA *IA, int *lenA);
void print(int n, int m, float *Matr, float *A, int *JA, struct IA *IA, int lenA);
int printmatrix(float *matr, int n, int m);
int Plus_R(int n, int m, float *A1, float *A2, int *JA1, int *JA2, struct IA *IA1, struct IA *IA2, int lenA1, int lenA2,
           float *A3, int *JA3, struct IA *IA3, int *lenA3);
struct IA* create(int i, int num);
struct IA* add(struct IA *node, int i, int num);
void free_all(struct IA *head);

#endif // HEAD_H
