#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define BEST_PRIMES {5, 11, 23, 47, 97, 193, 389, 769, 1543, 3079, 6161, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739}

typedef enum {WHITE, BLACK, GREY} status;

typedef struct {
    int first, second;
} pair;

typedef enum { EMPTY, OCCUPIED, DELETED } entry_state;

typedef struct set {
    size_t count;
    size_t size;
    pair *keys;
    entry_state *state;
    void (*add)(struct set *, pair);
    bool (*is_in)(struct set *, pair);
    void (*clear)(struct set *);
} set;

unsigned int next_best_prime(unsigned int current_prime){
    const unsigned int best_primes[] = BEST_PRIMES;
    size_t num_primes = sizeof best_primes / sizeof *best_primes;
    size_t left = 0, right = num_primes - 1;
    while (left < right) {
        size_t middle = (left + right) / 2;
        if (best_primes[middle] > current_prime)
            right = middle;
        else
            left = middle + 1;
    }
    if (left + 1 >= num_primes)
        return best_primes[num_primes - 1];
    return best_primes[left + 1];
}

static inline unsigned int hash_pair(pair p, unsigned int mod){
    unsigned int x = ((unsigned int)p.first) ^ (((unsigned int)p.second) << 1);
    x ^= x >> 16;
    x *= 0x85ebca6b;
    x ^= x >> 13;
    return x % mod;
}

void rehash(set *s){
    size_t old_size = s->size;
    pair *old_keys = s->keys;
    entry_state *old_st = s->state;
    unsigned int new_size = next_best_prime((unsigned int)old_size);
    pair *new_keys = malloc(new_size * sizeof *new_keys);
    entry_state *new_state = calloc(new_size, sizeof *new_state);
    if (!new_keys || !new_state) {
        free(new_keys);
        free(new_state);
        return;
    }
    s->keys = new_keys;
    s->state = new_state;
    s->size = new_size;
    s->count = 0;
    for (size_t i = 0; i < old_size; i++) {
        if (old_st[i] == OCCUPIED) {
            pair k = old_keys[i];
            unsigned int idx = hash_pair(k, new_size);
            int j = 1;
            while (s->state[idx] == OCCUPIED) {
                idx = (idx + j * j) % new_size;
                j++;
            }
            s->keys[idx] = k;
            s->state[idx] = OCCUPIED;
            s->count++;
        }
    }
    free(old_keys);
    free(old_st);
}

void add_el(set *s, pair key){
    if (s->count + 1 > (size_t)(0.75 * s->size))
        rehash(s);
    unsigned int idx = hash_pair(key, (unsigned int)s->size);
    int j = 1;
    size_t first_del = SIZE_MAX;
    while (s->state[idx] != EMPTY) {
        if (s->state[idx] == OCCUPIED &&
            s->keys[idx].first == key.first &&
            s->keys[idx].second == key.second)
            return;
        if (s->state[idx] == DELETED && first_del == SIZE_MAX)
            first_del = idx;
        idx = (idx + j * j) % (unsigned int)s->size;
        j++;
    }
    if (first_del != SIZE_MAX)
        idx = first_del;
    s->keys[idx] = key;
    s->state[idx] = OCCUPIED;
    s->count++;
}

bool contains(set *s, pair key){
    unsigned int idx = hash_pair(key, (unsigned int)s->size);
    int j = 1;
    while (s->state[idx] != EMPTY) {
        if (s->state[idx] == OCCUPIED &&
            s->keys[idx].first == key.first &&
            s->keys[idx].second == key.second)
            return true;
        idx = (idx + j * j) % (unsigned int)s->size;
        j++;
    }
    return false;
}

void clear_(set *s){
    s->count = 0;
    memset(s->state, EMPTY, s->size * sizeof *s->state);
}

void init_set(set *s, size_t sz){
    s->size = sz;
    s->count = 0;
    s->keys = malloc(sz * sizeof *s->keys);
    s->state = calloc(sz, sizeof *s->state);
    if (!s->keys || !s->state)
        printf("\033[31mMemory allocation failed in init()\033[0m\n");
    s->add = add_el;
    s->is_in = contains;
    s->clear = clear_;
}

void destroy_set(set *s){
    free(s->keys);
    free(s->state);
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

bool check(graph *gph, set *removed){
    status *colours = calloc(gph->size, sizeof(status));

    vect stk; init_vect(&stk, 4);

    stk.push_back(&stk, 1);
    colours[1-1] = GREY;

    int count = 1;

    while(stk.count){
        int curr = stk.pop_back(&stk);

        for (size_t i = 0; i < gph->vertices[curr-1].count; i++){
            int child = gph->vertices[curr-1].arr[i];
            pair edge1 = {.first = curr, .second = child};
            pair edge2 = {.first = child, .second = curr};
            if (!removed->is_in(removed, edge1) && !removed->is_in(removed, edge2)){
                if (colours[child-1] == WHITE){
                    colours[child-1] = GREY;
                    stk.push_back(&stk, child);
                    count++;
                }
            }
        }
        colours[curr-1] = BLACK;
    }

    destroy_vect(&stk);
    free(colours);

    return count == gph->size;
}

int main(void){
    size_t N, M;
    scanf("%zu %zu", &N, &M);

    graph gph; init_graph(&gph, N);

    pair *edges = malloc(M * sizeof(pair));

    for (size_t i = 0; i < M; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        gph.add_edge(&gph, u, v);
        edges[i] = (pair){.first = u, .second = v};
    }

    size_t K;
    scanf("%zu", &K);
    set removed; init_set(&removed, 8);

    for (size_t i = 0; i < K; i++){
        int C;
        scanf("%d", &C);

        for(int j = 0; j < C; j++){
            size_t idx;
            scanf("%zu", &idx);
            removed.add(&removed, edges[idx - 1]);
        }

        bool result = check(&gph, &removed);

        puts(result ? "Connected" : "Disconnected");

        removed.clear(&removed);
    }

    free(edges);
    destroy_graph(&gph);
    destroy_set(&removed);
    return 0;
}
