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

void insert(tree *self, int value){
    node *new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->right = new_node->left = NULL;

    node *curr = self->root;
    node *parent = NULL;

    while (curr){
        parent = curr;
        if (curr->value < value){
            curr = curr->right;
        }
        else if (curr->value > value){
            curr = curr->left;
        }
        else {
            free(new_node);
            return;
        }
    }

    if (parent->value > value){
        parent->right = new_node;
    }
    else if (parent->value < value){
        parent->left = new_node;
    }
    else return;
}

bool check(tree *self, int *arr, int size){
    node *curr = self->root;
    
    for (int i = 0; i < size, curr->left && curr->right ; i++){
        
        if (!curr) 
            return false;    

        if (arr[i] != curr->value){
            return false;
        }

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


int main(void){
    int *arr = malloc(sizeof *arr * 50000);

    int x;
    int idx = 0;
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
    return 0;
}


