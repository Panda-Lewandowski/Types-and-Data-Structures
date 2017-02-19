#include "automat.h"
//#define LOG
automat* init_auto() {
    automat * my_auto = malloc(sizeof(automat));
    if(my_auto == NULL)
        return NULL;
    else {
        my_auto->now = NULL;
        my_auto->prev = NONE;
        my_auto->work_time = 0;
        my_auto->count_t1 = 0;
        my_auto->count_t2 = 0;
        my_auto->downtime = 0;
        my_auto->work = 0;
        return my_auto;
    }

}


void refresh(queue* q1, queue* q2, automat* a) {
    if(a->now) {
        a->prev = a->now->type;
        if(a->now->type == T1) {
#ifdef LOG
            printf("Deleting element in <%d> on address: %p\n", T1, (void*) (q1->front));
#endif
            Dequeue(q1);
            a->now = NULL;
        }
        else if(a->now->type == T2) {
#ifdef LOG
            printf("Deleting element in <%d> on address: %p\n", T2, (void*) (q2->front));
#endif
            Dequeue(q2);
            a->now = NULL;
        }

        if(a->prev == T1 && q1->elts > 0)
            a->now = q1->front;
        else if(a->prev == T1 && q1->elts == 0 && q2->elts > 0)
            a->now = q2->front;
        else if(a->prev == T2 && q2->elts > 0)
            a->now = q2->front;
        else if(a->prev == T2 && q2->elts == 0 && q1->elts > 0)
            a->now = q1->front;
        else
            return;

        if(a->now->type == T1) {
            a->count_t1++;
            a->work_time = randfrom(T3_MIN, T3_MAX);
            a->work += a->work_time;
        }
        else if(a->now->type == T2) {
            a->count_t2++;
            a->work_time = randfrom(T4_MIN, T4_MAX);
            a->work += a->work_time;
        }
    }
    else {

        if(q1->elts == 0 && q2->elts == 0) {
            a->downtime += a->work_time;
            return;
        }
        else if(q1->elts > 0 && q2->elts == 0) {
            a->now = q1->front;
            a->count_t1++;
            a->work_time = randfrom(T3_MIN, T3_MAX);
            a->work += a->work_time;
        }
        else if(q1->elts == 0 && q2->elts > 0) {
            a->now = q2->front;
            a->count_t2++;
            a->work_time = randfrom(T4_MIN, T4_MAX);
            a->work += a->work_time;
        }
        else {
            if(q1->elts > 0 && q2->elts > 0) {
                if(a->prev == T1) {
                    a->now = q1->front;
                    a->count_t1++;
                    a->work_time = randfrom(T3_MIN, T3_MAX);
                    a->work += a->work_time;
                }
                if(a->prev == T2) {
                    a->now = q2->front;
                    a->count_t2++;
                    a->work_time = randfrom(T4_MIN, T4_MAX);
                    a->work += a->work_time;
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
