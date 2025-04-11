#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node node;

typedef struct vec_t{
    node **arr;
    size_t count;
    size_t size;
    
    void (*resize)(struct vec_t *);
    void (*push_back)(struct vec_t *, node *);
} vec_t;

void vec_resize_(vec_t *self) {
    self->size *= 2;
    node **tmp = realloc(self->arr, self->size * sizeof(node *));
    self->arr = tmp;
}

void vec_push_back_(vec_t *self, node *new_node){
    if (self->count > (size_t)(self->size * 0.7)){
        self->resize(self);
    }
    self->arr[self->count++] = new_node;
}

void init_vec(vec_t *self){
    self->count = 0;
    self->size = 2;
    self->arr = malloc(self->size * sizeof(node*));

    self->push_back = vec_push_back_;
    self->resize = vec_resize_;
}

void destroy_vec(vec_t *self){
    free(self->arr);
}

typedef struct node{
    int price;
    vec_t subordinates;
    size_t *indices;
    size_t indices_count;
} node;

typedef struct tree{
    node *root;
} tree;

void init_tree(tree *self, node *root){
    self->root = root;
}

int DFS_(node *curr){
    int best = INT_MAX;

    if (!curr->subordinates.count) return curr->price;

    for (size_t i = 0; i < curr->subordinates.count; i++){
        int candidate = DFS_(curr->subordinates.arr[i]);
        candidate += curr->price;
        best = candidate < best ? candidate : best;
    }

    return best;
}

int DFS(tree *t){
    return DFS_(t->root);
}

int main(void){
    size_t N;
    scanf("%zu", &N);

    node *ministers = malloc(N * sizeof(node));

    for (size_t i = 0; i < N; i++){
        int price; 
        size_t subordinate_count;
        scanf("%d %zu", &price, &subordinate_count);
        ministers[i].indices = malloc(subordinate_count * sizeof(size_t));
        init_vec(&ministers[i].subordinates);
        ministers[i].indices_count = subordinate_count;
        ministers[i].price = price;

        for (size_t j = 0; j < subordinate_count; j++){
            size_t subordinate_index;
            scanf("%zu", &subordinate_index);
            ministers[i].indices[j] = subordinate_index - 1; // f*ck one-indexed input
        }
    }

    for (size_t i = 0; i < N; i++){
        for (size_t j = 0; j < ministers[i].indices_count; j++){
            size_t index = ministers[i].indices[j];
            ministers[i].subordinates.push_back(&ministers[i].subordinates, &ministers[index]);
        }
    }

    node root = ministers[0];
    tree my_tree;
    init_tree(&my_tree, &root);

    int answer = DFS(&my_tree);

    printf("%d", answer);

    for (size_t i = 0; i < N; i++){
        free(ministers[i].indices);
        destroy_vec(&ministers[i].subordinates);
    }
    free(ministers);
    return 0;
}
