#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum {WHITE, BLACK, GREY} status;

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
        init_vect(&self->vertices[i], n);
    }
    self->add_edge = add_edge_;
}

void destroy_graph(graph *self){
    for (size_t i = 0; i < self->size; i++){
        destroy_vect(&self->vertices[i]);
    }
    free(self->vertices);
}

static bool cyclic;

void dfs(graph *gph, int curr, status *colours, vect *ordering){
    if (cyclic) return;
    // printf("Looking at %d\n", curr);
    colours[curr-1] = GREY;

    for (size_t j = 0; j < gph->vertices[curr-1].count && !cyclic; j++){
        int child = gph->vertices[curr-1].arr[j];
        if (colours[child-1] == WHITE){
            dfs(gph, child, colours, ordering);
        }
        else if (colours[child-1] == GREY){
            cyclic = true;
            return;
        }
    }

    colours[curr-1] = BLACK;
    ordering->push_back(ordering, curr);
    return;
}

void topological_sort(graph *gph){
    status *colours = calloc(gph->size, sizeof(status));
    vect ordering; init_vect(&ordering, gph->size);
    cyclic = false;

    for (size_t i = 1; i <= gph->size; i++){
        if (colours[i-1] == WHITE)
            dfs(gph, i, colours, &ordering);
        if (cyclic)
            break;
    }

    if (!cyclic){
        while (ordering.count){
            printf("%d ", ordering.pop_back(&ordering));
        }
    }
    else {
        puts("-1\n");
    }

    destroy_vect(&ordering);
    free(colours);
}

int main(void){
    size_t N, M;
    scanf("%zu %zu", &N, &M);

    graph gph; init_graph(&gph, N);

    for (size_t i = 0; i < M; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        gph.add_edge(&gph, u, v);
    }

    topological_sort(&gph);

    destroy_graph(&gph);
    return 0;
}
