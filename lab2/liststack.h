#ifndef LISTSTACK_H
#define LISTSTACK_H

#include <stdio.h>
#include<stdlib.h>
typedef struct StackNode {
    float data;
    struct StackNode *next;
} StackNode;

#define STACK_SUCCESS 0
#define STACK_FAILURE -1
#define STACKSIZE 5
#define STACK_EMPTY 1
#define STACK_NOT_EMPTY 0

/* Basic operations on stack */

StackNode *CreateStack( );

int push(StackNode **, float );
float pop(StackNode **);
int top(StackNode *);
int isEmpty(StackNode *);
void print_stack(StackNode *);
#endif // LISTSTACK_H
