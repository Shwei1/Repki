#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct vect{
    size_t size;
    size_t count;
    int *arr;
    void (*resize_)(struct vect *);
    void (*push_back)(struct vect *, int);
    int (*pop_back)(struct vect *);
} vect;

void resize__(vect *self){
    self->size *= 2;
    self->arr = realloc(self->arr, self->size * sizeof(int));
}

void push_back_(vect *self, int value){
    if (self->size * 0.7 < self->count){
        self->resize_(self);
    }
    self->arr[self->count++] = value;
}

int pop_back_(vect *self){
    if (!self->count)
        return -1;
    return self->arr[--self->count];
}

void init_vect(vect *self, size_t n){
    if (n < 2)
        n = 2;
    self->count = 0;
    self->size = n;
    self->arr = (int *)malloc(n * sizeof(int));
    self->resize_ = resize__;
    self->push_back = push_back_;
    self->pop_back = pop_back_;
}

void destroy_vect(vect *self){
    free(self->arr);
}

typedef struct graph{
    size_t size;
    vect *vertices;
    void (*add_vertex)(struct graph *, int, int);
} graph;

void add_vertex_(graph *self, int u, int v){
    vect *wherefrom = &self->vertices[u-1];
    wherefrom->push_back(wherefrom, v);
}

void init_graph(graph *self, size_t n){
    self->size = n;
    self->vertices = malloc(n * sizeof(vect));
    for (size_t i = 0; i < n; i++){
        init_vect(&self->vertices[i], n);
    }
    self->add_vertex = add_vertex_;
}

void destroy_graph(graph *self){
    for (size_t i = 0; i < self->size; i++){
        destroy_vect(&self->vertices[i]);
    }
    free(self->vertices);
}

void treeify(graph *gph){
    bool *visited = calloc(gph->size, sizeof(bool));

    vect stk; init_vect(&stk, gph->size);

    stk.push_back(&stk, 1);

    visited[1-1] = true;

    while (stk.count){
        int curr = stk.pop_back(&stk);

        for (size_t i = 0; i < gph->vertices[curr-1].count; i++){
            if (!visited[gph->vertices[curr-1].arr[i] - 1]){
                visited[gph->vertices[curr-1].arr[i] - 1] = true;
                printf("%d %d\n", curr, gph->vertices[curr-1].arr[i]);
                stk.push_back(&stk, gph->vertices[curr-1].arr[i]);
            }
        }
    }
}

int main(void){
    size_t n, m;
    scanf("%zu %zu", &n, &m);

    graph gph; init_graph(&gph, n);

    for (size_t i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        gph.add_vertex(&gph, u, v);
        gph.add_vertex(&gph, v, u);
    }

    treeify(&gph);

    destroy_graph(&gph);
    return 0;
}
