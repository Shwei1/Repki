#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void int_to_str(char* str, uint32_t number){
	size_t index = 0;
	size_t bitsize = sizeof(int) * CHAR_BIT;
	size_t significant;
	if (number == 0){
			str[0] = '0';
			str[1] = '\0';
			return;
		}
	for (int i = bitsize-1; i >= 0; i--){
		if (number & (1 << i)){
				significant = i;
				break;
			}
		}
	for (int j = significant; j >= 0; j--){
		str[index++] = (number & (1 << j)) ? '1': '0';
		}

	str[index] = '\0';
	return;
}

uint32_t str_to_int(char* str, size_t size){
	uint32_t result = 0;
	for (int i = 0; i < size; i++){
		if(str[i] == '1')
			result += (1 << (size - 1 - i));
		else
			continue;
	}
	return result;
}

size_t len(char* str){
	size_t size = 0;
	while (str[size] != '\0'){
		size++;
	}
	return size;
}


void permute(uint32_t* values, char* str){
	size_t size = len(str);
	for (int i = 0; i < size; i++){
		char first = str[0];
		memmove(str, str+1, size-1);
		str[size-1] = first;
		str[size] = '\0';
		uint32_t num = str_to_int(str, size);
		values[i] = num;
	}
}

void print_largest_permutation(uint32_t* values, size_t size){
	uint32_t largest = values[0];
	for (int i = 1; i < size; i++){
		if (values[i] > largest){
			largest = values[i];
		}
	}
	printf("%u\n", largest);
}

int main(){

	uint32_t number;
	char binary_str[33];
 	//printf("Enter your number: ");
	//fflush(stdout);	
	scanf("%u", &number);
	int_to_str(binary_str, number);
	uint32_t* values = (uint32_t *) malloc(number * sizeof(uint32_t));
	permute(values, binary_str);
	print_largest_permutation(values, number);	
	free(values);
	//printf("%s\n", binary_str); 

	return 0;




}
