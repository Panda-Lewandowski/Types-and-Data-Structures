#ifndef TICK_H
#define TICK_H
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "automat.h"


typedef struct alarm {
    float time;
}alarm;

float tick_tock(queue* q1, queue* q2, automat* a);
#endif // TICK_H
