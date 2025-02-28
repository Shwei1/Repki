#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void merge(long* arr, long* aux, size_t left, size_t mid, size_t right);
void merge_sort_(long *arr, long* aux, size_t left, size_t right);
void merge_sort(long *arr, size_t size);

#endif /* MERGE_SORT_H */

