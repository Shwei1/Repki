#include <stdio.h>
#include <stdlib.h>

int binary_left(int* arr, size_t size, int x){
	int l = 0;
	int r = size - 1;
	int result = -1;
	while (l <= r){
		int m = l + (r-l)/2;
		if (arr[m] == x){
			result = m;
			r = m-1;	
		} 
		else if (arr[m] > x){
			r = m-1;
		}
		else {
			l = m + 1;
		}
	}
	return result;
}


int binary_right(int* arr, size_t size, int x){
	int l = 0;
	int r = size - 1;
	int result = -1;
	while (l <= r){
		int m = l + (r-l)/2;
		if (arr[m] == x){
			result = m;
			l = m+1;	
		} 
		else if (arr[m] > x){
			r = m-1;
		}
		else {
			l = m + 1;
		}
	}
	return result;
}

int count_inclusions(int* arr, size_t size, int x){
	int first = binary_left(arr, size, x);
	int last = binary_right(arr, size, x);
	if (first == -1 || last == -1) return 0;
	return last - first + 1;
}





int main(){
	int n, m;

	scanf("%d", &n);
	
	int* colours = (int*) malloc(n * sizeof(int));
	
	for (int i = 0; i < n; i++){
		int colour;
		scanf("%d", &colour);
		colours[i] = colour;
	}
	
	scanf("%d", &m);
	
	int* desired = (int*) malloc(m * sizeof(int));
	
	for (int j = 0; j < m; j++){
		int colour;
		scanf("%d", &colour);
		desired[j] = colour;
	}

	for (int k = 0; k < m; k++){
		int count = count_inclusions(colours, n, desired[k]);
		printf("%d\n", count);
	}
	

	free(colours);
	free(desired);
	
	return 0;
}
