#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct minheap{
    long *arr;
    size_t count;
    size_t size;
} minheap;

void init(minheap *self, size_t n){
    self->size = n+1;
    self->count = 0;
    self->arr = malloc(self->size * sizeof(long));
}

void destroy(minheap *self){
    free(self->arr);
}

void push(minheap *self, long n){
    size_t idx = ++self->count;
    self->arr[idx] = n;

    while (idx > 1){
        size_t parent = idx / 2;
        if (self->arr[idx] < self->arr[parent]) {

            self->arr[idx] ^= self->arr[parent];
                self->arr[parent] ^= self->arr[idx];
                    self->arr[idx] ^= self->arr[parent];

            idx = parent;
        }
        else 
            break;
    }
}

long pop(minheap *self){
    long top = self->arr[1];

    self->arr[1] = self->arr[self->count--];

    size_t idx = 1;
    while (true){
        size_t left = 2 * idx;
        size_t right = left + 1;
        size_t min = idx;

        if (left <= self->count && self->arr[min] > self->arr[left]) min = left;
        if (right <= self->count && self->arr[min] > self->arr[right]) min = right;

        if (min != idx){
            self->arr[min] ^= self->arr[idx];
                self->arr[idx] ^= self->arr[min];
                    self->arr[min] ^= self->arr[idx];
            idx = min;
        }
        else
            break;

    }

    return top;
}

long find_best(minheap *h){
    long result = 0;

    while (h->count > 1){

        long v1 = pop(h);
        long v2 = pop(h);
        long c = v1 + v2;

        result += c;
        push(h, c);
    }

    return result;
}

int main() {
    size_t n;
    scanf("%zu", &n);
    minheap h;
    init(&h, n);

    for (size_t i = 0; i < n; i++){
        long val;
        scanf("%ld", &val);
        push(&h, val);
    }

    printf("%ld\n", find_best(&h));

    destroy(&h);
    return 0;
}

