#include "methods.h"
//инициализация хеш-таблицы
Hash_row **init_hash(int n)
{
    Hash_row **hashtable = (Hash_row**)malloc(n*sizeof(Hash_row*));
    for(int i = 0; i < n; i++)
        hashtable[i] = NULL;
    return hashtable;
}
//хеш-функция(суммирует коды всех символов и делит на размер таблицы
int hash(char *keyword, int n)
{
    int hashidx = 0, i = 0;
    while(keyword[i] != '\0')
    {
        hashidx += keyword[i];
        i++;
    }
    hashidx %= n;
    return hashidx;
}
//добавление значение в хэш-таблицу методом цепочек
void add_open_hash(Hash_row **hashtable, node *temp, int n)
{
    Hash_row *buff = (Hash_row*)malloc(sizeof(Hash_row));
    strcpy(buff->keyword, temp->keyword);
    strcpy(buff->HELP, temp->HELP);
    int hashidx = hash(temp->keyword, n);//нахождение ключа
    if(hashtable[hashidx] == NULL)//если нужная ячейка пуста
    {
        buff->next = NULL;
        hashtable[hashidx] = buff; //присоединяем значение
    }
    else //иначе
    {
        buff->next = hashtable[hashidx]; //присоединяем в начало списка значений
        hashtable[hashidx] = buff;
    }
}
//добавление значения в хэш-таблицу методом открытой адресации
int add_closed_hash(Hash_row **hashtable, node *temp, int n)
{
    Hash_row *buff = (Hash_row*)malloc(sizeof(Hash_row));
    strcpy(buff->keyword, temp->keyword);
    strcpy(buff->HELP, temp->HELP);
    buff->next = NULL;
    int hashidx = hash(temp->keyword, n), l_idx, r_idx, check = 0;
    if(hashtable[hashidx] == NULL)//если ячейка пуста
    {
        hashtable[hashidx] = buff;//присоединяем значение
        check = 1;
    }
    else
    {
        l_idx = r_idx = hashidx;
        l_idx--;
        r_idx++;
        while((l_idx >= 0 && l_idx < n) || (r_idx >= 0 && r_idx < n))//ищем значение ближайшего пустого места
        {
            if(l_idx >= 0 && l_idx < n)
                if(hashtable[l_idx] == NULL)//если слева есть место ближайшее, то все ок
                {
                    hashtable[l_idx] = buff;
                    check = 1;
                    break;
                }
            if(r_idx >= 0 && r_idx < n)//--||-- справа
                if(hashtable[r_idx] == NULL)
                {
                    hashtable[r_idx] = buff;
                    check = 1;
                    break;
                }
            l_idx--;
            r_idx++;
        }
    }
    if(!check)//если не нашли, все плохо
        return ERR_INPUT;
    else
        return OK;
}
//печать хеш-таблицы
void print_hashtable(Hash_row **hashtable, int n)
{
    Hash_row *buff = (Hash_row*)malloc(sizeof(Hash_row));
    for(int i = 0; i < n; i++)
    {
        printf("%d   ", i);
        buff = hashtable[i];
        while(buff != NULL)
        {
            printf("%s   ", buff->keyword);
            buff = buff->next;
        }
        printf("%s", "\n");
    }
    free(buff);
}

//удаление значения из хеш-таблицы метода цепочек
void delete_open_hash(Hash_row **hashtable, char *keyword, int n)
{
    int hashidx = hash(keyword, n), count = 0;
    Hash_row *buff = (Hash_row*)malloc(sizeof(Hash_row));
    buff = hashtable[hashidx];
    if(buff->next == NULL)//если одно значение, то ок
    {
        if(!strcmp(buff->keyword, keyword))
                hashtable[hashidx] = NULL;
    }
    while(buff != NULL)//если нет
    {
        if(count == 0 && !strcmp(buff->keyword, keyword))//если первое в списке
        {
            hashtable[hashidx] = buff->next;
            break;
        }
        else if(!strcmp(buff->keyword, keyword))//если в середине или последнее
        {
            buff = hashtable[hashidx];
            for(int i = 0; i < count - 1; i++)
                buff = buff->next;
            if(buff->next->next == NULL)
                buff->next = NULL;
            else
                buff->next = buff->next->next;
        }
        else
        {
            count++;
            buff = buff->next;
        }
    }
}

//удаление значение из хеш-таблицы с методом открытой адресации
void delete_closed_hash(Hash_row **hashtable, char *keyword, int n)
{
    int count = 0;
    int idx = closed_hash_search(hashtable, keyword, n, &count, 1);//ищем значение
    if(idx >= 0)
        hashtable[idx] = NULL;
}
//поиск в таблице методом цепочек
void open_hash_search(Hash_row *hashtable, char *keyword, int n, int *count, int mode)
{
    int check = 0, question;
    Hash_row *buff;
    buff = hashtable;
    while(buff != NULL)
    {
        *count = *count + 1;
        if(!strcmp(buff->keyword, keyword))
        {
            check = 1;
            if(!mode)
            {
                printf("Number of comparisons in the open hash-table: %d\n", *count);
                printf("%s", "The keyword has been found.\n");
                printf("HELP: %s\n", buff->HELP);
                printf("%s", "Rewrite HELP description?\n");
                printf("%s", "1 - Yes\n");
                printf("%s", "2 - No\n");
                scanf("%d", &question);
                if(question == 1)
                {
                    printf("%s", "Input HELP description:\n");
                    fflush(stdin);
                    gets(buff->HELP);
                }
            }
            break;
        }
        else
            buff = buff->next;
    }
    if(!mode && !check)
    {
        printf("Number of comparisons in the open hash-table: %d\n", *count);
        printf("%s", "The keyword has not been found.\n");
    }
}
//поиск в хеш-таблице с открытой адресацией
int closed_hash_search(Hash_row **hashtable, char *keyword, int n, int *count, int mode)
{
    int hashidx = hash(keyword, n), idx, l_idx, r_idx, check = 0, question = 0;
    *count = *count + 1;
    if(!strcmp(hashtable[hashidx]->keyword, keyword))
    {
        idx = hashidx;
        check = 1;
    }
    else
    {
        idx = l_idx = r_idx = hashidx;
        l_idx--;
        r_idx++;
        while((l_idx >= 0 && l_idx < n) || (r_idx >= 0 && r_idx < n))
        {
            *count = *count + 1;
            if(l_idx >= 0 && l_idx < n)
                if(!strcmp(hashtable[l_idx]->keyword, keyword))
                {
                    idx = l_idx;
                    check = 1;
                    break;
                }
            *count = *count + 1;
            if(r_idx >= 0 && r_idx < n)
                if(!strcmp(hashtable[r_idx]->keyword, keyword))
                {
                    idx = r_idx;
                    check = 1;
                    break;
                }
            l_idx--;
            r_idx++;
        }
    }
    if(!mode && !check)
    {
        printf("Number of comparisons in the open hash-table: %d\n", *count);
        printf("%s", "The keyword has not been found.\n");
        idx = -1;
    }
    else if(!mode)
    {
        printf("Number of comparisons in the open hash-table: %d\n", *count);
        printf("%s", "The keyword has been found.\n");
        printf("HELP: %s\n", hashtable[idx]->HELP);
        printf("%s", "Rewrite HELP description?\n");
        printf("%s", "1 - Yes\n");
        printf("%s", "2 - No\n");
        scanf("%d", &question);
        if(question == 1)
        {
            printf("%s", "Input HELP description:\n");
            fflush(stdin);
            gets(hashtable[idx]->HELP);
        }
    }
    return idx;
}

