#include "head.h"

int matrInput(int n, int m, float *Matr, float *A, int *JA, struct IA *IA, int *lenA)
{
    int i, j, t;
    float t1;
    struct IA *tmp, *tmp1, *tmp2;

    do
    {
        printf("\nInput i and j of matrix element:\n");
        while (1)
        {
            if (scanf("%d %d", &i, &j) != 2)
            {
                printf("Error! Try again!\n");
                fflush(stdin);
            }
            else if (i < 0 || i >= n || j < 0 || j > m)
                printf("Index out of range! Try again!\n");
            else break;
        }

        printf("Input element:\n");
        while (scanf("%f", &t1) != 1)
        {
            printf("It isnt number! Try again!\n");
            fflush(stdin);
        }
        Matr[i*m+j] = t1;

        t1 = Matr[i*m+j];
        tmp = IA;
        while (tmp != NULL)
        {
            if (tmp->i != i)
            {
                tmp1 = tmp;
                tmp = tmp->next;
            }
            else
            {
                if (JA[tmp->Nk] > j)
                {
                   for (int k=*lenA; k>tmp->Nk; k--)
                   {
                       A[k] = A[k-1];
                       JA[k] = JA[k-1];
                       tmp2 = IA;
                       while (tmp2 != NULL)
                       {
                           if (tmp2->Nk != k-1 || tmp->Nk == k-1)
                               tmp2 = tmp2->next;
                           else
                           {
                               tmp2->Nk += 1;
                               break;
                           }
                       }
                   }
                   A[tmp->Nk] = t1;
                   JA[tmp->Nk] = j;
                }
                else
                {
                    for (int k=*lenA; k>tmp->Nk+1; k--)
                    {
                        A[k] = A[k-1];
                        JA[k] = JA[k-1];
                        tmp2 = IA;
                        while (tmp2 != NULL)
                        {
                            if (tmp2->Nk != k-1)
                                tmp2 = tmp2->next;
                            else
                            {
                                tmp2->Nk += 1;
                                break;
                            }
                        }
                    }
                    A[tmp->Nk+1] = t1;
                    JA[tmp->Nk+1] = j;
                }
                break;
            }
        }
        if (tmp == NULL)
        {
            A[*lenA] = t1;
            JA[*lenA] = j;
            tmp1 = add(tmp1, i, *lenA);
        }

        *lenA += 1;

        printf("Continue input? (any letter - no, numbers - yes):\n");
    }
    while (scanf("%d", &t) != 0);

    while (IA->next != NULL)
        IA = IA->next;
    add(IA, n, *lenA);

    return 0;
}


int create_matrix(float *matr, int n, int m, int fill, int *count)
{
    int chance;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            chance = rand() % 100;
            if (chance > fill)
                matr[i*m+j] = 0;
            else
            {
                matr[i*m+j] = rand() % 10;
                *count = *count + 1;
            }
        }
    return 0;
}

void matrDefault(float *Matr, int n, int m,float *A, int *JA, struct IA *IA, int *lenA)
{
    struct IA *tmp, *tmp1, *tmp2;
    int t1;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            if (Matr[i*m+j] != 0)
            {
                //A[k] = matr[i*m+j];
                //JA[k] = j;
                //k++;
                t1 = Matr[i*m+j];
                tmp = IA;
                while (tmp != NULL)
                {
                    if (tmp->i != i)
                    {
                        tmp1 = tmp;
                        tmp = tmp->next;
                    }
                    else
                    {
                        if (JA[tmp->Nk] > j)
                        {
                           for (int k=*lenA; k>tmp->Nk; k--)
                           {
                               A[k] = A[k-1];
                               JA[k] = JA[k-1];
                               tmp2 = IA;
                               while (tmp2 != NULL)
                               {
                                   if (tmp2->Nk != k-1 || tmp->Nk == k-1)
                                       tmp2 = tmp2->next;
                                   else
                                   {
                                       tmp2->Nk += 1;
                                       break;
                                   }
                               }
                           }
                           A[tmp->Nk] = t1;
                           JA[tmp->Nk] = j;
                        }
                        else
                        {
                            for (int k=*lenA; k>tmp->Nk+1; k--)
                            {
                                A[k] = A[k-1];
                                JA[k] = JA[k-1];
                                tmp2 = IA;
                                while (tmp2 != NULL)
                                {
                                    if (tmp2->Nk != k-1)
                                        tmp2 = tmp2->next;
                                    else
                                    {
                                        tmp2->Nk += 1;
                                        break;
                                    }
                                }
                            }
                            A[tmp->Nk+1] = t1;
                            JA[tmp->Nk+1] = j;
                        }
                        break;
                    }
                }
                if (tmp == NULL)
                {
                    A[*lenA] = t1;
                    JA[*lenA] = j;
                    tmp1 = add(tmp1, i, *lenA);
                }

                *lenA += 1;

            }
        }
    while (IA->next != NULL)
        IA = IA->next;
    add(IA, n, *lenA);
}

void print(int n, int m, float *Matr, float *A, int *JA, struct IA *IA, int lenA)
{
    struct IA *tmp = IA->next;
    if (n > 27 || m > 27)
    {

        printf("A: ");
        for (int i=0; i<lenA; i++)
           printf("%.3f ", A[i]);

        printf("\nJA: ");
        for (int i=0; i<lenA; i++)
           printf("%d ", JA[i]);

        printf("\n\ni: ");
        for (; tmp->next != NULL; tmp = tmp->next)
            printf("%d ", tmp->i);

        printf("\nIA: ");
        IA = IA->next;
        for (; IA->next != NULL; IA = IA->next)
            printf("%d ", IA->Nk);
        printf("\n");
    }
    else
    {
        printf("Matrix:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                printf("%.3f ", Matr[i*m+j]);
            printf("\n");
        }
    }
}





int printmatrix(float *matr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%.4f ", matr[i*m+j]);
        printf("\n");
    }
    return 0;
}
