#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFERSIZE 25600

typedef struct {
    long *indices[96];
    long char_counts[96];
} table;

void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void count_chars(const char *str, long dissection[96]) {
    for (; *str != '\0'; str++) {
        unsigned char c = *str;
        if (c >= ' ' && c <= (unsigned char) 0b01111111) {
            dissection[c - ' ']++;
        }
    }
    return;
}

long binary_search(table *tbl, char c, long current_index){
    long index = c - ' ';
    long* arr = tbl->indices[index];
    long size = tbl->char_counts[index];

    long left = 0;
    long right = size - 1;

    long result = -1;

    while(left <= right){
        long middle = left + (right - left)/2;
        if (arr[middle] > current_index) {
            result = arr[middle];
            right = middle - 1;
        }
        else
            left = middle + 1;
    }
    return result;

}

void init(table* tbl, long char_counts[96]){
    for (long i = 0; i < 96; ++i){
        long amount = char_counts[i];

        if (amount > 0)
            tbl->indices[i] = (long *) malloc(amount * sizeof(long));
        else
            tbl->indices[i] = NULL;
    }
    memset(tbl->char_counts, 0, sizeof tbl->char_counts);
    return;
}

void destroy(table* tbl){
    for (long i = 0; i < 96; i++){
        free(tbl->indices[i]);
    }
}


int main(void){
    table my_table;

    long n;
    scanf("%ld", &n);
    getchar();

    char **words = (char**) malloc(n * sizeof(char*));
    char temp[BUFFERSIZE];
    for (long i = 0; i < n; i++){
        fgets(temp, BUFFERSIZE, stdin);
        size_t len = strlen(temp);
        remove_newline(temp);

        words[i] = (char*) malloc((len + 1) * sizeof(char));
        strcpy(words[i], temp);
    }


    char *T = (char*) malloc(1048576 * sizeof(char));
    fgets(T, 1048576, stdin);
    remove_newline(T);

    long T_counts[96] = {0};
    count_chars(T, T_counts);

init(&my_table, T_counts);
 

    char* tptr = T;
    long pos = 0;
    while(*tptr != '\0'){
        long current_index = (long)*tptr - ' ';
        my_table.indices[current_index][my_table.char_counts[current_index]] = pos;
        my_table.char_counts[current_index]++;
        tptr++;
        pos++;
    }
    

    long best_prefix = -1; 

    for (long i = 0; i < n; i++){

        bool found = true;
        long current_index = -1;

        for (char* p = words[i]; *p != '\0' && found; p++){
            long new_index = binary_search(&my_table, *p, current_index);

            if (new_index == -1)
                found = false;
            else
                current_index = new_index;
        }
        if (found){
            long prefix_length = current_index + 1;
        if (prefix_length < best_prefix || best_prefix == -1)
            best_prefix = prefix_length;
        }
    }

    if (best_prefix == -1) {
        printf("NO");
    } 
    else {
        printf("YES %ld", best_prefix);
    }

    for (int i = 0; i < n; i++){
        free(words[i]);
    }

free(words);
free(T);
destroy(&my_table);
}
