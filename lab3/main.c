#include "func.h"
#define SHELL
//#define INSERT
int main()
{
    FILE *f, *g;
    double duration1 = 0, duration2 = 0;
    clock_t t1, t2;
    struct flat table[MAX_N];
    struct key key[MAX_N];
    struct flat table_t[MAX_N];
    struct key key_t[MAX_N];
    int var, flag = 1, rc, fc;
    f = fopen("in.txt","r");
    if (f == NULL) {
        printf("Input file 'in.txt' was not find! Please, create it in program directory.");
        rc =  ERR_READ;
    }
    else {
        if ((fc = read(f, table, key)) == ERR_READ) {
            printf("Error reading file!");
            print(table, key);
            rc = ERR_READ;
        }
        else if (fc == INVALID_FLOOR){
            printf("Max allowded floor is %d! Min is 1!", MAX_FL);
            rc = INVALID_FLOOR;
        }
        else if (fc == INCOMPLETE_DATA) {
            printf("Incomplete data in adding area!Please, put it down!\n");
            rc = INCOMPLETE_DATA;
        }
        else {
            printf("Table need %d bytes. Key need %d bytes.\n\n", sizeof(table), sizeof(key));
            printf("Table was read, choose what to do:\n");
            while (flag == 1) {
                printf("\nMenu (Press specified number):\n\t"
                       "1 - Print table;\n\t"
                       "2 - Add to end element;\n\t"
                       "3 - Delete element;\n\t"
                       "4 - Find all flats with possibility to privatize attic;\n\t"
                       "5 - Sort table by floor;\n\t"
                       "6 - Sort keys table by floor;\n\t"
                       "7 - Time analysis;\n\t"
                       "To quit press any other key:\n");

                if (scanf("%d", &var) != 1) {
                    printf("INVALID INPUT!");
                    fflush(stdin);
                    continue;
                }
                else {
                    switch (var)
                    {
                        case 1:
                            print(table, key);
                        break;

                        case 2:
                            if ((fc = add(table, key)) != 0)
                            {
                                printf("Something wrong! Try again!\n");
                            }
                            else
                                print(table, key);
                        break;

                        case 3:
                            del(table, key);
                            print(table, key);
                        break;

                        case 4:
                            private_attic(table);
                        break;

                        case 5:
                        g = fopen("in.txt", "r");

#ifdef SHELL
                            for(int i = 0; i < 10000; i++) {
                                read(g, table_t, key_t);
                                t1 = clock();
                                shell_table(table_t);
                                t2 = clock();
                                rewind(g);
                                duration1 = duration1 + (double) (t2 - t1)/CLOCKS_PER_SEC;

                            }
#else
#ifdef INSERT
                            for(int i = 0; i < 10000; i++) {
                                read(g, table_t, key_t);
                                t1 = clock();
                                insert_table(table_t);
                                t2 = clock();
                                rewind(g);

                                duration1 = duration1 + (double) (t2 - t1)/CLOCKS_PER_SEC;
                            }

#endif
#endif

                            //printf("Sorting table:\n");
                            //print_table(table);
                        break;

                        case 6:
                        if(!g)
                            g = fopen("in.txt", "r");

#ifdef SHELL
                            for(int i = 0; i < 10000; i++) {
                                read(g, table_t, key_t);
                                t1 = clock();
                                shell_key(key_t);
                                t2 = clock();
                                rewind(g);
                                duration2 = duration2 + (double) (t2 - t1)/CLOCKS_PER_SEC;
                            }
#else
#ifdef INSERT

                            for(int i = 0; i < 10000; i++) {
                                read(g, table_t, key_t);
                                t1 = clock();
                                insert_key(key_t);//printf("d = %d\n", (int) t1);
                                t2 = clock();
                                rewind(g);

                                duration2 = duration2 + (double) (t2 - t1)/CLOCKS_PER_SEC;
                            }
#endif
#endif


                            //printf("Sorting key table:\n");
                            //print_key(key);
                        break;
                        case 7:
#ifdef SHELL
                            if( duration1 == 0 || duration2 == 0 )
                                printf("The both tables or one of the tables  are unsorted.\n");
                            else {
                                printf("Sort table tooks in shell sort %g sec.\n", duration1);
                                printf("Sort key table tooks in shell sort %g sec.\n", duration2);
                            }
#else
#ifdef INSERT
                        if(duration1 == 0 || duration2 == 0)
                            printf("The both tables or one of the tables  are unsorted.\n");
                        else {
                            printf("Sort table tooks in insertion sort %g sec.\n", duration1);
                            printf("Sort key table tooks in insertion sort %g sec.\n", duration2);
                        }
#endif
#endif

                        break;

                        default:
                            flag = 0;
                    }
                }

           }

        }

    }
    fclose(f);
    fclose(g);
    return rc;


}
