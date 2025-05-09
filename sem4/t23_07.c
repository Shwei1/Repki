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
    vect *whereto = &self->vertices[v-1];
    wherefrom->push_back(wherefrom, v);
    whereto->push_back(whereto, u);
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

void dissect(graph *gph){
    
    status *colours = calloc(gph->size, sizeof(status));

    vect *components = malloc(gph->size * sizeof(vect));
    for (size_t i = 0; i < gph->size; i++) init_vect(&components[i], 1);
    int component_id = 0;

    for (size_t n = 1; n <= gph->size; n++){
        if (colours[n-1] == WHITE){
            component_id++;
            components[component_id-1].push_back(&components[component_id-1], n);
            vect stk; init_vect(&stk, gph->size);

            stk.push_back(&stk, n);

            while(stk.count){
                int curr = stk.pop_back(&stk);
                colours[curr-1] = GREY;

                for (size_t j = 0; j < gph->vertices[curr-1].count; j++){
                    int child = gph->vertices[curr-1].arr[j];
                    if (colours[child - 1] == WHITE){
                        stk.push_back(&stk, child);
                        colours[child-1] = GREY;
                        components[component_id-1].push_back(&components[component_id-1], child);
                    }
                }
                colours[curr-1] = BLACK;
            }
            destroy_vect(&stk);
        }
    }

    printf("%d\n", component_id);
    for (size_t i = 0; i < gph->size; i++){
        if (components[i].count){
            printf("%zu\n", components[i].count);
            for (size_t j = 0; j < components[i].count; j++){
                printf("%d ", components[i].arr[j]);
            }
            puts("");
        }
    }

    for (size_t i = 0; i < gph->size; i++) destroy_vect(&components[i]);
    free(colours);
    free(components);
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

    dissect(&gph);

    destroy_graph(&gph);
}
