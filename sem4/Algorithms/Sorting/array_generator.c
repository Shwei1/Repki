#include "array_generator.h"

long *generate_array(size_t size){
    long *arr = (long *) malloc(size * sizeof(long));
    
    if (arr == NULL) {
        perror("Memory allocation failed at generate_array()");
        return NULL;
    }

    srandom((unsigned) time(NULL));
    for (size_t i = 0; i < size; ++i){
        arr[i] = random();
    }
    
    return arr;
}

