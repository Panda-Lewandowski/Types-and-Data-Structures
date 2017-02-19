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

int is_left(node *nod)
{
    int res = 0;
    if (nod->par)
        if (nod->par->left)
            if (!strcmp(nod->word, nod->par->left->word))
                res = 1;
    return res;
}

void add(tree *tr, char* word)
{
    node *temp1 = NULL;
    node *temp2 = tr->root;
    while (temp2 != NULL)
    {
        temp1 = temp2;
        if (strcmp(word, temp2->word) < 0)
            temp2 = temp2->left;
        else if(strcmp(word, temp2->word) > 0)
            temp2 = temp2->right;
        else
        {
            temp2->reps++;
            return;
        }
    }
    if (temp1 == NULL)
    {
        init_root(tr);
        strcpy(tr->root->word, word);
        tr->root->reps = 1;
    }
    else if (strcmp(temp1->word, word) <= 0)
    {
        node *temp = (node*)malloc(sizeof(node));
        init_node(temp);
        strcpy(temp->word, word);
        temp->reps = 1;
        temp1->right = temp;
        temp->par = temp1;
    }
    else
    {
        node *temp = (node*)malloc(sizeof(node));
        init_node(temp);
        strcpy(temp->word, word);
        temp->reps = 1;
        temp1->left = temp;
        temp->par = temp1;
    }

    /*const int MAX_LINE = 50;

    if(!tr)
    {
        node *temp = (node*)malloc(sizeof(node));
        if(!temp)
            return NULL;

        memset(temp, 0, sizeof(node));
        //temp->word = malloc(sizeof(char[MAX_LINE + 1]));
        memset(temp->word, 0, MAX_LINE + 1);
        strncpy(temp->word, word, MAX_LINE);
        temp->word[MAX_LINE] = 0;
        ++temp->reps;
        tr->root = temp;
        return tr;
    }
    else
    {
        int res = strcmp(word, tr->root->word);
        if(res < 0)
        {
            tr->root = tr->root->left;
            add(tr, word);
        }
        else if(res > 0)
        {
            tr->root = tr->root->right;
            add(tr, word);
        }
        else
            ++tr->root->reps;

        return tr;
    }*/







}

node* search(tree *tr, char *word, int *n)
{
    node *temp = tr->root;*n = 0;
    while (temp != NULL)
    {
        int cmp = strcmp(word, temp->word);
        if (cmp == 0)
            break;
        if (cmp < 0)
            temp = temp->left;
        else
            temp = temp->right;

        (*n)++;
        //printf("%d\n", *n);
    }
    return temp;
}

int delete_word(tree *tr, char *word)
{
    node *temp;
    int n = 0;
    temp = search(tr, word, &n);
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
            printf("%s", "     ");
        printf("%s(%d)\n", nod->word, nod->reps);
        print_tree(nod->right,level + 1);
    }
}

void preOrder(const struct node_s * nod)
{
    if (nod)
    {
        printf("%s(%d)\n", nod->word, nod->reps);
        preOrder(nod->left);
        preOrder(nod->right);
    }
    else return;
}

void inOrder(const struct node_s * nod) {
    if (nod) {
        inOrder(nod->left);
        printf("%s(%d)\n", nod->word, nod->reps);
        inOrder(nod->right);
    }
    else return;
}

void postOrder(const struct node_s * nod) {
    if (nod) {
        postOrder(nod->left);
        postOrder(nod->right);
        printf("%s(%d)\n", nod->word, nod->reps);
    }
    else return;
}
