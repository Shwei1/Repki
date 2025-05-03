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
    if (!(n % 2))
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

int dfs(graph *gph, int vertex, vect *children, int b, int d, int depth, bool *visited){
    if (depth > d)
        return 0;
    if (vertex == b)
        return 1;
    
    int count = 0;

    for (size_t i = 0; i < children->count; i++){
        if (!visited[children->arr[i]-1]){
            visited[children->arr[i]-1] = 1;
            count += dfs(gph, children->arr[i], &gph->vertices[children->arr[i]-1], b, d, depth+1, visited);
            visited[children->arr[i]-1] = 0;
        }
    }
    return count;
}

int count_paths(graph *gph, int a, int b, int d){
    bool *visited = calloc(gph->size, sizeof(bool));
    visited[a-1] = 1;
    int result = dfs(gph, a, &gph->vertices[a-1], b, d, 0, visited);
    free(visited);
    return result;
}

int main(void){
    size_t n, k;
    int a, b, d;
    scanf("%zu %zu %d %d %d", &n, &k, &a, &b, &d);

    graph gph;
    init_graph(&gph, n);

    for (size_t i = 0; i < k; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        gph.add_vertex(&gph, u, v);
    }

    int res = count_paths(&gph, a, b, d);

    printf("%d\n", res);

    destroy_graph(&gph);
    return 0;
}


