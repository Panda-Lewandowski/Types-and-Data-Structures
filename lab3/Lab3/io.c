#include "head.h"

int read(FILE *f, struct flats table[], struct keys key[], int *n)
{
    while (!feof(f))
    {
        if (fscanf(f, "%s %f %d %f %d ", table[*n].addr, &table[*n].square, &table[*n].rooms,
               &table[*n].price, &table[*n].floor) != 5)
            return -1;
        if (table[*n].floor < 1 || table[*n].floor > 20)
            return -2;
        switch (table[*n].floor)
        {
            case 1:
                if (fscanf(f, "%c\n", &table[*n].u.cell.isC) != 1)
                    return -1;
            break;
            case 20:
               if (fscanf(f, "%c %f %d\n", &table[*n].u.att.isA, &table[*n].u.att.squareA,
                           &table[*n].u.att.isPrivate) != 3)
                    return -1;
            break;
            default:
                if (fscanf(f, "%c %f\n", &table[*n].u.balc.isB, &table[*n].u.balc.squareB)
                    != 2)
                    return -1;
        }

        key[*n].n_f = *n+1;
        key[*n].price = table[*n].price;

        *n += 1;
    }

    return 0;
}

void print(struct flats table[], struct keys key[], int n)
{
    printf("\nFlats table:\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| #  | Addres                       | Square     | Rooms | Price      | Floor | Add | Add square | Add private |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for (int i=0; i<n; i++)
    {
        printf("| %-2d | %-28s | %-10.3f | %-5d | %-10.3f | %-5d | ",
               i+1, table[i].addr, table[i].square, table[i].rooms, table[i].price,
               table[i].floor);
        switch (table[i].floor)
        {
            case 1:
                printf("%-3c |            |             |\n", table[i].u.cell.isC);
            break;
            case 20:
                 printf("%-3c | %-10.3f | %-11d |\n", table[i].u.att.isA, table[i].u.att.squareA,
                        table[i].u.att.isPrivate);
            break;
            default:
                printf("%-3c | %-10.3f |             |\n", table[i].u.balc.isB, table[i].u.balc.squareB);
        }
        printf("----------------------------------------------------------------------------------------------------------------\n");
    }
    printf("\nAdd - B: Balcony, A: Attic, C: Cellar, N: Nothing;\n"
           "Add square - Square of balcony or attic;\n"
           "Add private - 1: Can privatize, 0: Can't.\n\n");

    printf("Keys table:\n");
    printf("-------------------------\n");
    printf("| #   | Num | Price      |\n");
    printf("-------------------------\n");
    for (int i=0; i<n; i++)
    {
        printf("| %-3d | %-3d | %-10.3f |\n", i+1, key[i].n_f, key[i].price);
        printf("-------------------------\n");
    }
    printf("\nNum - number in flats table.\n");
}

void fprint(FILE **f, struct flats table[], int n)
{
    fclose(*f);
    *f = fopen("in.txt", "w+");
    for (int i=0; i<n; i++)
    {
        fprintf(*f, "%s %.3f %d %.3f %d ", table[i].addr, table[i].square, table[i].rooms, table[i].price,
                table[i].floor);
        switch (table[i].floor)
        {
            case 1:
                fprintf(*f, "%c\n", table[i].u.cell.isC);
            break;
            case 20:
                 fprintf(*f, "%c %.3f %d\n", table[i].u.att.isA, table[i].u.att.squareA,
                        table[i].u.att.isPrivate);
            break;
            default:
                fprintf(*f, "%c %.3f\n", table[i].u.balc.isB, table[i].u.balc.squareB);
        }
    }

}
