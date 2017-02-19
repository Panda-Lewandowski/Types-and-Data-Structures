#include "head.h"
#include <string.h>



unsigned long long tick(void)
{
    unsigned long long tmp;
    __asm__ __volatile__ ("rdtsc" : "=A" (tmp) );
    return tmp;
}


int Plus_R(int n, int m, float *A1, float *A2, int *JA1, int *JA2, struct IA *IA1, struct IA *IA2, int lenA1, int lenA2,
           float *A3, int *JA3, struct IA *IA3, int *lenA3)
{
    float *T = calloc(m, sizeof(float));
    struct IA *tmp1 = IA1->next, *tmp2, *tmp3 = IA3;
    int l3 = 0, al, t;
    while (tmp1->next != NULL)
        {
            tmp2 = IA2->next;
            while (tmp2->next != NULL)
            {
                if (tmp1->i == tmp2->i)
                    break;
                tmp2 = tmp2->next;
            }

            if (tmp2->next == NULL)
            {
                tmp3 = add(tmp3, tmp1->i, l3);
                al = abs(tmp1->next->Nk - tmp1->Nk);
                for (int k=0; k<al; k++)
                {
                    A3[k+l3] = A1[tmp1->Nk+k];
                    JA3[k+l3] = JA1[tmp1->Nk+k];
                }
                l3 += al;
            }
            else
            {
               // if (IA1[tmp1->Nk] < IA2[tmp2->Nk])
                    tmp3 = add(tmp3, tmp1->i, l3);
               // else
                   // tmp3 = add(tmp3, tmp2->j, tmp2->Nk);
                al = abs(tmp1->next->Nk - tmp1->Nk);
                for (int k=0; k<al; k++)
                    T[JA1[tmp1->Nk+k]] += A1[tmp1->Nk+k];
                t = JA1[tmp1->Nk+al-1];
                al = abs(tmp2->next->Nk - tmp2->Nk);
                for (int k=0; k<al; k++)
                    T[JA2[tmp2->Nk+k]] += A2[tmp2->Nk+k];
                if (t < JA2[tmp2->Nk+al-1])
                    t = JA2[tmp2->Nk+al-1];
                for (int k=0; k<=t; k++)
                    if (T[k] != 0)
                    {
                        A3[l3] = T[k];
                        JA3[l3] = k;
                        l3++;
                    }
                memset(T, 0, m*sizeof(T));
            }

            tmp1 = tmp1->next;
        }

        tmp2 = IA2->next;
        while (tmp2->next != NULL)
        {
            tmp1 = IA1->next;
            while (tmp1->next != NULL)
            {
                if (tmp1->i == tmp2->i)
                    break;
                tmp1 = tmp1->next;
            }

            if (tmp1->next == NULL)
            {
                tmp3 = add(tmp3, tmp2->i, l3);
                al = abs(tmp2->next->Nk - tmp2->Nk);
                for (int k=0; k<al; k++)
                {
                    A3[k+l3] = A2[tmp2->Nk+k];
                    JA3[k+l3] = JA2[tmp2->Nk+k];
                }
                l3 += al;
            }

            tmp2 = tmp2->next;
        }

    *lenA3 = l3;
    add(tmp3, n, l3);
    return 0;
}

/*
int matrTolist(float *matr, int n, int m, struct IA *IA)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            if (matr[i*n+j] != 0)
            {
                if (IA == NULL)
                {
                    IA = create(i, matr[i*n+j]);
                }
                else
                {
                    IA = add(IA, i, matr[i*n+j]);
                }
            }
        }
}
*/
int summtrix(float *matr1, float *matr2, float *matr3,int n,int m)
{
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            matr3[i*m+j] = matr1[i*m+j] + matr2[i*m+j];
    return 0;
}



int time_test(int fill)
{
    srand(time(0));
    int n1, m1, n2, m2, lenA1 = 0, lenA2 = 0, lenA3 = 0;
    float *Matr1, *Matr2, *Matr3, *A1, *A2, *A3;
    int *JA1, *JA2, *JA3;
    struct IA *IA1 = NULL, *IA2 = NULL, *IA3 = create(-1, -1);
    int count1 = 0, count2 = 0; // количество ненулевых элементов
    //int fill = 2; // то, что заполнится 5 %
    unsigned long long time_beg, time_end;
    unsigned long long time_beg2, time_end2;
    // Сложение методом единичек
    n1 = m1 = 1000;
    IA1 = create(-1, -1);
    Matr1 = calloc(n1*m1, sizeof(float));
    create_matrix(Matr1, n1, m1, fill, &count1);
    A1 = malloc(n1*m1*sizeof(float));
    JA1 = malloc(n1*m1*sizeof(int));
    matrDefault(Matr1, n1, m1,A1,JA1,IA1, &lenA1);
    //print(n1,m1, Matr1, A1, JA1, IA1, lenA1);
    printf("Time test for summing arrays of 10000 elements with fill of %d procents", fill);
    n2 = m2 = 1000;
    IA2 = create(-1, -1);
    Matr2 = calloc(n2*m2, sizeof(float));
    create_matrix(Matr2, n2, m2, fill, &count2);
    printf("\n");
    A2 = malloc(n2*m2*sizeof(float));
    JA2 = malloc(n2*m2*sizeof(int));
    matrDefault(Matr2, n2, m2,A2,JA2,IA2, &lenA2);
    //print(n2,m2, Matr2, A2, JA2, IA2, lenA2);
    //Matr3 = calloc(, sizeof(float));
    // Сложение
    Matr3 = calloc(n2*m2, sizeof(float));
    A3 = malloc(n2*m2*sizeof(float));
    JA3 = malloc(n2*m2*sizeof(int));

    time_beg = tick();
    Plus_R(n1, m1, A1, A2, JA1, JA2, IA1, IA2, lenA1, lenA2, A3, JA3, IA3, &lenA3);
    time_end = tick();
    printf("Time taken  %lu milliseconds for method \n", time_end - time_beg);
    time_beg2 = tick();
    summtrix(Matr1, Matr2, Matr3, n1, m1);;
    time_end2 = tick();
    printf("Time taken  %lu milliseconds for simple metod\n", time_end2 - time_beg2);
    return 0;
    //print(n1,m1, Matr3, A3, JA3, IA3, lenA1);
}
/*
int time_test2(int fill)
{
    srand(time(0));
    int var, n1, m1, n2, m2, lenA1 = 0, lenA2 = 0, lenA3 = 0;
    float *Matr1, *Matr2, *Matr3, *A1, *A2, *A3;
    int *JA1, *JA2, *JA3;
    struct IA *IA1 = NULL, *IA2 = NULL, *IA3 = create(-1, -1);
    int count1 = 0, count2 = 0; // количество ненулевых элементов
   // то, что заполнится 5 %
    clock_t time_beg, time_end;
    // Сложение методом единичек
    n1 = m1 = 500;
    IA1 = create(-1, -1);
    Matr1 = calloc(n1*m1, sizeof(float));
    create_matrix(Matr1, n1, m1, fill, &count1);
    A1 = malloc(n1*m1*sizeof(float));
    JA1 = malloc(n1*m1*sizeof(int));
    matrDefault(Matr1, n1, m1,A1,JA1,IA1, &lenA1);
    //print(n1,m1, Matr1, A1, JA1, IA1, lenA1);

    n2 = m2 = 500;
    IA2 = create(-1, -1);
    Matr2 = calloc(n2*m2, sizeof(float));
    create_matrix(Matr2, n2, m2, fill, &count2);
    printf("\n");
    A2 = malloc(n2*m2*sizeof(float));
    JA2 = malloc(n2*m2*sizeof(int));
    matrDefault(Matr2, n2, m2,A2,JA2,IA2, &lenA2);
    //print(n2,m2, Matr2, A2, JA2, IA2, lenA2);
    Matr3 = calloc(10*10, sizeof(float));
    // Сложение
    Matr3 = calloc(n2*m2, sizeof(float));
    A3 = malloc(n2*m2*sizeof(float));
    JA3 = malloc(n2*m2*sizeof(int));
    //time_beg = clock();
    Plus_R(n1, m1, A1, A2, JA1, JA2, IA1, IA2, lenA1, lenA2, A3, JA3, IA3, &lenA3);
    //time_end = clock() - time_beg;
    printf("Time taken %d seconds %d milliseconds", (time_end * 1000 / CLOCKS_PER_SEC)/1000, (time_end * 1000 / CLOCKS_PER_SEC)%1000);
    //print(n1,m1, Matr3, A3, JA3, IA3, lenA1);
}*/


// Функция выделения памяти под элемент и его создания
struct IA* create(int i, int num)
{
    struct IA *node = malloc(sizeof(struct IA));
    if (node)
    {
        node->Nk = num;
        node->i = i;
        node->next = NULL;
    }

    return node;
}

// Функция добавления элемента в стек
struct IA* add(struct IA *node, int i, int num)
{
    struct IA *curr;
    curr = create(i, num);
    if (curr == NULL)
        return NULL;
    node->next = curr;

    return curr;
}

// Освобождение всех эл-тов стека
void free_all(struct IA *head)
{
    struct IA *nxt;

    for (; head; head = nxt)
    {
        nxt = head->next;
        free(head);
    }
}
