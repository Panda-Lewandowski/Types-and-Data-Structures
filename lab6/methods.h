#ifndef METHODS_H
#define METHODS_H
#define OK 0
#define ERR_NO_FILE -1
#define ERR_FILE_EMPTY -1
#define ERR_DELETE -3

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <time.h>

struct node_s
{
    int reps;
    char word[50];
    struct node_s *left, *right, *par;
};

typedef struct node_s node;

typedef struct
{
    node *root;
} tree;

void init_tree(tree *tr);
void init_node(node *temp);
void init_root(tree *tr);
int is_left(node *nod);
void add(tree *tr, char *word);
node* search(tree *tr, char *word, int *n);
int delete_word(tree *tr, char *word);
void print_tree(struct node_s * nod, int level);
void postOrder(const struct node_s * nod);
void inOrder(const struct node_s * nod);
void preOrder(const struct node_s * nod);
#endif // METHODS_H
