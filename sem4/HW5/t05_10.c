#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void generate_prefix_sums(long* arr, long size, long* prefices_arr){
    long sum = 0;
    for (long i = 0; i < size; i++){
        sum += arr[i];
        prefices_arr[i] = sum;
    }
}

long evaluate(long start, long finish, long median, long* field_coordinates, long field_count, long* prefix_sums){
    long cost_left = 0;
    long cost_right = 0;
    long left_count = median - start;
    
    if (left_count > 0){
        long left_sum;
        if (start == 0)
            left_sum = prefix_sums[median-1];
        else
            left_sum = prefix_sums[median - 1] - prefix_sums[start - 1];
        cost_left = field_coordinates[median] * left_count - left_sum;
    }
    long right_count = finish - median;
    if (right_count > 0) {
        long right_sum = prefix_sums[finish] - prefix_sums[median];
        cost_right = right_sum - field_coordinates[median] * right_count;
    }
    return cost_left + cost_right;
}


bool satisfiable(long middle, long* field_coordinates, long field_count, long* prefix_sums, long budget){
    for (long start = 0; start <= field_count - middle; start++){
        long finish = start + middle - 1;
        long median = start + (middle - 1)/2;
        long cost = evaluate(start, finish, median, field_coordinates, field_count, prefix_sums);
        if (cost <= budget)
            return true;
    }
    return false;
}


long binary_search(long* field_coordinates, long field_count, long* prefix_sums, long budget){
    long left = 1;
    long right = field_count;
    while(left < right){
        long middle = (left + right) / 2;
        if (satisfiable(middle, field_coordinates, field_count, prefix_sums, budget))
            left = middle + 1;
        else
            right = middle - 1;
    }

    return right; 
}

int main(void){
    
    long field_count, last_element, budget;
    scanf("%ld %ld %ld", &field_count, &last_element, &budget);
    
    long* field_coordinates = (long*)malloc(field_count * sizeof(long));

    for (int i = 0; i < field_count; ++i){
        long item;
        scanf("%ld", &item);
        field_coordinates[i] = item;
    } 
    
    long* prefix_sums = (long*)malloc(field_count * sizeof(long));

    generate_prefix_sums(field_coordinates, field_count, prefix_sums);
    
    long answer = binary_search(field_coordinates, field_count, prefix_sums, budget);
    
    printf("%ld\n", answer);

    free(field_coordinates);
    free(prefix_sums);

    return 0;
}
