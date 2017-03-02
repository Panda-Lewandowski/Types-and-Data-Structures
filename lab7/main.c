#include "methods.h"

int main()
{
    FILE *f;
    tree *tr = (tree*)malloc(sizeof(tree));
    init_tree(tr);
    node *temp = (node*)malloc(sizeof(node));
    Hash_row **open_hashtable;
    Hash_row **closed_hashtable;
    int err = OK, check = 0, n_open, n_closed, check_rep, check_balance = 0, choice = -1, count = 0;
    double time, time_start, time_finish;
    char keyword[20];
    f = fopen("Input.txt", "r");
    if(f == NULL)
    {
        printf("No file \"Input.txt\" found in directory.\n");
        err = ERR_NO_FILE;
    }
    else
    {
        printf("Input number of rows in the open hash-table: ");
        scanf("%d", &n_open);
        printf("Input number of rows in the closed hash-table: ");
        scanf("%d", &n_closed);
        if(n_open <= 0 || n_closed <= 0)
        {
            printf("Number of rows in the hash-table must be more than zero.\n");
            choice = 0;
            err = ERR_INPUT;
        }
        else
        {
            open_hashtable = init_hash(n_open);
            closed_hashtable = init_hash(n_closed);
            while(fscanf(f, "%s\n", temp->keyword) == 1)
            {
                fgets(temp->HELP, 1000, f);
                check_rep = add(tr, temp);
                if(!check_rep)
                {
                    add_open_hash(open_hashtable, temp, n_open);
                    err = add_closed_hash(closed_hashtable, temp, n_closed);
                    if(err == ERR_INPUT)
                    {
                        choice = 7;
                        printf("%s", "Closed hash-table too small, reform required.\n");
                        break;
                    }
                }
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
               while(choice)
               {
                   if(err == OK)
                   {
                       choice = 0;
                       printf("%s", "Select operation:\n");
                       printf("%s", "1 - Add a keyword to the file, binary tree and to the hash-tables.\n");
                       printf("%s", "2 - Remove a keyword from the binary tree and the hash-tables.\n");
                       printf("%s", "3 - Print the binary tree.\n");
                       printf("%s", "4 - Print the open hash-table.\n");
                       printf("%s", "5 - Print the closed hash-table.\n");
                       printf("%s", "6 - Balance the binary tree.\n");
                       printf("%s", "7 - Reform the hash-table by a new number of rows.\n");
                       printf("%s", "8 - Get HELP description for a C++ keyword from the binary tree.\n");
                       printf("%s", "9 - Get HELP description for a C++ keyword from the hash-tables.\n");
                       printf("%s", "10 - Do time-efficiency analysis of binary tree and hash-tables search.\n");
                       printf("%s", "0 - Exit the program\n");
                       scanf("%d", &choice);
                   }
                   switch(choice)
                   {
                       case 1:
                           f = fopen("Input.txt", "a");
                           printf("%s", "Input a new C++ keyword: ");
                           scanf("%s", temp->keyword);
                           printf("%s", "Input HELP description:\n");
                           fflush(stdin);
                           gets(temp->HELP);
                           check_rep = add(tr, temp);
                           if(!check_rep)
                           {
                               add_open_hash(open_hashtable, temp, n_open);
                               err = add_closed_hash(closed_hashtable, temp, n_closed);
                               if(err == ERR_INPUT)
                               {
                                   choice = 7;
                                   printf("%s", "Closed hash-table too small, reform required.\n");
                                   break;
                               }
                               fprintf(f, "%s\n", temp->keyword);
                               fprintf(f, "%s\n", temp->HELP);
                           }
                           fclose(f);
                           check_balance = 0;
                       break;
                       case 2:
                           printf("%s", "Input a keyword: ");
                           scanf("%s", keyword);
                           err = delete_keyword(tr, keyword);
                           if(err == ERR_DELETE)
                           {
                               printf("Non-existing keyword cannot be removed.\n");
                               err = OK;
                               continue;
                           }
                           else
                               printf("The keyword has been removed from the binary tree.\n");
                           delete_open_hash(open_hashtable, keyword, n_open);
                           printf("The keyword has been removed from the open hash-table.\n");
                           delete_closed_hash(closed_hashtable, keyword, n_closed);
                           printf("The keyword has been removed from the closed hash-table.\n");
                       break;
                       case 3:
                           printf("%s", "Current state of the binary tree:\n");
                           print_tree(tr->root, 0);
                       break;
                       case 4:
                           printf("%s", "Current state of the open hash-table:\n");
                           print_hashtable(open_hashtable, n_open);
                       break;
                       case 5:
                           printf("%s", "Current state of the closed hash-table:\n");
                           print_hashtable(closed_hashtable, n_closed);
                       break;
                       case 6:
                           get_balanced_tree(tr);
                           check_balance = 1;
                           printf("%s", "The tree is now balanced.\n");
                       break;
                       case 7:
                           init_tree(tr);
                           printf("Input number of rows in the open hash-table: ");
                           scanf("%d", &n_open);
                           printf("Input number of rows in the closed hash-table: ");
                           scanf("%d", &n_closed);
                           if(n_open <= 0 || n_closed <= 0)
                           {
                               printf("Number of rows in the hash-table must be more than zero.\n");
                               choice = 0;
                               err = ERR_INPUT;
                           }
                           else
                           {
                               open_hashtable = init_hash(n_open);
                               closed_hashtable = init_hash(n_closed);
                               f = fopen("Input.txt", "r");
                               while(fscanf(f, "%s\n", temp->keyword) == 1)
                               {
                                   fgets(temp->HELP, 1000, f);
                                   check_rep = add(tr, temp);
                                   if(!check_rep)
                                   {
                                       add_open_hash(open_hashtable, temp, n_open);
                                       err = add_closed_hash(closed_hashtable, temp, n_closed);
                                       if(err == ERR_INPUT)
                                       {
                                           choice = 7;
                                           printf("%s", "Closed hash-table too small, reform required.\n");
                                           break;
                                       }
                                   }
                                   check = 1;
                               }
                               fclose(f);
                               if(check_balance)
                                   get_balanced_tree(tr);
                           }
                       break;
                       case 8:
                           printf("%s", "Input a keyword: ");
                           scanf("%s", keyword);
                           count = 0;
                           temp = search(tr, keyword, &count, 0);
                       break;
                       case 9:
                           printf("%s", "Input a keyword: ");
                           scanf("%s", keyword);
                           printf("Open hash index of the keyword: %d\n", hash(keyword, n_open));
                           printf("Closed hash index of the keyword: %d\n", hash(keyword, n_closed));
                           count = 0;
                           open_hash_search(open_hashtable[hash(keyword, n_open)], keyword, n_open, &count, 0);
                           count = 0;
                           closed_hash_search(closed_hashtable, keyword, n_closed, &count, 0);
                       break;
                       case 10:
                           printf("%s", "Input a keyword: ");
                           scanf("%s", keyword);
                           time_start = clock();
                           for(int i = 0; i < 1000000; i++)
                           {
                               count = 0;
                               temp = search(tr, keyword, &count, 1);
                           }
                           time_finish = clock();
                           time = (time_finish - time_start)/CLOCKS_PER_SEC;
                           printf("Time of 1000000 binary tree searches: %f\n", time);
                           printf("Number of comparisons in the binary tree: %d\n", count);
                           time_start = clock();
                           for(int i = 0; i < 1000000; i++)
                           {
                               count = 0;
                               open_hash_search(open_hashtable[hash(keyword, n_open)], keyword, n_open, &count, 1);
                           }
                           time_finish = clock();
                           time = (time_finish - time_start)/CLOCKS_PER_SEC;
                           printf("Open hash index of the keyword: %d\n", hash(keyword, n_open));
                           printf("Time of 1000000 hash-table searches: %f\n", time);
                           printf("Number of comparisons in the open hash-table: %d\n", count);
                           time_start = clock();
                           for(int i = 0; i < 1000000; i++)
                           {
                               count = 0;
                               closed_hash_search(closed_hashtable, keyword, n_closed, &count, 1);
                           }
                           time_finish = clock();
                           time = (time_finish - time_start)/CLOCKS_PER_SEC;
                           printf("Closed hash index of the keyword: %d\n", hash(keyword, n_closed));
                           printf("Time of 1000000 hash-table searches: %f\n", time);
                           printf("Number of comparisons in the closed hash-table: %d\n", count);
                       break;
                       case 0:
                           return err;
                   }
               }
            }
        }
    }
}
