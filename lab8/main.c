#include "head.h"

int main()
{
    FILE *fi, *fo, *fo1;
    int n, **Matr, *path, p_l = 0;

    fi = fopen("in.txt", "r");
    if (fi == NULL)
    {
        printf("File don't exist! Please create in.txt!\n");
        return -1;
    }

    fo = fopen("graph.dot", "w");
    if (fo == NULL)
    {
        printf("Can't create file in this directory!\n");
        fclose(fi);
        return -1;
    }

    fo1 = fopen("graph1.dot", "w");
    if (fo1 == NULL)
    {
        printf("Can't create file in this directory!\n");
        fclose(fo);
        fclose(fi);
        return -1;
    }

    if (fscanf(fi, "%d", &n) != 1)
    {
        printf("Wrong input!\n");
        return -1;
    }

    path = calloc(n, sizeof(int));

    Matr = alloc_matr_rows(n);
    if (Matr == NULL)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    if (scan(fi, Matr, n) != 0)
    {
        printf("Wrong values in file!\n");
        free_matr_rows(Matr, n);
        return -1;
    }

    print_graph(fo, Matr, n, path, p_l);
    fclose(fo);
    system("G:\\Graphviz2.38\\bin\\dot.exe -Tpng graph.dot -o OutputFile.png");
    system("OutputFile.png");

    find(Matr, n, path, &p_l);

    printf("The longest path:\n");
    for (int i = 0; i < p_l; i++)
    {
        printf("%d -> ", path[i]+1);
    }

    print_graph(fo1, Matr, n, path, p_l);
    fclose(fo1);
    system("G:\\Graphviz2.38\\bin\\dot.exe -Tpng graph1.dot -o OutputFile1.png");
    system("OutputFile1.png");

    free_matr_rows(Matr, n);
    free(path);
    fclose(fi);
    return 0;
}
