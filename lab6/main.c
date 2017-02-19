#include "methods.h"

int main()
{
    setlocale(LC_ALL, "Russian");  /// Для распознавания кириллицы
    FILE *f;
    tree *tr = (tree*)malloc(sizeof(tree));
    init_tree(tr);
    node *temp;
    int err = OK, check = 0, choice, file_reps = 0, question = 0;
    double time_tree, time_file, time_start, time_finish;
    char word[50], current_word[50];
    f = fopen("Input.txt", "r");
    if(f == NULL)
    {
        printf("No file \"Input.txt\" found in directory.\n");
        err = ERR_NO_FILE;
    }
    else
    {
        while(fscanf(f, "%s", word) == 1)
        {
            add(tr, word);
            strcpy(word, "");
            check = 1;
        }
        fclose(f);
        if(!check)
        {
            printf("File is empty.\n");
            err = ERR_FILE_EMPTY;
        }
        else
        {
            while(1)
            {
                printf("\n\nCurrent state of tree:\n");
                print_tree(tr->root, 0);
                printf("Choose option:\n");
                printf("0 - Exit program\n");
                printf("1 - Add the word to tree and write it to the file\n");
                printf("2 - Remove the word\n");
                printf("3 - Find the word in the tree and in the file and compare time spent\n");
                printf("4 - Go-round the tree\n");
                printf("5 - General test\n");
                scanf("%d", &choice);
                switch(choice)
                {
                    case 0:
                         return err;
                    break;
                    case 1:
                        printf("Input word: ");
                        scanf("%s", word);
                        add(tr, word);
                        printf("The word has been added to the tree\n");
                        f = fopen("Input.txt", "a");
                        fprintf(f, "%s\n", word);
                        printf("The word has been written to the file \"Input.txt\"\n");
                        strcpy(word, "");
                        fclose(f);
                    break;
                    case 2:
                        printf("Input word: ");
                        scanf("%s", word);
                        err = delete_word(tr, word);
                        strcpy(word, "");
                        if(err == ERR_DELETE)
                        {
                            printf("The word for removal was not found in the tree.\n");
                            err = OK;
                        }
                        else
                            printf("The word  has been removed from the tree\n");
                    break;
                    case 3:
                        printf("Input word: ");
                        scanf("%s", word);
                        printf(">>Searching in the tree\n");
                        int n;
                        time_start = clock();
                        for(int i = 0; i < 10; i++)
                            temp = search(tr, word, &n);
                        time_finish = clock();
                        time_tree = (time_finish - time_start)*1000/CLOCKS_PER_SEC;
                        if(temp == NULL)
                            printf("The word has not been found in the tree.\n___________________\n");
                        else
                        {
                            printf("The word has been found in the tree\n");
                            printf("It has %d repetitions in the text file\n", temp->reps);
                            printf("Search time in the tree (ms): %f\n", time_tree);
                            printf("Finding needs %d comparison\n___________________\n", n);


                        }
                        printf(">>Searching in the text file\n");
                        for(int i = 0; i < 10; i++)
                        {
                            check = 0;
                            f = fopen("Input.txt", "r");
                            time_start = clock();
                            n = 0;
                            while(fscanf(f, "%s", current_word) == 1)
                            {
                                //printf("%d\n", n);
                                if(strcmp(current_word, word) == 0)
                                {
                                    check = 1;
                                    file_reps += 1;
                                }
                                n++;
                            }
                            time_finish = clock();
                            time_file += (time_finish - time_start);
                            fclose(f);
                        }
                        time_file *= 1000/CLOCKS_PER_SEC;
                        if(check == 0)
                            printf("The word has not been found in the text file.\n");
                        else
                        {
                            printf("The word has been found in the text file\n");
                            printf("It has %d repetitions in the text file\n", file_reps/10);
                            printf("Search time in the text file (ms): %f\n", time_file);
                            printf("Finding needs %d comparison\n___________________\n", n);

                        }


                        if(check == 0 && temp == NULL)
                        {
                            printf("Add the word to tree and write it to the file? (1 - Yes / 2 - No)\n");
                            scanf("%d", &question);
                            if(question == 1)
                            {
                                add(tr, word);
                                printf("The word has been added to the tree\n");
                                f = fopen("Input.txt", "a");
                                fprintf(f, "%s\n", word);
                                printf("The word has been written to the file \"Input.txt\"\n");
                                fclose(f);
                            }
                        }
                    break;
                    case 4:
                    printf("1 - inOrder\n");
                    printf("2 - preOrder\n");
                    printf("3 - postOrder\n");
                    printf("Select:\n");
                    scanf("%d", &choice);
                    switch(choice)
                    {
                    case 1:
                    {
                        inOrder(tr->root);
                        break;
                    }
                    case 2:
                    {
                        ///printf("kak\n\n\n");
                        preOrder(tr->root);
                        break;
                    }
                    case 3:
                    {
                        postOrder(tr->root);
                        break;
                    }
                    }
                    break;
                    case 5:
                    {
                        FILE* k;
                        FILE* g;
                        int n, count=0;
                        char c_word[50];
                        tree *t = (tree*)malloc(sizeof(tree));
                        init_tree(t);
                        k = fopen("time-test.txt", "r");
                        g = fopen("time-test-input.txt", "r");
                        while(fscanf(g, "%s", c_word) == 1)
                        {
                            add(t, c_word);
                            strcpy(c_word, "");
                        }
                        fclose(g);
                        //print_tree(t->root, 0);
                        while(fscanf(k, "%s", c_word) == 1)
                        {
                            n = 0;
                            count++;
                            time_start = clock();
                            for(int i = 0; i < 100; i++)
                                temp = search(t, c_word, &n);
                            //printf("%d\n", count);
                            time_finish = clock();
                            time_tree += (time_finish - time_start)*10/CLOCKS_PER_SEC;
                            //printf("%f\n", time_tree);
                        }
                        fclose(k);
                        time_tree /= count;
                        printf("_____________\nAverage time to find word in the tree: %f\n", time_tree);
                        printf("Tree takes %d bytes\n", sizeof(t)+sizeof(node)*count);
                        printf("File takes 1 716 140 bytes");

                    }
                    break;
                }
            }
        }
    }
    getch();
    return err;
}
