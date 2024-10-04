#include "sort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void merge(int* arr, int left, int mid, int right) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int leftArr[n1], rightArr[n2];

  for (i = 0; i < n1; i++)
    leftArr[i] = arr[left + i];
  for (j = 0; j < n2; j++)
    rightArr[j] = arr[mid + 1 + j];

  i = 0;
  j = 0;
  k = left;

  while(i < n1 && j < n2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    }
    else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }
}

void merge_sort(int* arr, int left, int right) {
  if (left < right) {

    int mid = left + (right - left) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, mid, right);
  }
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

int* combine_arrays(int* arr1, int size1, int* arr2, int size2) {
  int *result = (int*)malloc(sizeof(int) * size1 * size2);

  memcpy(result, arr1, size1 * sizeof(int));
  memcpy(result + size1, arr2, size2 * sizeof(int));

  return result;
}
