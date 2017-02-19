#ifndef AUTOMAT_H
#define AUTOMAT_H
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct automat {
    qNode * now;
    enum req_type prev;
    float work_time;
    int count_t1;
    int count_t2;
    float downtime;
    float work;
} automat;


void refresh(queue* q1, queue* q2, automat *a);
automat* init_auto();
float randfrom(int min, int max);
#endif // AUTOMAT_H
