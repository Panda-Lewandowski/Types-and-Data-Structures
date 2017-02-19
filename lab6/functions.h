#define OK 0
#define RC 2
#define FILE_NOT_FOUND -1
#define FILE_IS_EMPTY -1
#define DELETING_ERROR -3

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <time.h>

struct node_s
{
    int reps;
    char word[64];  /// Слово
    struct node_s *left, *right, *par;  /// Потомки
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
node* search(tree *tr, char *word);
int delete_word(tree *tr, char *word);
void print_tree(struct node_s * nod, int level);

//int output(struct tree *tree, FILE *f);
//int out_control(struct tree *tree);
