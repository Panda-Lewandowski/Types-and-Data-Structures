#include "head.h"

int main()
{
    FILE *f;
    struct flats table[MAX_N];
    struct keys key[MAX_N];
    int n = 0, var, flag = 1, err;

    f = fopen("in.txt","r+");
    if (f == NULL)
    {
        printf("Input file 'in.txt' was not find! Please, create it in program directory.");
        return -1;
    }

    if ((err = read(f, table, key, &n)) == -1)
    {
        printf("Error reading file!");
        return -1;
    }
    else if (err == -2)
    {
        printf("Max allowded floor is 20! Min is 1!");
        return -1;
    }
    printf("Table was readed, choose what to do:\n");
    while (flag == 1)
    {
        printf("\nMenu (Press specified number):\n\t"
               "1 - Print table;\n\t"
               "2 - Add to end element;\n\t"
               "3 - Delete element;\n\t"
               "4 - Find all flats with possibility to privatize attic;\n\t"
               "5 - Sort table by price (time test);\n"
               "To quit press any other key:\n");

        if (scanf("%d", &var) != 1)
            break;

        switch (var)
        {
            case 1:
                print(table, key, n);
            break;

            case 2:
                if ((err = add_end(table, key, &n)) != 0)
                {
                    printf("Something wrong! Try again!\n");
                    if (err == -1)
                        del(table, key, &n, n);
                }
                else
                    fprint(&f, table, n);
            break;

            case 3:
                del(table, key, &n, -1);
                fprint(&f, table, n);
            break;

            case 4:
                private_attic(table, n);
            break;

            case 5:

            break;

            default:
                flag = 0;
        }
    }

    fclose(f);
    return 0;
}
