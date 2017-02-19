#include "automat.h"

automat* init_auto() {
    automat * my_auto = malloc(sizeof(automat));
    if(my_auto == NULL)
        return NULL;
    else {
        my_auto->prev = NONE;
        my_auto->now_t = NONE;
        my_auto->now = -1;
        my_auto->work_time = 0;
        my_auto->count_t1 = 0;
        my_auto->count_t2 = 0;
        my_auto->downtime = 0;
        my_auto->work = 0;
        return my_auto;
    }

}


void refresh(queue_t *q1, queue_t *q2, automat* a) {
    if(a->now != -1) {//printf("%f\n", a->now);
        if(a->now_t == T1) {//printf("-----1a-----\n");
            Dequeue(q1);
            a->now = -1;
            a->prev = T1;
        }
        else if(a->now_t == T2) {
            Dequeue(q2);
            a->now = -1;
            a->prev = T2;
        }
        //printf(">>>>>>%d\n", a->prev);
        if(a->prev == T1 && q1->elts > 0) {//printf("-----1/1a-----\n");
            a->now = q1->data_store[0];
            a->now_t = T1;
        }
        else if(a->prev == T1 && q1->elts == 0 && q2->elts > 0) {
            a->now = q2->data_store[0];//printf("-----1/2a-----\n");
            a->now_t = T2;
        }
        else if(a->prev == T2 && q2->elts > 0) {//printf("-----1\3a-----\n");
            a->now = q2->data_store[0];
            a->now_t = T2;
        }
        else if(a->prev == T2 && q2->elts == 0 && q1->elts > 0) {
            a->now = q1->data_store[0];//printf("-----1\4a-----\n");
            a->now_t = T1;
        }
        else
            return;//printf("fuuuuuuuuuuuuuuuuuuuuck");

        if(a->now_t == T1) {
            a->count_t1++;
            a->work_time = randfrom(T3_MIN, T3_MAX);
            a->work += a->work_time;
            //printf(">>>>>>>>>>%f", a->work_time);
        }
        else if(a->now_t == T2) {
            a->count_t2++;
            a->work_time = randfrom(T4_MIN, T4_MAX);
            a->work += a->work_time;
            //printf(">>>>>>>>>>%f", a->work_time);
        }
    }
    else /*if(a->now == -1)*/{//printf("-----2a-----");

        if(q1->elts == 0 && q2->elts == 0) {
            a->downtime += a->work_time;//printf("-----2.1a-----");
            return;
        }
        else if(q1->elts > 0 && q2->elts == 0) {//printf("-----2.2-----");
            a->now = q1->data_store[0];
            a->now_t = T1;
            a->count_t1++;
            a->work_time = randfrom(T3_MIN, T3_MAX);
            a->work += a->work_time;
            //printf(">>>>>>>>>>%f", a->work_time);
        }
        else if(q1->elts == 0 && q2->elts > 0) {//printf("-----2.3a-----");
            a->now = q2->data_store[0];
            a->now_t = T2;
            a->count_t2++;
            a->work_time = randfrom(T4_MIN, T4_MAX);
            a->work += a->work_time;
            //printf(">>>>>>>>>>%f", a->work_time);
        }
        else {
            if(q1->elts > 0 && q2->elts > 0) {//printf("-----2.4a-----");
                if(a->prev == T1) {
                    a->now = q1->data_store[0];
                    a->now_t = T1;
                    a->count_t1++;
                    a->work_time = randfrom(T3_MIN, T3_MAX);
                    a->work += a->work_time;
                    //printf(">>>>>>>>>>%f", a->work_time);
                }
                if(a->prev == T2) {//printf("-----2.5a-----");
                    a->now = q2->data_store[0];
                    a->now_t = T2;
                    a->count_t2++;
                    a->work_time = randfrom(T4_MIN, T4_MAX);
                    a->work += a->work_time;
                    //printf(">>>>>>>>>>%f", a->work_time);
                }

            }

        }
    }


}


float randfrom(int min, int max)
{
    int range = max - min;
    int div = RAND_MAX / range;
    //printf("%f  %d\n", (float) rand() / div, min);
    return  min + ((float) rand() / div);
}
