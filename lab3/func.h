#ifndef FUNC_C
#define FUNC_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 40
#define MAX_FL 20

#define ERR_READ -1
#define INVALID_FLOOR -2
#define OVERFLOW -3
#define INCOMPLETE_DATA -4

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
    char isPrivate;
};

struct flat {
    int index;
    char address[20];
    float square;
    int rooms;
    float price;
    int floor;
    union
    {
        struct cellar cell;
        struct balcony balc;
        struct attic att;
    } ad;

};

struct key
{
    int index;
    int floor;
};


int read(FILE *f, struct flat table[], struct key key[]);
void private_attic(struct flat table[]);
int add(struct flat *table, struct key *key);
int del(struct flat *table, struct key *key);
void print(struct flat table[], struct key key[]);
void shell_key (struct key key[]);
void shell_table (struct flat table[]);
void insert_key(struct key key[]);
void print_table(struct flat table[]);
void print_key(struct key key[]);
void insert_table(struct flat table[]);
#endif // FUNC_C
