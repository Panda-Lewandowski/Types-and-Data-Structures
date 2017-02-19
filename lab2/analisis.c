#include "arrstack.h"
#include "liststack.h"
#include "analisis.h"

void analise()
{


    double duration1 = -1.0, duration2 = -1.0;
    clock_t t1, t2;
    struct stack stack_arr;
    stack_arr.pos_l = -1;
    stack_arr.pos_r = STACKSIZE;
    StackNode *stack_list = CreateStack();
    float num;

    t1 = clock();
    for(int i = 0; i < STACKSIZE; i++) {
        stack_arr.pos_l = push_l(NUM, stack_arr.data, stack_arr.pos_l, LEFT);
    }
    t2 = clock();
    duration1 = (double) (t2-t1)/CLOCKS_PER_SEC/10000;

    t1 = clock();
    for(int i = 0; i < STACKSIZE; i++)  {
        push(&stack_list, NUM);
    }
    t2 = clock();
    duration2 = (double) (t2-t1)/CLOCKS_PER_SEC/10000;

    printf("The 'push' - operation took %g ms in stack-array "
           "and %g ms in stack-list.\n", duration1, duration2);

    duration1 = 0;
    duration2 = 0;
    t1 = clock();
    for(int i = 0; i < STACKSIZE; i++) {
        stack_arr.pos_l = pop_l(&num, stack_arr.data, stack_arr.pos_l, LEFT);
    }
    t2 = clock();
    duration1 = (double) (t2-t1)/CLOCKS_PER_SEC/10000;

    t1 = clock();
    for(int i = 0; i < STACKSIZE; i++)  {
        pop(&stack_list);
    }
    t2 = clock();
    duration2 = (double) (t2-t1)/CLOCKS_PER_SEC/10000;

    printf("The 'pop' - operation took %g ms in stack-array "
           "and %g ms in stack-list.\n", duration1, duration2);
}
