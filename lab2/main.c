#include "arrstack.h"
#include "liststack.h"
#include "interface.h"
#include "analisis.h"
#include <stdlib.h>

#include <stdio.h>
int main()
{
    int ch = 0, fc;
    float num;
    struct stack StLst;
    StLst.pos_l = -1;
    StLst.pos_r = STACKSIZE;
    StackNode *mystack = CreateStack();

    info(STACKSIZE, STACKSIZE);

    while(1)
    {
        menu();
        fflush(stdin);
        fc = scanf("%d", &ch);

        if(fc == 0)
            ch = -1;
        printf("\n<------------RESULTS-------------->\n");
        switch (ch) {

        case 1:

            printf(""
                   "Enter float number:  ");
            fc = scanf("%f", &num);
            if(fc != 1)
                printf("INVALID INPUT!");
            else
                StLst.pos_l = push_l(num, StLst.data, StLst.pos_l, LEFT);
            break;
        case 2:
            printf(""
                   "Enter float number:  ");
            fc = scanf("%f", &num);
            if(fc != 1)
                printf("INVALID INPUT!");
            else
                StLst.pos_r = push_l(num, StLst.data, StLst.pos_r, RIGHT);
            break;
        case 3:
            StLst.pos_l = pop_l(&num, StLst.data, StLst.pos_l, LEFT);
            if(StLst.pos_l != 0)
                printf("\n The pop element is %.3f\n", num);
            break;
        case 4:
            StLst.pos_r = pop_l(&num, StLst.data, StLst.pos_r, RIGHT);
            if(StLst.pos_r != 0)
                printf("\n The pop element is %.3f\n", num);
            break;
        case 5:
            printf(""
                   "Enter number:  ");
            fc = scanf("%f", &num);
            if(fc != 1)
                printf("INVALID INPUT!");
            else
                push(&mystack, num);
            break;
        case 6:
            num = pop(&mystack);
            if(num != STACK_FAILURE)
                printf("\nThe pop element is %.3f\n", num);
            break;
        case 7:
            analise();
            break;
        case 0:
            printf("Good bye!");
            exit(0);
            break;
        default:
            printf("UNKNOWN CHOISE!\n");
            break;
        }


        num = 0;
        printf("\n---------------------\n");
        print_stack(mystack);
        printf("\n---------------------");
        printf("\n");
        ch = 0;
        printf("Double stack-array:\n");
        for(int i = 0; i < STACKSIZE; i++)
        {
            if(i <= StLst.pos_l || i >= StLst.pos_r)
                printf("%.3f  ", StLst.data[i]);
            else
                printf("|");
        }

        printf("\n<--------------------------------->\n");

    }
    return 0;
}
