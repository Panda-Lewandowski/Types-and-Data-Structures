#include "tick.h"
//#define LOG

static float time_now = 0;
static alarm al1;
static alarm al2;
static alarm al3;
float tick_tock(queue* q1, queue* q2, automat* a) {


    if(!al1.time && !al2.time && !al3.time) {
        al1.time = randfrom(T1_MIN, T1_MAX);
        al2.time = randfrom(T2_MIN, T2_MAX);
        time_now = (al1.time < al2.time ? al1.time : al2.time);
        if(al1.time <= al2.time) {
            Enqueue(q1, randfrom(T1_MIN, T1_MAX), T1);
            a->count_t1++;
            a->now = q1->front;
            a->work_time = randfrom(T3_MIN, T3_MAX);
            al1.time = time_now + q1->front->time;
        }
        else {
            Enqueue(q2, randfrom(T2_MIN, T2_MAX), T2);
            a->count_t2++;
            a->now = q2->front;
            a->work_time = randfrom(T4_MIN, T4_MAX);
            al2.time = time_now + q2->front->time;
        }
        al3.time = time_now + a->work_time;
    }
    else {
        if(al1.time <= al2.time && al1.time <= al3.time) {
            time_now = al1.time;
#ifdef LOG
            printf("\n>>>  (_%.3f_)     Adding element in <1> queue on address: ", time_now);
#endif
            Enqueue(q1, randfrom(T1_MIN, T1_MAX), T1);
#ifdef LOG
            printf("%p\n", (void*) (q1->rear));
#endif
            al1.time += q1->rear->time;
        }
        if(al2.time <= al1.time && al2.time <= al3.time) {
            time_now = al2.time;
#ifdef LOG
            printf("\n>>>  (_%.3f_)     Adding element in <2> queue on address: ", time_now);
#endif
            Enqueue(q2, randfrom(T2_MIN, T2_MAX), T2);
#ifdef LOG
            printf("%p\n", (void*) (q2->rear));
#endif
            al2.time += q2->rear->time;
        }
        if(al3.time <= al2.time && al3.time <= al1.time) {
#ifdef LOG
            printf("\n>>>  (_%.3f_)     Refreshing machine...", time_now);
#endif
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
       "a->work time %f\n\n", a->count_t1,a->count_t2, a->prev, a->work_time);*/


    return time_now;

}



