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
    if (self->size * 0.7 <= self->count){
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
    self->count = 0;
    self->size = n;
    self->arr = malloc(n * sizeof(int));
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
    void (*add_edge)(struct graph *, int, int);
} graph;

void add_edge_(graph *self, int u, int v){
    vect *wherefrom = &self->vertices[u-1];
    wherefrom->push_back(wherefrom, v);
}

void init_graph(graph *self, size_t n){
    self->size = n;
    self->vertices = malloc(n * sizeof(vect));
    for (size_t i = 0; i < n; i++){
        init_vect(&self->vertices[i], 4);
    }
    self->add_edge = add_edge_;
}

void destroy_graph(graph *self){
    for (size_t i = 0; i < self->size; i++){
        destroy_vect(&self->vertices[i]);
    }
    free(self->vertices);
}

void dfs1(const graph *g, int u, bool *visited, vect *order) {
    visited[u-1] = true;
    vect *nbrs = &g->vertices[u-1];
    for (size_t i = 0; i < nbrs->count; i++) {
        int v = nbrs->arr[i];
        if (!visited[v-1])
            dfs1(g, v, visited, order);
    }
    order->push_back(order, u);
}

void dfs2(const graph *gT, int u, bool *visited) {
    visited[u-1] = true;
    vect *nbrs = &gT->vertices[u-1];
    for (size_t i = 0; i < nbrs->count; i++) {
        int v = nbrs->arr[i];
        if (!visited[v-1])
            dfs2(gT, v, visited);
    }
}

int main(void){
    size_t n, m;
    if (scanf("%zu %zu", &n, &m) != 2) return 0;

    graph G, GT;
    init_graph(&G,  n);
    init_graph(&GT, n);

    for (size_t i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        G .add_edge(&G,  u, v);
        GT.add_edge(&GT, v, u);
    }

    bool *visited = calloc(n, sizeof(bool));

    vect order;
    init_vect(&order, n);
    for (int u = 1; u <= (int)n; u++){
        if (!visited[u-1])
            dfs1(&G, u, visited, &order);
    }

    for (size_t i = 0; i < n; i++)
        visited[i] = false;

    int scc_count = 0;
    for (int idx = order.count - 1; idx >= 0; idx--){
        int u = order.arr[idx];
        if (!visited[u-1]) {
            scc_count++;
            dfs2(&GT, u, visited);
        }
    }

    printf("%d\n", scc_count);

    free(visited);
    destroy_vect(&order);
    destroy_graph(&G);
    destroy_graph(&GT);

    return 0;
}

