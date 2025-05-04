#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

static inline int fast_int(void) {
  int c = getchar_unlocked(), x = 0;
  while (c < '0') c = getchar_unlocked();
  for (; c >= '0'; c = getchar_unlocked())
    x = x*10 + (c - '0');
  return x;
}

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
    vect *vertices;
    bool *is_op;
    bool *rights;
    bool *sharing;
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
        init_vect(&self->vertices[i], 4);
    }
    self->add_vertex = add_vertex_;
    self->is_op = calloc(n, sizeof(bool));
    self->rights = calloc(n, sizeof(bool));
    self->sharing = calloc(n, sizeof(bool));
}

void destroy_graph(graph *self){
    for (size_t i = 0; i < self->size; i++){
        destroy_vect(&self->vertices[i]);
    }
    free(self->vertices);
    free(self->is_op);
    free(self->sharing);
    free(self->rights);
}

void promote(graph *base, int user_id){
    base->is_op[user_id-1] = true;
}

void demote(graph *base, int user_id){
    base->is_op[user_id-1] = false;
}

void promote_subjugates(graph *base, int user_id){
    base->sharing[user_id-1] = true;
}

void promote_down(graph *base, int user_id){
    base->sharing[user_id-1] = true;
    vect stk; init_vect(&stk, base->size / 2);
    bool *visited = calloc(base->size, sizeof(bool));
    stk.push_back(&stk, user_id);
    visited[user_id-1] = true;

    while (stk.count){
        int curr = stk.pop_back(&stk);

        for (size_t i = 0; i < base->vertices[curr-1].count; i++){
            int subjugate = base->vertices[curr-1].arr[i];
            if (!visited[subjugate-1]){
                visited[subjugate-1] = true;
                base->sharing[subjugate-1] = true;
                stk.push_back(&stk, subjugate);
            }
        }
    }

    destroy_vect(&stk);
    free(visited);
}

void demote_subjugates(graph *base, int user_id){
    base->sharing[user_id-1] = false;
}

void determine_rights(graph *base){
    queue q; init_queue(&q, base->size);
    bool *in_queue = calloc(base->size, sizeof(bool));

    for (size_t i = 0; i < base->size; i++){
        if (base->is_op[i]){
            q.push_back(&q, i+1);
            base->rights[i] = true;
            in_queue[i] = true;
        }
    }

    while (q.count){
        int curr = q.pop_front(&q);

        if (!base->sharing[curr-1])
            continue;

        if (base->rights[curr-1]){
            for (size_t j = 0; j < base->vertices[curr-1].count; j++){
                int subjugate = base->vertices[curr-1].arr[j];
                if (!in_queue[subjugate - 1]){
                    base->rights[subjugate - 1] = true;
                    q.push_back(&q, subjugate);
                    in_queue[subjugate-1] = true;
                }
            }
        }
    }
    free(in_queue);
    destroy_queue(&q);
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

    for (size_t i = 0; i < K; i++){
        int T = fast_int();
        int X = fast_int();
        // scanf("%d %d", &T, &X);

        switch (T) {
            case 1:
                promote(&base, X);
                break;
            case 2:
                demote(&base, X);
                break;
            case 3:
                promote_subjugates(&base, X);
                break;
            case 4:
                promote_down(&base, X);
                break;
            case 5:
                demote_subjugates(&base, X);
                break;
            default:
                break;
        }
    }

    determine_rights(&base);

    for (size_t j = 0; j < N; j++){
        int right = base.rights[j];
        printf("%d ", right);
    }

    destroy_graph(&base);
    return 0;
}
