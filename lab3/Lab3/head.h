#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 100

struct balcony
{
    char isB;
    float squareB;
};

struct cellar
{
    char isC;
};

struct attic
{
    char isA;
    float squareA;
    int isPrivate;
};

struct flats
{
    char addr[25];
    float square;
    int rooms;
    float price;
    int floor;
    union
    {
        struct cellar cell;
        struct balcony balc;
        struct attic att;
    } u;
};

struct keys
{
    int n_f;
    float price;
};

int read(FILE *f, struct flats table[], struct keys key[], int *n);
void print(struct flats table[], struct keys key[], int n);
void fprint(FILE **f, struct flats table[], int n);

void private_attic(struct flats table[], int n);
int add_end(struct flats *table, struct keys *key, int *n);
int del(struct flats *table, struct keys *key, int *n, int i);

#endif // HEAD_H
