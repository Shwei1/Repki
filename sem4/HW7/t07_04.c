#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DELETED ((char*) -1)
#define PLACEHOLDER "PLACEHOLDER"
#define PRESENT "PRESENT"
#define BEST_PRIMES {5, 11, 23, 47, 97, 193, 389, 769, 1543, 3079, 6161, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739}
#define OKAYANSWER "Everything is going to be OK."
#define UNKNOWNANSWER "Some words from the text are unknown."
#define NOTPERFECTANSWER "The usage of the vocabulary is not perfect."
#define WORDSIZE 20


typedef struct {

    size_t count;
    size_t size;

    char** keys;
    char** values;

} table;


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


void init(table* hashtable, size_t size){
    hashtable->size = size;
    hashtable->count = 0;
    hashtable->keys = (char**) malloc(size * sizeof(char*));
    hashtable->values = (char**) malloc(size * sizeof(char*));
    if (hashtable->keys == NULL || hashtable->values == NULL) {
        printf("\033[31mMemory allocation failed in init()\033[0m\n");
        return;  
    }
    for (int i = 0; i < size; i++){
        hashtable->keys[i] = NULL;
        hashtable->values[i] = NULL;
    }
    return;
}


void destroy(table* hashtable){
    for (int i = 0; i < hashtable->size; ++i){
        if (hashtable->keys[i] != NULL && hashtable->keys[i] != DELETED)
            free(hashtable->keys[i]);
        if (hashtable->values[i] != NULL) 
            free(hashtable->values[i]);
    }
    free(hashtable->keys);
    free(hashtable->values);
}


unsigned int hash(char* str, unsigned int prime_base){
    unsigned int result = 0;
    unsigned int length = strlen(str);
    for (int i = 0; i < length; ++i){
        result += (unsigned int)str[i] * i;
    }

    return result % prime_base;
}


void rehash(table* hashtable){
    size_t old_size = hashtable->size;

    hashtable->size = next_best_prime(hashtable->size);

    char** new_keys = (char**)malloc(hashtable->size * sizeof(char*));
    char** new_values = (char**) malloc(hashtable->size * sizeof(char*));

    if (new_keys == NULL || new_values == NULL){
        printf("\033[33mMemory allocation failed at rehash().\033[0m\n");
        return;
    }

    for (unsigned int i = 0; i < hashtable->size; ++i){
        new_keys[i] = NULL;
        new_values[i] = NULL;
    }

    for (unsigned int i = 0; i < old_size; ++i){
        if (hashtable->keys[i] != NULL && hashtable->keys[i] != DELETED){
            
            unsigned int index = hash(hashtable->keys[i], hashtable->size);
            
            if (new_keys[index] != NULL) {
                int j = 1;
                do {
                    index = (index + j * j) % hashtable->size;
                    j++;
                } while (new_keys[index] != NULL);
             
            }
            new_keys[index] = hashtable->keys[i];
            new_values[index] = hashtable->values[i];
        }
    } 

    free(hashtable->keys);
    free(hashtable->values);

    hashtable->keys = new_keys;
    hashtable->values = new_values;

    return;
}


void add_pair(table* hashtable, char* key, char* value){
    
    if(hashtable->count > 0.75 * hashtable->size){ rehash(hashtable); }

    size_t keysize = strlen(key);
    size_t valuesize = strlen(value);
    
    unsigned int index = hash(key, hashtable->size);
    
    if (hashtable->keys[index] != NULL && hashtable->keys[index] != DELETED && strcmp(hashtable->keys[index], key) == 0){
        free(hashtable->values[index]);
        hashtable->values[index] = (char*) malloc(valuesize * sizeof(char) + 1);
        
        if (hashtable->values[index] == NULL) {
            printf("\033[33mMemory allocation failed at add_pair.\033[0m\n");
            return;
         }

        strcpy(hashtable->values[index], value);
        return;
    }

    if (hashtable->keys[index] == NULL || hashtable->keys[index] == DELETED){
        
        hashtable->values[index] = (char*) malloc(valuesize * sizeof(char) + 1);
        hashtable->keys[index] = (char*) malloc(keysize * sizeof(char) + 1);
        
        if (hashtable->keys[index] == NULL || hashtable->values[index] == NULL) {
            printf("\033[33mMemory allocation failed at add_pair.\033[0m\n"); 
            return;
        }

        strcpy(hashtable->keys[index], key);
        strcpy(hashtable->values[index], value);
        hashtable->count++;
    }
    else {

        int i = 1;

        do {
            if (strcmp(hashtable->keys[index], key) == 0){
                free(hashtable->values[index]);
                hashtable->values[index] = (char*) malloc(valuesize * sizeof(char) + 1);
                if (hashtable->values[index] == NULL) {
                    printf("\033[33mMemory allocation failed at add_pair.\033[0m\n");
                    return;
                }
                strcpy(hashtable->values[index], value);
                return;
            }
            index = (index + i * i) % hashtable->size;
            i++;
        } while (hashtable->keys[index] != NULL && hashtable->keys[index] != DELETED);
        
        hashtable->keys[index] = (char*) malloc(keysize * sizeof(char) + 1);
        hashtable->values[index] = (char*) malloc(valuesize * sizeof(char) + 1);
        
        if (hashtable->keys[index] == NULL || hashtable->values[index] == NULL) {
            printf("\033[33mMemory allocation failed at add_pair.\033[0m\n");
            return;
        }

            strcpy(hashtable->keys[index], key);
            strcpy(hashtable->values[index], value);
            hashtable->count++;
    }

    return;
}

char* get_value(table* hashtable, char* key){
    unsigned int index = hash(key, hashtable->size);
    
    int i = 1;

    do {
        if (hashtable->keys[index] != NULL && hashtable->keys[index] != DELETED && strcmp(hashtable->keys[index], key) == 0){
                    return hashtable->values[index];
                }
        index = (index + i * i) % hashtable->size;
        i++;
    } while(hashtable->keys[index] != NULL); 

    return NULL;
}  

void del_key(table* hashtable, char* key){
    unsigned int index = hash(key, hashtable->size);
    
    int i = 1;

    do {
        if (hashtable->keys[index] != NULL && hashtable->keys[index] != DELETED && strcmp(key, hashtable->keys[index]) == 0){
            free(hashtable->keys[index]);
            free(hashtable->values[index]);
            hashtable->keys[index] = DELETED;
            hashtable->values[index] = NULL;
            hashtable->count--;
            return;
        }
        index = (index + i * i) % hashtable->size;
        i++;

    } while(hashtable->keys[index] != NULL);

    return;
}


int main(void){

    const char punct[] = " .,:;'\"-!?";

    int N, M;

    scanf("%d %d", &N, &M);

    table dict;
    init(&dict, 389);

    for (int i = 0; i < N; i++){
        char buffer[WORDSIZE + 1];
        scanf("%20s", buffer);
        add_pair(&dict, buffer, PLACEHOLDER);
    }

    getchar();

    for (int j = 0; j < M; j++){
        char buffer[4096];
        if (fgets(buffer, 4096, stdin) == NULL) {
            break;  
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        char* token = strtok(buffer, punct);

        while(token != NULL){
            for (int j = 0; token[j] != '\0'; j++) {
                token[j] = tolower((unsigned char)token[j]);
            }

            if (get_value(&dict, token)){
                add_pair(&dict, token, PRESENT);
            }
            else {
                printf(UNKNOWNANSWER);
                destroy(&dict);
                return 0;
            }

            token = strtok(NULL, punct);
        }

    }

    for (int i = 0; i < dict.size; i++){
        if(dict.values[i] != NULL && strcmp(dict.values[i], PLACEHOLDER) == 0){
             printf(NOTPERFECTANSWER);
             destroy(&dict);
             return 0;
        }
    }

    printf(OKAYANSWER);
    destroy(&dict);
    return 0;
}
