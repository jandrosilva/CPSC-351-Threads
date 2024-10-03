#include "sort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int compare(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

void sort(int* arr, int size) {
  qsort(arr, size, sizeof(int), compare);
}

void split_array(int* arr, int size, int** first_half, int *first_size, int** second_half,  int *second_size) {
  *first_size = size / 2;
  *second_size = size - *first_size;

  *first_half = (int*)calloc(*first_size, sizeof(int));
  *second_half = (int*)calloc(*second_size, sizeof(int));

  printf("first_size: %d, second_size: %d\n", *first_size, *second_size);

  memcpy(*first_half, arr, *first_size * sizeof(int));
  memcpy(*second_half, arr + *first_size, *second_size * sizeof(int));
}


void disp_array(int* array, int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d ", array[i]);
  }
  putchar('\n');
}

int* merge_arrays(int* arr1, int size1, int* arr2, int size2) {
  int *result = (int*)malloc(sizeof(int) * size1 * size2);

  memcpy(result, arr1, size1 * sizeof(int));
  memcpy(result + size1, arr2, size2 * sizeof(int));

  return result;
}
