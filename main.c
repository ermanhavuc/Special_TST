#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct tst {
    int data;
    struct bin_tree * right, * mid, * left;
};
typedef struct tst node;

int inputarray[200];
int max_size=0;

void insert(node ** tree, int val)
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = temp->mid = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)
    {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data && val < pow((*tree)->data,2))
    {
        insert(&(*tree)->mid, val);
    }
    else if(val > pow((*tree)->data,2))
    {
        insert(&(*tree)->right, val);
    }

}

node* find(node ** tree, int val)
{
    if(!(*tree))
    {
        return NULL;
    }

    if(val < (*tree)->data)
    {
        find(&(*tree)->left, val);
    }
    else if(val > (*tree)->data && val < pow((*tree)->data,2))
    {
        find(&(*tree)->mid, val);
    }
    else if(val > pow((*tree)->data,2))
    {
        find(&(*tree)->right, val);
    }
    else if(val == (*tree)->data)
    {
        return *tree;
    }
}

int print_preorder(node * tree)
{
    if (tree)
    {
        printf("%d\n",tree->data);
        print_preorder(tree->left);
        print_preorder(tree->mid);
        print_preorder(tree->right);
    }
}

size_t FindIndex( const int a[], size_t size, int value )
{
    size_t index = 0;

    while ( index < size && a[index] != value ) ++index;

    return ( index == size ? -1 : index );
}

node* delete(int val)
{
    node* root = NULL;

    int position = FindIndex(inputarray, max_size, val);

    for (int c = position; c < max_size - 1; c++)
        inputarray[c] = inputarray[c+1];

    max_size--;

    for(int i = 0; i < max_size; i++){
        insert(&root, inputarray[i]);
    }

    return root;
}

void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->mid);
        deltree(tree->right);
        free(tree);
    }
}

int main() {
    FILE *fp;
    fopen_s(&fp, "../input.txt", "r");

    node *root;
    node *tmp = NULL;

    root = NULL;

    int input=0;
    int i=0;
    int a;

    while(fscanf_s(fp, "%d", &input) != EOF){
        insert(&root, input);
        inputarray[i]=input;
        max_size++;
        i++;
    }

    //printf("%d",print_preorder(root));
    //tmp = find(&root, 75);
    //node * deneme = removea(root, &tmp, 75);

    print_preorder(delete(75));
    printf("\n");
    print_preorder(delete(1700));

    return 0;
}