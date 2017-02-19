#include "liststack.h"
static int n = 0, m = 0;
static void **area;
static void **free_area;

StackNode *CreateStack() {
    /* As of now set the stack pointer to NULL, stack doesnt have any nodes. */
    area = calloc(STACKSIZE, sizeof(void*));
    free_area = calloc(STACKSIZE, sizeof(void*));
    return NULL;
}

inline int isEmpty(StackNode *top) {
    if(top == NULL) {
        return STACK_EMPTY;
    } else {
        return STACK_NOT_EMPTY;
    }
}

int push(StackNode **top, float data) {
    if(n == STACKSIZE) {
        printf("STACK IS FULL!");
        return STACK_FAILURE;
    }
    StackNode *temp=(StackNode *)malloc(sizeof(StackNode));

    if(NULL == temp) {
        printf("Memory allocation failed in Push operation.\n");
        return STACK_FAILURE;
    }
    temp->data = data;
    temp->next = *top;
    *top = temp;
    area[n] = (void*) temp;
    n++;
    if(m > 0) {
        free_area[m] = NULL;
        m--;
    }
    return STACK_SUCCESS;
}

float pop(StackNode **top) {
    if (STACK_EMPTY == isEmpty(*top)) {
        printf("Stack is empty, no element can be popped.\n");
        return STACK_FAILURE;
    }
    StackNode *temp = *top;
    free_area[m] = area[n - 1];
    area[n] = NULL;
    float data = temp->data;
    *top=temp->next;
    free(temp);
    n--;
    m++;
    return data;
}

int top(StackNode *top) {
    if(isEmpty(top) == STACK_EMPTY) {
        return STACK_FAILURE;
    } else {
        return top->data;
    }
}

void print_stack(StackNode *top) {
    printf("\n\nStack-list:\n");
    int  i = n - 1;
    if(top == NULL)
        printf("Empty");
    else {

        while(top!=NULL) {

            printf("%.3f - %p\n", top->data, area[i]);
            top=top->next;
            i--;
        }

    }
    printf("\n\nFree area:\n");
    for(int j = 0; j < m; j++)
        printf("%p ", free_area[j]);
}

