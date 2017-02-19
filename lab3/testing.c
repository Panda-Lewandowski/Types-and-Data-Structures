#include "func.h"

int main() {
    FILE *f;
    struct flat table[MAX_N];
    struct key key[MAX_N];
    int fc = 0;
    f = fopen("test.txt","r");
    fc = read(f, table, key);
    fclose(f);
    //private_attic(table);
    print(table, key);
    /*del(table, key);
    print(table, key);
    add(table, key);*/
    //shell_table(table);
    insert_key(key);
    print_key(key);
    printf("fc = %d", fc);
}
