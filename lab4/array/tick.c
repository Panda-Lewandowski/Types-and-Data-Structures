#include "tick.h"

static float time_now = 0;
static alarm al1;
static alarm al2;
static alarm al3;
float tick_tock(queue_t *q1, queue_t *q2, automat* a) {


    if(!al1.time && !al2.time && !al3.time) {
        al1.time = randfrom(T1_MIN, T1_MAX);
        al2.time = randfrom(T2_MIN, T2_MAX);
        time_now = (al1.time < al2.time ? al1.time : al2.time);
        if(al1.time <= al2.time) {
            Enqueue(q1, randfrom(T1_MIN, T1_MAX), T1);
            a->count_t1++;
            a->now = q1->data_store[0];
            a->now_t = T1;
            a->work_time = randfrom(T3_MIN, T3_MAX);
            al1.time = time_now + q1->data_store[0];
        }
        else {
            Enqueue(q2, randfrom(T2_MIN, T2_MAX), T2);
            a->count_t2++;
            a->now = q2->data_store[0];
            a->now_t = T2;
            a->work_time = randfrom(T4_MIN, T4_MAX);
            al2.time = time_now + q2->data_store[0];
        }
        al3.time = time_now + a->work_time;
    }
    else {
        if(al1.time <= al2.time && al1.time <= al3.time) {
            time_now = al1.time;
            Enqueue(q1, randfrom(T1_MIN, T1_MAX), T1);
            al1.time += q1->data_store[q1->front-1];
        }
        if(al2.time <= al1.time && al2.time <= al3.time) {
            time_now = al2.time;
            Enqueue(q2, randfrom(T2_MIN, T2_MAX), T2);
            al2.time += q2->data_store[q2->front-1];
        }
        if(al3.time <= al2.time && al3.time <= al1.time) {
            refresh(q1, q2, a);
            time_now = al3.time;
            al3.time += a->work_time;
        }
    }
    /*printf("STATISTIC:\n"
       "Automat:\n"
       "count q1 : %d\n"
       "count q2 : %d\n"
       "a->prev : %d\n"
       "a->work time %f\n\n", a->count_t1,a->count_t2, a->prev, a->work_time);
        printf("al1 %f\n"
           "al2 %f\n"
           "al3 %f\n\n", al1.time, al2.time, al3.time);
    queue_print(q1);
    printf("------\n");
    queue_print(q2);*/

    return time_now;

}



