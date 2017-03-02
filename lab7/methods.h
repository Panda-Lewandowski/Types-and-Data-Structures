#ifndef METHODS_H
#define METHODS_H
#define OK 0
#define ERR_NO_FILE -1
#define ERR_FILE_EMPTY -2
#define ERR_INPUT -3
#define ERR_DELETE -4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//BINARY TREE

struct node_s
{
    char keyword[20];
    char HELP[1000];
    struct node_s *left, *right, *par;
};

typedef struct node_s node;

typedef struct
{
    node *root;
}tree;

void init_tree(tree *tr);
void init_node(node *temp);
void init_root(tree *tr);
int is_left(node *nod);
int is_right (node *nod);
node* min(node *root);
node* max (node *root);
node* next(node *temp);
int add(tree *tr, node *data);
node* search(tree *tr, char *keyword, int* count, int mode);
int delete_keyword(tree *tr, char *keyword);
void get_balanced_tree(tree *tr);
node* balance(node *nod);
void print_tree(struct node_s * nod, int level);

//HASH-TABLE

struct node_l
{
    char keyword[20];
    char HELP[1000];
    struct node_l *next;
};

typedef struct node_l Hash_row;

Hash_row** init_hash(int n);
int hash(char *keyword, int n);
void add_open_hash(Hash_row **hashtable, node *temp, int n);
int add_closed_hash(Hash_row **hashtable, node *temp, int n);
void print_hashtable(Hash_row **hashtable, int n);
void delete_open_hash(Hash_row **hashtable, char *keyword, int n);
void delete_closed_hash(Hash_row **hashtable, char *keyword, int n);
void open_hash_search(Hash_row *hashtable, char *keyword, int n, int *count, int mode);
int closed_hash_search(Hash_row **hashtable, char *keyword, int n, int *count, int mode);

#endif // METHODS_H
