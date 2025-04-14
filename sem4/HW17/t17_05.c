#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int value;
    struct node *left, *right;
} node;

typedef struct tree{
    node *root;
} tree;

void init(tree *self){
    self->root = NULL;
}

void insert(tree *self, int value) {

    node *new_node = malloc(sizeof *new_node);
    
    new_node->value = value;
    new_node->left = new_node->right = NULL;

    if (self->root == NULL) {
        self->root = new_node;
        return;
    }

    node *curr = self->root, *parent = NULL;

    while (curr) {
        parent = curr;
        if (value < curr->value)
            curr = curr->left;
        else if (value > curr->value)
            curr = curr->right;
        else {
            free(new_node);
            return;
        }
    }

    if (value < parent->value)
        parent->left  = new_node;
    else
        parent->right = new_node;
}

bool check(tree *self, int *arr, int size) {
    if (size <= 0) return false;       

    node *curr = self->root;
    for (int i = 0; i < size; i++) {
        if (!curr) 
            return false;

        if (arr[i] != curr->value)
            return false;

        if (i == size - 1)
            return (curr->left == NULL && curr->right == NULL);

        if (arr[i+1] < curr->value)
            curr = curr->left;
        else if (arr[i+1] > curr->value)
            curr = curr->right;
        else
            return false;  
    }

    return false;
}

void destroy_(node *curr){
    if (!curr) return;
    destroy_(curr->left);
    destroy_(curr->right);
    free(curr);
}

void destroy(tree *self){
    destroy_(self->root);
}


int main(void){

    int *arr = malloc(sizeof *arr * 50000);

    int x;
    int idx = 0;

    // int arr[4] = {5, 1, 3, 2};

    while (scanf("%d", &x) == 1){
        arr[idx++] = x;
    }

    tree bst;
    init(&bst);

    for (int i = 0; i < idx; i++){
        insert(&bst, arr[i]);
    }

     puts(check(&bst, arr, idx) ? "YES" : "NO");

    free(arr);
    destroy(&bst);
    return 0;
}
