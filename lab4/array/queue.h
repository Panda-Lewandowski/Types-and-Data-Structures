#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#define QUEUE_SUCCESS 0
#define QUEUE_FAILURE -1
#define ELEM 4000

#define T1_MAX 5
#define T1_MIN 1

#define T2_MAX 3
#define T2_MIN 0

#define T3_MAX 4
#define T3_MIN 0

#define T4_MAX 1
#define T4_MIN 0


enum req_type {NONE, T1, T2};


typedef struct queue {
    float* data_store;
    int front;
    int capacity;
    int elts;
    int ever_elts;
    enum req_type type;
} queue_t;

queue_t *new_queue(int capacity, enum req_type t);
int Enqueue(queue_t* queue, float item, enum req_type t);
void queue_free(queue_t* queue);
float Dequeue(queue_t* queue);
void queue_print(queue_t* q);
#endif // QUEUE_H
