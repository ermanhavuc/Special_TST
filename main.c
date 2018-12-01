#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct tst {
    int data;
    struct bin_tree *right, *mid, *left;
};
typedef struct tst node;

int pInt[200];
int max_size = 0;

void insert(node **tree, int val) {
    node *temp = NULL;
    if (!(*tree)) {
        temp = (node *) malloc(sizeof(node));
        temp->left = temp->right = temp->mid = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if (val < (*tree)->data) {
        insert(&(*tree)->left, val);
    } else if (val > (*tree)->data && val < pow((*tree)->data, 2)) {
        insert(&(*tree)->mid, val);
    } else if (val > pow((*tree)->data, 2)) {
        insert(&(*tree)->right, val);
    }
}

node *find(node **tree, int val) {
    if (!(*tree)) {
        return NULL;
    }

    if (val < (*tree)->data) {
        find(&(*tree)->left, val);
    } else if (val > (*tree)->data && val < pow((*tree)->data, 2)) {
        find(&(*tree)->mid, val);
    } else if (val > pow((*tree)->data, 2)) {
        find(&(*tree)->right, val);
    } else if (val == (*tree)->data) {
        return *tree;
    }
}

int print_preorder(node *tree) {
    if (tree) {
        printf("%d\n", tree->data);
        print_preorder(tree->left);
        print_preorder(tree->mid);
        print_preorder(tree->right);
    }
}

int FindIndex(const int a[], size_t size, int value) {
    size_t index = 0;

    while (index < size && a[index] != value) ++index;

    return (index == size ? -1 : index);
}

node *delete(int val) {
    node *root = NULL;
    int position = FindIndex(pInt, max_size, val);

    if (position != -1) {
        for (int c = position; c < max_size - 1; c++)
            pInt[c] = pInt[c + 1];

        max_size--;

        for (int i = 0; i < max_size - 1; i++) {
            insert(&root, pInt[i]);
        }
    } else {
        printf("Can't find this value in TST!\n");
    }
    return root;
}

int main() {
    FILE *fp;
    fopen_s(&fp, "../input.txt", "r");

    node *root = NULL;
    node *tmp = NULL;

    int input = 0;
    int i = 0;
    int menu;

    printf("Welcome to TST handler program!\n\n");

    while (fscanf_s(fp, "%d", &input) != EOF) {
        insert(&root, input);
        pInt[i] = input;
        i++;
    }

    max_size = i;

    while (1) {
        printf("Please choose:\n");
        printf("1. Insert a value\n");
        printf("2. Delete a value\n");
        printf("3. Find a value\n");
        printf("4. Print the TST\n");
        printf("0. Exit\n");

        scanf_s("%d", &menu);

        switch (menu) {
            case 1:
                printf("Enter the value: \n");
                scanf_s("%d", &menu);
                insert(&root, menu);
                max_size++;
                pInt[max_size - 1] = menu;
                break;
            case 2:
                printf("Enter the value: \n");
                scanf_s("%d", &menu);
                root = delete(menu);
                break;
            case 3:
                printf("Enter the value: \n");
                scanf_s("%d", &menu);
                tmp = find(&root, menu);
                if (tmp) {
                    printf("Searched node=%d\n", tmp->data);
                } else {
                    printf("Data Not found in tree.\n");
                }
                break;
            case 4:
                printf("\n");
                print_preorder(root);
                printf("\n");
                break;
            case 0:
                break;
            default:
                printf("Please enter a valid input\n");
        }

        if (menu == 0)
            break;
    }

    return 0;
}