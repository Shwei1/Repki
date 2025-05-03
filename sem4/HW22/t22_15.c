#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define PROMOTED 1
#define OPERATOR 2

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

typedef struct queue{
    size_t size;
    size_t count;
    size_t head;
    int *arr;
    void (*resize_)(struct queue *);
    void (*push_back)(struct queue *, int);
    int (*pop_front)(struct queue *);
} queue;

int pop_front_(queue *self){
    if (!self->count)
        return -1;
    int value = self->arr[self->head];
    self->head = (self->head + 1) % self->size;
    self->count--;
    return value;
}

void q_resize_(queue *self){
    size_t newsize = self->size * 2;
    int *newarr = malloc(newsize * sizeof(int));

    for (size_t i = 0; i < self->count; i++){
        newarr[i] = self->arr[(self->head + i) % self->size];
    }

    free(self->arr);
    self->size = newsize;
    self->arr = newarr;
    self->head = 0;
}

void q_push_back_(queue *self, int value){
    if (self->count > self->size * 0.7)
        self->resize_(self);

    size_t tail = (self->head + self->count) % self->size;
    self->arr[tail] = value;
    self->count++;
}

void init_queue(queue *self, size_t n){
    self->size = n;
    self->head = self->count = 0;
    self->arr = malloc(n * sizeof(int));
    self->resize_ = q_resize_;
    self->push_back = q_push_back_;
    self->pop_front = pop_front_;
}

void destroy_queue(queue *self){
    free(self->arr);
}

typedef struct graph{
    size_t size;
    int *rights;
    vect *vertices;
    vect *covertices;
    bool *sharing;
    void (*add_vertex)(struct graph *, int, int);
} graph;

void add_vertex_(graph *self, int u, int v){
    vect *wherefrom = &self->vertices[u-1];
    vect *whereto = &self->covertices[v-1];
    wherefrom->push_back(wherefrom, v);
    whereto->push_back(whereto, u);
}

void init_graph(graph *self, size_t n){
    self->size = n;
    self->vertices = malloc(n * sizeof(vect));
    self->covertices = malloc(n * sizeof(vect));

    for (size_t i = 0; i < n; i++){
        init_vect(&self->vertices[i], n);
        init_vect(&self->covertices[i], n);
    }
    self->add_vertex = add_vertex_;
    self->rights = calloc(n, sizeof(int));
    self->sharing = calloc(n, sizeof(bool));
}

void destroy_graph(graph *self){
    for (size_t i = 0; i < self->size; i++){
        destroy_vect(&self->vertices[i]);
        destroy_vect(&self->covertices[i]);
    }
    free(self->vertices);
    free(self->covertices);
    free(self->rights);
    free(self->sharing);
}

void promote(graph *base, int user_id){
    base->rights[user_id-1] = OPERATOR;

    if (base->sharing[user_id-1]){
        for (size_t i = 0; i < base->vertices[user_id-1].count; i++){
            if (base->rights[base->vertices[user_id-1].arr[i]-1] != OPERATOR){
                base->rights[base->vertices[user_id-1].arr[i]-1] = PROMOTED;
            }
        }
    }
}

void demote(graph *base, int user_id){
    base->rights[user_id-1] = 0;

    for (size_t j = 0; j < base->covertices[user_id-1].count; j++){
        int boss = base->covertices[user_id-1].arr[j];
        if (base->rights[boss - 1] && base->sharing[boss-1]){
            base->rights[user_id-1] = PROMOTED;
            break;
        }
    }

    queue q; init_queue(&q, base->size);
    bool *in_queue = calloc(base->size, sizeof(bool));

    // start from X’s direct subordinates (but only if X is sharing; if X isn't sharing
    // no one below could ever have inherited *from* X in the first place)
    if (base->sharing[user_id-1]) {
        for (size_t i = 0; i < base->vertices[user_id-1].count; i++){
            int sub = base->vertices[user_id-1].arr[i];
            q.push_back(&q, sub);
            in_queue[sub-1] = true;
        }
    }

    while (q.count){
        int curr = q.pop_front(&q);

        if (base->rights[curr-1] == OPERATOR)
            continue;


        bool has_source = false;
        for (size_t k = 0; k < base->covertices[curr-1].count; k++){
            int boss = base->covertices[curr-1].arr[k];
            if (base->rights[boss-1] && base->sharing[boss-1]){
                has_source = true;
                break;
            }
        }

        if (!has_source){
            base->rights[curr-1] = 0;
            if (base->sharing[curr-1]) {
                for (size_t m = 0; m < base->vertices[curr-1].count; m++){
                    int sub2 = base->vertices[curr-1].arr[m];
                    if (!in_queue[sub2-1]){
                        q.push_back(&q, sub2);
                        in_queue[sub2-1] = true;
                    }
                }
            }
        }
    }

    destroy_queue(&q);
    free(in_queue);
}

void promote_subjugates(graph *base, int user_id){
    base->sharing[user_id-1] = true;
    for (size_t i = 0; i < base->vertices[user_id - 1].count; i++){
        int curr = base->vertices[user_id - 1].arr[i];
        if (base->rights[curr-1] != OPERATOR)
            base->rights[curr-1] = PROMOTED;
    }
}

void promote_down(graph *base, int user_id){

    bool *visited = calloc(base->size, sizeof(bool));
    visited[user_id-1] = true;

    vect stk; init_vect(&stk, base->size);
    stk.push_back(&stk, user_id);

    while (stk.count){
        int curr = stk.pop_back(&stk);

        base->sharing[curr-1] = true;

        for (size_t i = 0; i < base->vertices[curr-1].count; i++){
            if (!visited[base->vertices[curr-1].arr[i] - 1]){
                visited[base->vertices[curr-1].arr[i] - 1] = true;
                stk.push_back(&stk, base->vertices[curr-1].arr[i]);
                if (base->rights[base->vertices[curr-1].arr[i] - 1] != OPERATOR)
                    base->rights[base->vertices[curr-1].arr[i] - 1] = PROMOTED;
            }
        }
    }

    destroy_vect(&stk);
    free(visited);
}

void demote_subjugates(graph *base, int user_id){
    base->sharing[user_id-1] = false;

    queue q; init_queue(&q, base->size);
    bool *in_queue = calloc(base->size, sizeof(bool));

    for (size_t i = 0; i < base->vertices[user_id-1].count; i++){
        q.push_back(&q, base->vertices[user_id-1].arr[i]);
        in_queue[base->vertices[user_id-1].arr[i]-1] = true;
    }

    while (q.count){
        int curr = q.pop_front(&q);

        if (base->rights[curr-1] == OPERATOR)
            continue;

        bool accepts = false;
        for (size_t j = 0; j < base->covertices[curr-1].count; j++){
            int boss = base->covertices[curr-1].arr[j];
            if (base->rights[boss-1] && base->sharing[boss-1]){
                accepts = true;
                break;
            }
        }

        if (!accepts){
                base->rights[curr-1] = 0;
                for (size_t k = 0; k < base->vertices[curr-1].count; k++){
                    int subjugate = base->vertices[curr-1].arr[k];
                    if (!in_queue[subjugate-1]){
                        q.push_back(&q, subjugate);
                        in_queue[subjugate-1] = true;
                    }
                }
            }
    }
    free(in_queue);
    destroy_queue(&q);
}


void __print_rights(graph *base){
    for (size_t j = 0; j < base->size; j++){
        printf("%d ", base->rights[j]);
    }
    printf("\n");
}


int main(void){
    size_t N, M;
    scanf("%zu %zu", &N, &M);

    graph base; init_graph(&base, N);

    for (size_t i = 0; i < M; i++){
        int X, Y;
        scanf("%d %d", &X, &Y);
        base.add_vertex(&base, X, Y);
    }

    size_t K;
    scanf("%zu", &K);

    // chroot :)

    for (size_t i = 0; i < K; i++){
        int T, X;
        scanf("%d %d", &T, &X);

        switch (T) {
            case 1:
                promote(&base, X);
                // __print_rights(&base);
                break;
            case 2:
                demote(&base, X);
                // __print_rights(&base);
                break;
            case 3:
                promote_subjugates(&base, X);
                // __print_rights(&base);
                break;
            case 4:
                promote_down(&base, X);
                // __print_rights(&base);
                break;
            case 5:
                demote_subjugates(&base, X);
                // __print_rights(&base);
                break;
            default:
                break;
        }
    }

    for (size_t j = 0; j < N; j++){
        int right = base.rights[j] ? 1 : 0;
        printf("%d ", right);
    }

    destroy_graph(&base);
    return 0;
}

