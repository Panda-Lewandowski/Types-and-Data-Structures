#include "methods.h"

void init_tree(tree *tr)
{
    tr->root = NULL;
}

void init_node(node *temp)
{
    temp->left = NULL;
    temp->right = NULL;
    temp->par = NULL;
}

void init_root(tree *tr)
{
    node *temp = (node*)malloc(sizeof(node));
    init_node(temp);
    tr->root = temp;
}

int add(tree *tr, node *data)
{
    node *temp1 = NULL;
    node *temp2 = tr->root;
    int res = 0;
    while (temp2 != NULL)
    {
        temp1 = temp2;
        if (strcmp(data->keyword, temp2->keyword) < 0)
            temp2 = temp2->left;
        else if(strcmp(data->keyword, temp2->keyword) > 0)
            temp2 = temp2->right;
        else
        {
            printf("That keyword is already in the tree.\n");
            res = 1;
            break;
        }
    }
    if (temp1 == NULL && res != 1)
    {
        init_root(tr);
        strcpy(tr->root->keyword, data->keyword);
        strcpy(tr->root->HELP, data->HELP);
    }
    else if ((strcmp(temp1->keyword, data->keyword) <= 0 )&& res != 1)
    {
        node *temp = (node*)malloc(sizeof(node));
        init_node(temp);
        strcpy(temp->keyword, data->keyword);
        strcpy(temp->HELP, data->HELP);
        temp1->right = temp;
        temp->par = temp1;
    }
    else if(res != 1)
    {
        node *temp = (node*)malloc(sizeof(node));
        init_node(temp);
        strcpy(temp->keyword, data->keyword);
        strcpy(temp->HELP, data->HELP);
        temp1->left = temp;
        temp->par = temp1;
    }

    return res;
}

node* search(tree *tr, char *keyword, int* count, int mode)
{
    node *temp = tr->root;
    int check = 0, question;
    while (temp != NULL)
    {
        *count = *count + 1;
        if (strcmp(keyword, temp->keyword) == 0)
        {
            check = 1;
            if(!mode)
            {
                printf("Number of comparisons in the binary tree: %d\n", *count);
                printf("%s", "The keyword has been found.\n");
                printf("HELP: %s\n", temp->HELP);
                printf("%s", "Rewrite HELP description?\n");
                printf("%s", "1 - Yes\n");
                printf("%s", "2 - No\n");
                scanf("%d", &question);
                if(question == 1)
                {
                    printf("%s", "Input HELP description:\n");
                    fflush(stdin);
                    gets(temp->HELP);
                }
             }
             break;
        }
        if (strcmp(keyword, temp->keyword) < 0)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if(!mode && !check)
    {
        printf("Number of comparisons in the binary tree: %d\n", *count);
        printf("%s", "The keyword has not been found.\n");
    }
    return temp;
}

int delete_keyword(tree *tr, char *keyword)
{
    node *temp;
    int count = 0;
    temp = search(tr, keyword, &count, 1);
    if (temp == NULL)
        return ERR_DELETE;
    if (temp != tr->root)
    {
        if ((temp->left == NULL)*(temp->right == NULL))
        {
            if (is_left(temp))
                temp->par->left = NULL;
            else
                temp->par->right = NULL;
        }
        else if ((temp->left == NULL)*(temp->right != NULL))
        {
            if (is_left(temp))
            {
                temp->par->left = temp->right;
                temp->right->par = temp->par;
            }
            else
            {
                temp->par->right = temp->right;
                temp->right->par = temp->par;
            }
        }
        else if ((temp->right == NULL)*(temp->left != NULL))
        {
            if (is_left(temp))
            {
                temp->par->left = temp->left;
                temp->left->par = temp->par;
            }
            else
            {
                temp->par->right = temp->left;
                temp->left->par = temp->par;
            }
        }
        else
        {
            node *temp2 = temp->right;
            while (temp2->left != NULL)
            {
                temp2 = temp2->left;
            }
            if (is_left(temp))
            {
                temp->par->left = temp2;
                temp2->par = temp->par;
            }
            else
            {
                temp->par->right = temp2;
                temp2->par = temp->par;
            }

            temp2->left = temp->left;
            temp->left->par = temp2;
        }
    }
    else
    {
        if ((tr->root->left == NULL)*(tr->root->right == NULL))
            tr->root = NULL;
        else if ((tr->root->left == NULL)*(tr->root->right != NULL))
        {
            tr->root->right->par = NULL;
            tr->root = tr->root->right;
        }
        else if ((tr->root->left != NULL)*(tr->root->right == NULL))
        {
            tr->root->left->par = NULL;
            tr->root = tr->root->left;
        }
        else
        {
            node *temp2 = tr->root->right;
            while (temp2->left != NULL)
            {
                temp2 = temp2->left;
            }
            temp2->left = tr->root->left;
            tr->root->left->par = temp2;
            tr->root = tr->root->right;
            tr->root->par = NULL;
        }
    }
    return OK;
}

void print_tree(struct node_s * nod, int level)
{
    if(nod)
    {
        print_tree(nod->left, level + 1);
        for(int i = 0;i < level;i++)
            printf("%s", "   ");
        printf("%s\n", nod->keyword);
        print_tree(nod->right,level + 1);
    }
}

int count(node *nod)
{
    int res = 0;
    if (nod != NULL)
        res = 1 + count(nod->left) + count(nod->right);
    return res;
}

node* min(node *root)
{
    node *temp = root;
    if (temp)
    {
        while (temp->left != NULL)
            temp = temp->left;
    }
    return temp;
}

node* max (node *root)
{
    node *temp = root;
    if (temp)
    {
        while (temp->right != NULL)
            temp = temp->right;
    }
    return temp;
}

int is_left (node *nod)
{
    int res = 0;
    if (nod->par)
        if (nod->par->left)
            if (strcmp(nod->keyword, nod->par->left->keyword) == 0)
                res = 1;
    return res;
}

int is_right (node *nod)
{
    int res = 0;
    if (nod->par)
        if (nod->par->right)
            if (strcmp(nod->keyword, nod->par->right->keyword) == 0)
                res = 1;
    return res;
}

node* next(node *temp)
{
    node *res = temp;
    if (res == NULL)
        return NULL;
    if (res->right != NULL)
    {
        res = min(res->right);
    }
    else
    {
        while (res != NULL)
        {
            if (is_left(res))
            {
                res = res->par;
                break;
            }
            else
                res = res->par;
        }
    }
    return res;
}
//балансировка
node* balance(node *nod)
{

    int l = count(nod);
    int i;
    node *temp = min(nod);
    node *temp1 = (node*)malloc(sizeof(node));
    node *temp2 = (node*)malloc(sizeof(node));
    tree *sub1 = (tree*)malloc(sizeof(tree));
    tree *sub2 = (tree*)malloc(sizeof(tree));
    init_tree(sub1);
    init_tree(sub2);
    node *res = (node*)malloc(sizeof(node));
    res = nod;
    if (l > 2)
    {
        for (i = 0; i < l/2; i++)
        {
            add(sub1, temp);
            temp = next(temp);
        }
        res = temp;
        temp = next(temp);
        for (i = l/2; i < l-1; i++)
        {
            add(sub2, temp);
            temp = next(temp);
        }
        temp1 = balance(sub1->root);
        temp2 = balance(sub2->root);
        res->left = temp1;
        res->right = temp2;
        temp1->par = res;
        temp2->par = res;
    }
    return res;
}

void get_balanced_tree(tree *tr)
{
    node *temp = balance(tr->root);
    if (is_left(temp))
    {
        temp->par->left = NULL;
        temp->par = NULL;
    }
    if (is_right(temp))
    {
        temp->par->right = NULL;
        temp->par = NULL;
    }
    tr->root = temp;
}




