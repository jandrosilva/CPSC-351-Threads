#ifndef SORT_H
#define SORT_H

#include "stdlib.h"

void merge(int* arr, int left, int mid, int right);
void merge_sort(int*, int, int);

void split_array(int*, int, int**, int*, int**, int*);

void disp_array(int*, int);

int* combine_arrays(int*, int, int*, int);

void* safe_malloc(size_t);

#endif
