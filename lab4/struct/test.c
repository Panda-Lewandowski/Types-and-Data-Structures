#include "automat.h"
#include "queue.h"
#include "tick.h"

int main() {
    automat *a;
    queue *myq = CreateQueue();
    queue *myqu = CreateQueue();
    a = init_auto();

    srand(time(NULL));

    /*Enqueue(myq, randfrom(T1_MIN, T1_MAX), T1);
    Dequeue(myq);
    printf("%d ", myq->elts);
    Enqueue(myq, randfrom(T1_MIN, T1_MAX), T1);
    printf("%d ", myq->elts);
    t = Dequeue(myq);
    printf("%d ", t);
    PrintQueue(myq);
    printf("\n");*/




    /*for(int i = 0; i < 100; i++) {printf("elmt %d %d \n", myq->elts, myqu->elts);
        tick_tock(myq, myqu, a);
        printf("STATISTIC:\n"
           "Automat:\n"
           "count q1 : %d\n"
           "count q2 : %d\n"
           "a->prev : %d\n"
           "a->work time %f\n\n", a->count_t1,a->count_t2, a->prev, a->work_time);
        printf("elmt %d %d \n", myq->elts, myqu->elts);
        PrintQueue(myq);
        printf("\n");
        PrintQueue(myqu);
        printf("\n------------------------------------\n\n");
    }*/

    while(myq->elts < 1000) {
        tick_tock(myq, myqu, a);
    }

    return 0;
}
