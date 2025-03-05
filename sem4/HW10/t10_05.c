#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 2048


int find_max_(int tape_length, int *CD_list, int CD_count, int CD_index, int current_tape) {

    int best_found = current_tape;

    for (int i = CD_index; i < CD_count; i++) {
        int new_tape = current_tape + CD_list[i];
        if (new_tape <= tape_length) {
            int result = find_max_(tape_length, CD_list, CD_count, i + 1, new_tape);
            if (result == tape_length) {
                return result;
            }
            if (result > best_found) {
                best_found = result;
            }
        }
    }

    return best_found;
}


void find_max(int tape_length, int *CD_list, int CD_count){
    int best_found = find_max_(tape_length, CD_list, CD_count, 0, 0);
    printf("sum:%d\n", best_found);
}

int main(void){

    char buffer[BUFFER_SIZE];

    while(fgets(buffer, BUFFER_SIZE, stdin)){

        buffer[strcspn(buffer, "\n")] = '\0';

        char *token = strtok(buffer, " ");

        int N = atoi(token);

        token = strtok(NULL, " ");

        int s = atoi(token);

        // printf("%d\n", s);

        int *arr = (int *) malloc(100 * sizeof(int));

        int i = 0;
        while ((token = strtok(NULL, " ")) != NULL && i < s) {
            arr[i++] = atoi(token);
        }

        // for (int i = 0; i < s; i++){
        //     printf("%d ", arr[i]);
        // }

        find_max(N, arr, s);

    }

    return 0;
}
