#include "automat.h"
#include "queue.h"
#include "tick.h"
#define TIMES 1000
#define MOD 100
int main() {
    automat *a;
    queue_t *q1 = new_queue(ELEM, T1);
    queue_t *q2 = new_queue(ELEM, T2);
    a = init_auto();
    int len1 = 0;
    int len2 = 0;
    float stay1, stay2;
    float t;
    float i = 0;
    int j = 1;
    float ideal;
    float app;
    float measurement_error;
    double duration = 0;
    clock_t t1, t2;

    srand(time(NULL));
    printf("<--------------SETTINGS-------------->\n\n\n");
#ifdef LOG
    printf("<----LOG---------LOG---------LOG------>\n\n");
#endif
    printf("<-------------MODELING--------------->\n\n");
    while(a->count_t1 < TIMES) {
        t1 = clock();
        t = tick_tock(q1, q2, a);
        t2 = clock();
        duration = duration + (double) (t2 - t1)/CLOCKS_PER_SEC;
        if(a->count_t1 % MOD == 0 && i != a->count_t1) {
            i = a->count_t1;
            len1 += q1->elts;
            len2 += q2->elts;
            stay1 += q1->data_store[q1->front];
            stay2 += q2->data_store[q2->front];
            printf("<--------------<SUBTOTAL>---------------->\n");
            printf("_%.3f_\n\n", t);
            j++;
            printf(">>Now lenght of first queue: %d.\n"
                                      ">>Now lenght of second queue: %d.\n", q1->elts, q2->elts);
            printf(">>Time now is %f.\n",t);
            printf(">>The average length of the first queue is  %d.\n", len1 /j);
            printf(">>The average length of the second queue is  %d.\n", len2 /j);
            //printf(">>The average downtime of the first queue is  %f.\n", stay1 /j);
            //printf(">>The average downtime of the second queue is  %f.\n", stay2 /j);
            printf("------------------------------\n");

        }
    }
    app = (T1_MAX + T2_MAX + T1_MIN)/3.0;


    printf("\n\n<----------------TESTING------------------->\n\n"
           "Modeling time : %f;\n"
           "The downtime : %f;\n"
           "The number of entered applications in first queue : %d;\n"
           "The number of entered applications in second queue : %d;\n"
           "The number of left applications of first queue: %d;\n"
           "The number of left applications of second queue: %d;\n"
           "The muchine work time is %f;\n"
           "The average time of entering of a single application : %.3f.\n"
           "Estimated work time on the input: %.3f;\n\n\n", t, a->downtime, q1->ever_elts,  q2->ever_elts,
           a->count_t1,a->count_t2, a->work,
           app,app*TIMES);
    printf("Compare practical results with theoretical calculations...\n\n\n"
           "Check of correctness of the system work on the input...\n\n");
    ideal = t / app;
    measurement_error = ((q1->ever_elts + q2->ever_elts - ideal)/ ideal)/ 100 ;
    printf("Measurement error : %f %%.\n\n", measurement_error);
    printf("\n It takes time: %g\n", duration);
    printf("Used memory: %d \n", sizeof(queue_t)*2 + sizeof(automat) + ELEM*2*sizeof(float));



    queue_free(q1);
    queue_free(q2);
    return 0;

}
