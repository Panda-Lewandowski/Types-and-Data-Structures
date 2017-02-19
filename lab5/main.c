#include "head.h"

int main()
{
    srand(time(0));
    int var, n1, m1, n2, m2, lenA1 = 0, lenA2 = 0, lenA3 = 0;
    float *Matr1, *Matr2, *Matr3, *A1, *A2, *A3;
    int *JA1, *JA2, *JA3;
    struct IA *IA1 = NULL, *IA2 = NULL, *IA3 = create(-1, -1);
    int count1 = 0, count2 = 0; // количество ненулевых элементов
    int fill = 20; // то, что заполнится 20 %
    printf("Summ of matriexes.\n");
    printf("Element have type of integer.\n");
    int c = sizeof(IA1);
    printf("Do you want to enter matrixes by yourself? (1 - yes, 0- no):\n");
    while (scanf("%d", &var) != 1)
    {
        printf("Ooops, error! Try again!\n");
        fflush(stdin);
    }
    if (var != 0)
    {
        printf("Input N and M of 1st matrix:\n");
        while (scanf("%d %d", &n1, &m1) != 2)
        {
            printf("Ooops, error! Try again!\n");
            fflush(stdin);
        }

        IA1 = create(-1, -1);

        IA2 = create(-1, -1);
        Matr1 = calloc(n1*m1, sizeof(float));
        A1 = malloc(n1*m1*sizeof(float));
        JA1 = malloc(n1*m1*sizeof(int));
        matrInput(n1, m1, Matr1, A1, JA1, IA1, &lenA1);
        print(n1,m1, Matr1, A1, JA1, IA1, lenA1);
        fflush(stdin);
        printf("Input N and M of 2st matrix:\n");
        while (scanf("%d %d", &n2, &m2) != 2)
        {
            printf("Ooops, error! Try again!\n");
            fflush(stdin);
        }
        Matr2 = calloc(n2*m2, sizeof(float));
        A2 = malloc(n2*m2*sizeof(float));
        JA2 = malloc(n2*m2*sizeof(int));

        matrInput(n2, m2, Matr2, A2, JA2, IA2, &lenA2);
        print(n2,m2, Matr2, A2, JA2, IA2, lenA2);
    }
    else
    {
        //n1 = m1 = 4;
        printf("Input N and M of 1st matrix:\n");
        while (scanf("%d %d", &n1, &m1) != 2)
        {
            printf("Ooops, error! Try again!\n");
            fflush(stdin);
        }
        fflush(stdin);
        printf("Input N and M of 2st matrix:\n");
        while (scanf("%d %d", &n2, &m2) != 2)
        {
            printf("Ooops, error! Try again!\n");
            fflush(stdin);
        }
        fflush(stdin);
        IA1 = create(-1, -1);
        Matr1 = calloc(n1*m1, sizeof(float));
        create_matrix(Matr1, n1, m1, fill, &count1);
        A1 = malloc(count1*sizeof(float));
        JA1 = malloc(count1*sizeof(int));
        matrDefault(Matr1, n1, m1,A1,JA1,IA1, &lenA1);
        print(n1,m1, Matr1, A1, JA1, IA1, lenA1);

        //n2 = m2 = 4;
        IA2 = create(-1, -1);
        Matr2 = calloc(n2*m2, sizeof(float));
        create_matrix(Matr2, n2, m2, fill, &count2);
        printf("\n");
        A2 = malloc(count2*sizeof(float));
        JA2 = malloc(count2*sizeof(int));
        matrDefault(Matr2, n2, m2,A2,JA2,IA2, &lenA2);
        print(n2,m2, Matr2, A2, JA2, IA2, lenA2);
    }
    if (n1 != n2 || m1 != m2)
        printf("\nDiffrent size of matrixes.\n");
    else
    {
    Matr3 = calloc(10*10, sizeof(float));
    printf("\n");
    //printmatrix(Matr3,n1,m1);
    // Сложение
    Matr3 = calloc(n2*m2, sizeof(float));
    A3 = malloc(n2*m2*sizeof(float));
    JA3 = malloc(n2*m2*sizeof(int));

    Plus_R(n1, m1, A1, A2, JA1, JA2, IA1, IA2, lenA1, lenA2, A3, JA3, IA3, &lenA3);
    summtrix(Matr1, Matr2, Matr3, n1, m1);
    print(n1,m1, Matr3, A3, JA3, IA3, lenA1);
    fflush(stdin);
    printf("Do you want print matriex? (1 - yes, else - no):\n");
    while (scanf("%d", &var) != 1)
    {
        printf("Ooops, error! Try again!\n");
        fflush(stdin);
    }
    if (var == 1)
    {
       printf("First matrix:\n");
       printmatrix(Matr1, n1, m1);
       printf("Secord matrix:\n");
       printmatrix(Matr2, n2, m2);
       printf("Result matrix:\n");
       printmatrix(Matr3, n1, m2);
    }
    free_all(IA1);
    free_all(IA2);
    free_all(IA3);
    free(A1);
    free(A2);
    free(A3);
    free(JA1);
    free(JA2);
    free(JA3);
    free(Matr1);
    free(Matr2);
    free(Matr3);
    printf("Do you want print to make a time test? (1 - yes, else - no):\n");
    while (scanf("%d", &var) != 1)
    {
        printf("Ooops, error! Try again!\n");
        fflush(stdin);
    }
    if (var == 1)
    {
        time_test(5);
        time_test(15);
        time_test(25);
        time_test(40);
        //time_test(90);
    }

}


}
