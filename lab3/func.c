#include "func.h"
static int n = 0; //floors

int read(FILE *f, struct flat table[], struct key key[])
{
    int rc = 0; n = 0;

    while (!feof(f)) {

        if (fscanf(f, "%s %f %d %f %d ", table[n].address, &table[n].square,
                   &table[n].rooms, &table[n].price, &table[n].floor) != 5)
            rc =  ERR_READ;
        else if (table[n].floor < 1 || table[n].floor > MAX_FL)
            rc = INVALID_FLOOR;
        else {

            switch (table[n].floor) {
                case 1:
                    if (fscanf(f, "%c\n", &table[n].ad.cell.isC) != 1)
                        rc = 0;
                break;
                case MAX_FL:
                   if (fscanf(f, "%c %f %c\n", &table[n].ad.att.isA, &table[n].ad.att.squareA,
                               &table[n].ad.att.isPrivate) != 3)
                        rc =  INCOMPLETE_DATA;
                break;
                default:
                    if (fscanf(f, "%c %f\n", &table[n].ad.balc.isB,
                               &table[n].ad.balc.squareB) != 2)
                        rc = INCOMPLETE_DATA;
            }
        }
        /*printf("%s %.3f %d %.3f %d \n", table[n].address, table[n].square,
                           table[n].rooms, table[n].price, table[n].floor);*/
        table[n].index = n + 1;
        key[n].index = n +1;
        key[n].floor = table[n].floor;

        n++;
    }
    return rc;
}


void private_attic(struct flat table[])
{
    printf("\nAll flats with possibility to privatize attic:\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| #  | Addres                       | Square     | Rooms | Price      | Floor | Add | Add square | Add private |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for (int i=0; i<n; i++)
    {
        if (table[i].ad.att.isPrivate == 'y')
        {
            printf("| %-2d | %-28s | %-10.3f | %-5d | %-10.3f | %-5d | %-3c | %-10.3f | %-11c |\n",
                   table[i].index, table[i].address, table[i].square, table[i].rooms, table[i].price,
                   table[i].floor, table[i].ad.att.isA, table[i].ad.att.squareA,
                   table[i].ad.att.isPrivate);
            printf("----------------------------------------------------------------------------------------------------------------\n");
        }
    }
    printf("\nAdd - A: Attic;\n"
           "Add square - Square of attic;\n"
           "Add private - y/n: privatize possibility.\n\n");
}


int add(struct flat *table, struct key *key)
{
    int rc = 0;
    if (n+1 > MAX_N) {
        printf("Reached maximum of elements!\n");
        rc = OVERFLOW;
    }
    else {
        printf("Input data in next order: Addres (no more then 25 symbols) Square (float) Rooms (int) "
               "Price (float) Floor (int, from 1 to %d):\n", MAX_FL);
        if (scanf("%s %f %d %f %d", table[n].address, &table[n].square, &table[n].rooms,
               &table[n].price, &table[n].floor) != 5)
            rc = ERR_READ;
        else if (table[n].floor < 1 || table[n].floor > MAX_FL)
            rc = INVALID_FLOOR;
        else {
            fflush(stdin);
            char ans;
            switch (table[n].floor)
            {
                case 1:

                    printf("Cellar? y/n\n");
                    scanf("%c", &ans);
                    if(ans == 'y') {
                        table[n].ad.cell.isC = 'C';
                    }
                break;
                case MAX_FL:
                    printf("Attic? y/n\n");
                    scanf("%c", &ans);
                    if(ans == 'y') {
                        table[n].ad.att.isA = 'A';
                        printf("Input additional data in next order: AddSquare (float) "
                           "AddPrivate (y if allowed to privatize, n if not):\n");
                        if (scanf("%f %c",&table[n].ad.att.squareA,
                               &table[n].ad.att.isPrivate) != 2)
                            rc = ERR_READ;
                    }
                break;
                default:
                    printf("Balcony? y/n\n");
                    scanf("%c", &ans);
                    if(ans == 'y') {
                        table[n].ad.balc.isB = 'B';
                        printf("Input additional data in next order: AddSquare (float):\n");
                        if (scanf("%f",&table[n].ad.balc.squareB) != 1)
                            rc = ERR_READ;
                    }
            }
            table[n].index = n + 1;
            key[n].index = n + 1;
            key[n].floor = table[n].floor;
            n++;

        }

    }
    return rc;
}



int del(struct flat *table, struct key *key)
{
    int i, rc = 0;
    if (n <= 0)
    {
        printf("Table is already empty!\n");
        rc = OVERFLOW;
    }
    else {
        printf("Input number of element which should be deleted:\n");
        while(scanf("%d", &i) != 1)
        {

            printf("Incorrect input! Try again:\n");
            fflush(stdin);
        }

        if (i > n || i <= 0)
        {
            printf("Incorrect number!\n");
            rc =  ERR_READ;
        }
        else {
            for (int j=i-1; j< n; j++)
            {
                *(table+j) = *(table+j+1);
                *(key+j) = *(key+j+1);
            }

            n--;
            i--;
            for (; i < n; i++) {
                table[i].index--;
                key[i].index--;
            }

        }
    }

    return rc;
}


void print(struct flat table[], struct key key[])
{
    printf("\nFlats table:\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| #  | Addres                       | Square     | Rooms | Price      | Floor | Add | Add square | Add private |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    for (int i=0; i<n; i++)
    {
        printf("| %-2d | %-28s | %-10.3f | %-5d | %-10.3f | %-5d | ",
               table[i].index, table[i].address, table[i].square, table[i].rooms, table[i].price,
               table[i].floor);
        switch (table[i].floor)
        {
            case 1:
                if(table[i].ad.cell.isC == 'C')
                    printf("%-3c |            |             |\n", table[i].ad.cell.isC);
                else
                    printf("    |            |             |\n");
            break;
            case MAX_FL:
                if(table[i].ad.att.isA == 'A')
                    printf("%-3c | %-10.3f | %-11c |\n", table[i].ad.att.isA, table[i].ad.att.squareA,
                        table[i].ad.att.isPrivate);
                else
                    printf("    |            |             |\n");
            break;
            default:
                if(table[i].ad.balc.isB  == 'B')
                    printf("%-3c | %-10.3f |             |\n", table[i].ad.balc.isB, table[i].ad.balc.squareB);
                else
                    printf("    |            |             |\n");
        }
        printf("----------------------------------------------------------------------------------------------------------------\n");
    }
    printf("\nAdd - B: Balcony, A: Attic, C: Cellar;\n"
           "Add square - Square of balcony or attic;\n"
           "Add private - y: Can privatize\n\n");

    printf("Keys table:\n");
    printf("-------------------------\n");
    printf("| #   | Num | Floor      |\n");
    printf("-------------------------\n");
    for (int i=0; i<n; i++)
    {
        printf("| %-3d | %-3d | %-10d |\n", i+1, key[i].index,  key[i].floor);
        printf("-------------------------\n");
    }
    printf("\nNum - number in flats table.\n");
}


void shell_key (struct key key[]) {

    int h, i, j, t, k;

    for (h = n; h /= 2;) {
        for (i = h; i < n; i++) {
            t = key[i].floor;
            k = key[i].index;
            for (j = i; j >= h && t < key[j - h].floor; j -= h) {
                key[j].index = key[j - h].index;
                key[j].floor = key[j - h].floor;
            }
            key[j].floor = t;
            key[j].index = k;

        }
    }
}


void shell_table (struct flat table[]) {

    int h, i, j;
    struct flat t;

    for (h = n; h /= 2;) {
        for (i = h; i < n; i++) {
            t = table[i];
            for (j = i; j >= h && t.floor < table[j - h].floor; j -= h) {
                table[j] = table[j - h];
                table[j] = table[j - h];
            }
            table[j] = t;

        }
    }
}

void print_table(struct flat table[])
{
    printf("\nFlats table:\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("| #  | Addres                       | Square     | Rooms | Price      | Floor | Add | Add square | Add private |\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    for (int i=0; i<n; i++)
    {
        printf("| %-2d | %-28s | %-10.3f | %-5d | %-10.3f | %-5d | ",
               i+1, table[i].address, table[i].square, table[i].rooms, table[i].price,
               table[i].floor);
        switch (table[i].floor)
        {
            case 1:
                if(table[i].ad.cell.isC == 'C')
                    printf("%-3c |            |             |\n", table[i].ad.cell.isC);
                else
                    printf("    |            |             |\n");
            break;
            case MAX_FL:
                if(table[i].ad.att.isA == 'A')
                    printf("%-3c | %-10.3f | %-11c |\n", table[i].ad.att.isA, table[i].ad.att.squareA,
                        table[i].ad.att.isPrivate);
                else
                    printf("    |            |             |\n");
            break;
            default:
                if(table[i].ad.balc.isB  == 'B')
                    printf("%-3c | %-10.3f |             |\n", table[i].ad.balc.isB, table[i].ad.balc.squareB);
                else
                    printf("    |            |             |\n");
        }
        printf("----------------------------------------------------------------------------------------------------------------\n");
    }
    printf("\nAdd - B: Balcony, A: Attic, C: Cellar, N: Nothing;\n"
           "Add square - Square of balcony or attic;\n"
           "Add private - y: Can privatize\n\n");
}

void print_key(struct key key[])
{
    printf("Keys table:\n");
    printf("-------------------------\n");
    printf("| #   | Num | Floor      |\n");
    printf("-------------------------\n");
    for (int i=0; i<n; i++)
    {
        printf("| %-3d | %-3d | %-10d |\n", i+1, key[i].index,  key[i].floor);
        printf("-------------------------\n");
    }
    printf("\nNum - number in flats table.\n");
}






void insert_key(struct key key[]) {
    for(size_t i = 1; i < n; ++i) {
        struct key tmp = key[i];
        size_t j = i;
        while(j > 0 && tmp.floor < key[j - 1].floor) {
            key[j] = key[j - 1];
            --j;
        }
        key[j] = tmp;
    }
}

void insert_table(struct flat table[]) {
    for(size_t i = 1; i < n; ++i) {
        struct flat tmp = table[i];
        size_t j = i;
        while(j > 0 && tmp.floor < table[j - 1].floor) {
            table[j] = table[j - 1];
            --j;
        }
        table[j] = tmp;
    }
}



/*void bubble_sort (int *a, int n) {
    int i, t, s = 1;
    while (s) {
        s = 0;
        for (i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
    }
}*/

