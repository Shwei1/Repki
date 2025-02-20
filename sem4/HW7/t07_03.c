#include <stdio.h>
#include <stdlib.h>

#define BEST_PRIMES {5, 11, 23, 47, 97, 193, 389, 769, 1543, 3079, 6161, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739}

typedef struct {
    size_t count;
    size_t size;

    int* keys;
} set;

unsigned int next_best_prime(unsigned int current_prime){
    const unsigned int best_primes[] = BEST_PRIMES;
    size_t left = 0;
    size_t right = sizeof best_primes / sizeof(unsigned int) - 1;
    while(left < right){
        size_t middle = (left + right) / 2;
        if(best_primes[middle] > current_prime)
            right = middle;
        else
            left = middle + 1;
    }

    return best_primes[left + 1];
}


void init(set* hashset, size_t size){
    hashset->size = size;
    hashset->count = 0;
    hashset->keys = (int*) calloc(size, sizeof(int));
    if (hashset->keys == NULL){
        printf("Memory allocation failed at init.\n");
        return;
    }
    return;
}    

void destroy(set* hashtable){
    free(hashtable->keys);
    return;
}

unsigned int hash(int key, unsigned int prime_base){
    const unsigned int A = 2654435769u;
    return (key * A) % prime_base;
}

void rehash(set* hashset){
    size_t old_size = hashset->size;
    
    hashset->size = next_best_prime(old_size);
    int* new_keys = (int*) calloc(hashset->size, sizeof(int));
    
    if(new_keys == NULL){
        printf("Memory allocation failed at rehash.\n");
        return;
    }
    
    for (int i = 0; i < old_size; i++){
        if (hashset->keys[i] != 0 && hashset->keys[i] != -1){
            
            unsigned int index = hash(hashset->keys[i], hashset->size);
            
            if (new_keys[index] != 0){
                int j = 1;
                do {
                    index = (index + j * j) % hashset->size;
                    j++;
                } while (new_keys[index] != 0 && new_keys[index] != -1);
            
            }
            new_keys[index] = hashset->keys[i];
        }
    }
    
    free(hashset->keys);
    hashset->keys = new_keys;
}


void add_el(set* hashset, int key){
    
    if (hashset->count > 0.75 * hashset -> size){ rehash(hashset); }

    unsigned int index = hash(key, hashset->size);

    if (hashset->keys[index] != 0 && hashset->keys[index] != -1 && hashset->keys[index] == key){
        return; 
    }

    if (hashset->keys[index] == 0 || hashset->keys[index] == -1){
        hashset->keys[index] = key;
        hashset->count++;
        return;
    }
    else {
        unsigned int i = 1;
        do {
            if (hashset->keys[index] == key){
                return; 
                
            }
            index = (index + i * i) % hashset->size;
            i++;
        } while (hashset->keys[index] != 0 && hashset->keys[index] != -1);
        
        hashset->keys[index] = key;
        hashset->count++;
    }

    return;
}

void del_key(set* hashset, int key){
    unsigned int index = hash(key, hashset->size);

    unsigned int i = 1;
    
    do {
        if (hashset->keys[index] != 0 && hashset->keys[index] != -1 && hashset->keys[index] == key){
            hashset->keys[index] = -1;
            hashset->count--;
        }
        index = (index + i * i) % hashset->size;
        i++;
    } while(hashset->keys[index] != 0);

    return;
}

int main(void){
    set contact_book;
    
    init(&contact_book, 5);

    int N;
    scanf("%d", &N);
    
    int* phone_numbers = (int*) malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i){
        scanf("%d", &phone_numbers[i]);
        add_el(&contact_book, phone_numbers[i]);
    }

    free(phone_numbers);

    printf("%d", contact_book.count);

    destroy(&contact_book);
    return 0;
}

