#include <stdlib.h> /*qsort*/
#include <stdio.h> /*printf*/
#include <pthread.h> /*POSIX threads*/
#include <unistd.h> /*sleep()*/
#include <string.h>

#include "sort.h"

/*
 * Takes Array struct as arg and sorts array in place
 */
void* thread_sort(void* arg);

typedef struct {
  int* arr;
  int size;
} Array;

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

void* thread_sort(void* arg) {
  pthread_detach(pthread_self());

  Array* arr_struct = (Array*)arg;

  sort(arr_struct->arr, arr_struct->size);

  pthread_exit(NULL);
}

