#include <stdio.h>
#include <stdlib.h>

int binary_search(int* arr, size_t size, int x){
	int l = 0;
	int r = size - 1;
	while (l <= r) {
		int m = l + (r - l)/2;
		if (arr[m] == x){
			return 1;		
		}
		else if (arr[m] < x){
			l = m + 1;
			}
		else {
			r = m - 1;		
		}

	} 
	return 0;
}



int main(){
	int n, m;
	
	scanf("%d", &n);
	
	int* collection = (int *) malloc(n * sizeof(int));
	
	for (int i = 0; i < n; ++i){
		int item;
		scanf("%d", &item);
		collection[i] = item;
	}


	scanf("%d", &m);
	
	int* desired = (int*) malloc(m * sizeof(int));
	
	for (int j = 0; j < m; ++j){
		int item;
		scanf("%d", &item);
		desired[j] = item;
	}

	for (int k = 0; k < m; k++){
		char* answer = (binary_search(collection, n, desired[k]) == 1) ? "YES" : "NO";
		printf("%s\n", answer);
	}
}
