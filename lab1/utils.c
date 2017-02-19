#include "const.h"
#include "stdio.h"

/**
 * @brief set_array_null - обнуляет массив
 * @param A - массив
 * @param len - длина массива
 */
void set_array_null(int *A,int len)
{
    for (int i=0;i < len;i++)
    {
        A[i] = 0;
    }
}

/**
 * @brief check_simbol - проверяет принадлежит ли символ массиву dopusk
 * @param s - символ
 * @return
 */
int check_simbol(char s)
{
    char dopusk[] = "0123456789.E+-";
    int correct = 0;
    for (int i = 0;i < 14;i++)
    {
        if (dopusk[i] == s)
        {
            correct = 1;
        }
    }
    return correct;
}
/**
 * @brief count - считает количество сиволов совпадающих с с в строке сh1
 * @param c - символ
 * @param ch1 - строка
 * @return
 */
int count(char c,char *ch1)
{
    int n=0,i=0;
    while (ch1[i] != '\0')
    {
        if (c == ch1[i])
        {
            n++;
        }
        i++;
    }
    return n;
}
