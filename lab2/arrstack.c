#include "arrstack.h"
static int max_l = STACKSIZE - 1;
static  int max_r = 0;

int push_l(float num, float stack[], int pos, int side)
{


    if(side == RIGHT)
    {
        if(pos <= max_r)
            printf("STACK IS FULL!");
        else
        {
            pos--;
            stack[pos] = num;
            max_l--;
        }
    }
    else if(side == LEFT)
    {

        if(pos >= max_l)
            printf("STACK IS FULL!");
        else
        {
            pos++;
            stack[pos] = num;
            max_r++;

        }
    }
    return pos;

}



int pop_l(float *num, float stack[], int pos, int side)
{


    if(side == RIGHT)
    {
        if(pos == STACKSIZE)
        {
            printf("STACK IS EMPTY!");
            return pos;
        }
        else
        {
            *num = stack[pos];
            stack[pos] = 0;
            pos++;
            max_l++;
        }

    }
    else if(side == LEFT)
    {
        if(pos == -1)
        {
            printf("STACK IS EMPTY!");
            return pos;
        }
        else
        {
            *num = stack[pos];
            stack[pos] = 0;
            pos--;
            max_r--;
        }
    }
    return pos;
}
