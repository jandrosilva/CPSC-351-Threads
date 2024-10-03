#include <stdlib.h> /*qsort*/
#include <stdio.h> /*printf*/
#include <pthread.h> /*POSIX threads*/
#include <unistd.h> /*sleep()*/
#include <stdint.h>
#include <string.h>

#include "sort.h"


typedef struct {

  int* arr;
  int size;

} Array;

void* func(void* arg) {
  pthread_detach(pthread_self());

  int seconds = (int)(intptr_t)arg;
  printf("Thread will wait for %d seconds.\n", seconds);
  sleep(seconds);
  puts("Thread ending");

  pthread_exit(NULL);
}

void* thread_sort(void* arg) {
  pthread_detach(pthread_self());

  Array* arr_struct = (Array*)arg;

  sort(arr_struct->arr, arr_struct->size);

  pthread_exit(NULL);
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

#define SIZE 11


int main(void) {
  int array[SIZE] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};

  int* first_half;
  int* second_half;
  int first_size, second_size;

  printf("Original array: ");
  disp_array(array, SIZE);

  split_array(array, SIZE, &first_half, &first_size, &second_half, &second_size);

  printf("Left array: ");
  disp_array(first_half, first_size);
  printf("Right array: ");
  disp_array(second_half, second_size);


  pthread_t ptid1, ptid2;

  Array arr1, arr2;
  arr1.arr = first_half;
  arr1.size = first_size;

  arr2.arr = second_half;
  arr2.size = second_size;

  pthread_create(&ptid1, NULL, &thread_sort, (void*)&arr1);
  pthread_create(&ptid2, NULL, &thread_sort, (void*)&arr2);

  pthread_join(ptid1, NULL);
  pthread_join(ptid2, NULL);

  printf("Sorted left: ");
  disp_array(first_half, first_size);
  printf("Sorted right: ");
  disp_array(second_half, second_size);

  putchar('\n');

  int* result = merge_arrays(first_half, first_size, second_half, second_size);

  // this should really use merge sort
  sort(result, SIZE);

  disp_array(result, SIZE);

  pthread_exit(NULL);


  return 0;
}
