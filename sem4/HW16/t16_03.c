#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* VERBOSE HELLSCAPE / DATA STRUCT PLAYGROUND */

struct node;
typedef struct node node;

typedef struct vec_t{
    node **arr;
    size_t count;
    size_t size;
    
    void (*resize)(struct vec_t *);
    void (*push_back)(struct vec_t *, node *);
    bool (*is_empty)(struct vec_t *);
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

bool vec_is_empty_(vec_t *self){
    return self->count == 0;
}

void init_vec(vec_t *self){
    self->count = 0;
    self->size = 2;
    self->arr = malloc(self->size * sizeof(node*));

    self->push_back = vec_push_back_;
    self->resize = vec_resize_;
    self->is_empty = vec_is_empty_;
}

void destroy_vec(vec_t *self){
    free(self->arr);
}

typedef struct node{
    int colour;
    vec_t children;
} node;

typedef struct stack{
    node **arr;
    size_t size;
    size_t count;

    void (*push_top)(struct stack *, node *);
    void (*resize)(struct stack *);
    node *(*pop)(struct stack *);
    bool (*is_empty)(struct stack *);
} stack;

void stk_resize_(stack *self){
    self->size *= 2;
    self->arr = realloc(self->arr, self->size * sizeof(node *));
}

void stk_push_top_(stack *self, node *new_node){
    if (self->count > (size_t)(self->size * 0.7)) self->resize(self);

    self->arr[self->count++] = new_node;
}

node* stk_pop_(stack *self){
    self->count--;
    return self->arr[self->count];
}

bool stk_is_empty_(stack *self){
    return self->count == 0;
}

void init_stk(stack *self){
    self->size = 2;
    self->arr = malloc(self->size * sizeof(node*));
    self->count = 0;

    self->resize = stk_resize_;
    self->push_top = stk_push_top_;
    self->pop = stk_pop_;
    self->is_empty = stk_is_empty_;
}

void destroy_stk(stack *self){
    free(self->arr);
}

int DFS(node *start, size_t colour_count){
    stack stk; 
    init_stk(&stk);

    int count = 0;

    bool *colours = calloc(colour_count, sizeof(bool));

    stk.push_top(&stk, start);

    while (!stk.is_empty(&stk)){
        node *curr = stk.pop(&stk);

        if (!colours[curr->colour-1]){
            colours[curr->colour-1] = true;
            count++;
        }

        for (size_t i = 0; i < curr->children.count; i++){
            stk.push_top(&stk, curr->children.arr[i]);
        }
    }
    free(colours);
    destroy_stk(&stk);
    return count;
}

int main(void){
    size_t n;
    scanf("%zu", &n);

    node *c = malloc(n * sizeof(node));
    size_t *p = malloc(n * sizeof(size_t));

    for (size_t i = 0; i < n; i++){
        int c_i;
        size_t p_i;
        scanf("%zu %d", &p_i, &c_i);

        p[i] = p_i;
        c[i].colour = c_i;
        init_vec(&c[i].children);
    }

    for (size_t i = 0; i < n; i++){
        if (p[i]){
           c[p[i]-1].children.push_back(&c[p[i]-1].children, &c[i]);
        }
    }

    for (size_t i = 0; i < n; i++){
        printf("%d ", DFS(&c[i], n));
    }

    for (size_t i = 0; i < n; i++)
        destroy_vec(&c[i].children);
    free(c);
    free(p);

    return 0;
}
