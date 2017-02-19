#include "head.h"

void private_attic(struct flats table[], int n)
{
    printf("\nAll flats with possibility to privatize attic:\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| #  | Addres                       | Square     | Rooms | Price      | Floor | Add | Add square | Add private |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for (int i=0; i<n; i++)
    {
        if (table[i].u.att.isPrivate == 1)
        {
            printf("| %-2d | %-28s | %-10.3f | %-5d | %-10.3f | %-5d | %-3c | %-10.3f | %-11d |\n",
                   i+1, table[i].addr, table[i].square, table[i].rooms, table[i].price,
                   table[i].floor, table[i].u.att.isA, table[i].u.att.squareA,
                   table[i].u.att.isPrivate);
            printf("----------------------------------------------------------------------------------------------------------------\n");
        }
    }
    printf("\nAdd - A: Attic;\n"
           "Add square - Square of attic;\n"
           "Add private - 1: Can privatize.\n\n");
}

int add_end(struct flats *table, struct keys *key, int *n)
{

    if (*n+1 > MAX_N)
    {
        printf("Reached maximum of elements!\n");
        return -1;
    }

    printf("Input data in next order: Addres (no more then 25 symbols) Square (float) Rooms (int) "
           "Price (float) Floor (int, from 1 to 20):\n");
    if (scanf("%s %f %d %f %d", table[*n].addr, &table[*n].square, &table[*n].rooms,
           &table[*n].price, &table[*n].floor) != 5)
        return -2;
    if (table[*n].floor < 1 || table[*n].floor > 20)
        return -1;
    fflush(stdin);
    switch (table[*n].floor)
    {
        case 1:
            printf("Input additional data in next order: Add (C if cellar exist, N if not):\n");
            if (scanf("%c", &table[*n].u.cell.isC) != 1)
                return -1;
        break;
        case 20:
            printf("Input additional data in next order: Add (A if attic exist, N if not) AddSquare (float) "
                   "AddPrivate (1 if allowed to privatize, 0 if not):\n");
            if (scanf("%c %f %d", &table[*n].u.att.isA, &table[*n].u.att.squareA,
                       &table[*n].u.att.isPrivate) != 3)
                return -1;
        break;
        default:
            printf("Input additional data in next order: Add (B if balcony exist, N if not) AddSquare (float):\n");
            if (scanf("%c %f", &table[*n].u.balc.isB, &table[*n].u.balc.squareB) != 2)
                return -1;
    }

    key[*n].n_f = *n+1;
    key[*n].price = table[*n].price;

    *n += 1;

    return 0;
}

int del(struct flats *table, struct keys *key, int *n, int i)
{
    if (i == -1)
    {
        printf("Input number of element which should be deleted:\n");
        while(scanf("%d", &i) != 1)
        {
            printf("Incorrect input! Try again:\n");
            fflush(stdin);
        }
    }

    if (i > *n || i <= 0)
    {
        printf("Incorrect number!\n");
        return -1;
    }
    if (*n <= 0)
    {
        printf("Table is already empty!\n");
        return -1;
    }

    for (int j=i-1; j<*n; j++)
    {
        *(table+j) = *(table+j+1);
        *(key+j) = *(key+j+1);
    }
    *n -= 1;

    return 0;
}
