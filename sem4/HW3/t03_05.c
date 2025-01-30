#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_INPUT_SIZE 100000

int yield_accepted(int* heights, int desired[2], int amount){
	int count = 0;
	for (int i = 0; i < amount; ++i){
		if (heights[i] >= desired[0] && heights[i] <= desired[1])
			count += 1;
	}

	return count;
}




int main(){
	int count_entrances = 0;
	int* entrances = (int *) malloc(2 * sizeof(int));
	int capacity = 2;
	int amount;
	int desired[2];
	char buffer[MAX_INPUT_SIZE];

	while (1) {
	if (!fgets(buffer, sizeof(buffer), stdin)) break;
	if (buffer[0] == '\n') break;
	amount = atoi(buffer);
	
	int* heights = (int *) malloc(amount * sizeof(int));
	
	fgets(buffer, sizeof(buffer), stdin);
	char *token = strtok(buffer, " ");
	
	for (int i = 0; i < amount && token != NULL; i++){
		heights[i] = atoi(token);
            	token = strtok(NULL, " ");
	}

	fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d %d", &desired[0], &desired[1]);
	
	int entrance = yield_accepted(heights, desired, amount);
	entrances[count_entrances++] = entrance;
	if (count_entrances >= capacity){
		capacity *= 2;
		int *temp = realloc(entrances, capacity * sizeof(int));
		entrances = temp;
	}
	free(heights);
	}
	
	for (int i = 0; i < count_entrances; i++){
		printf("%d\n", entrances[i]);
	}
	free(entrances);
	

}
