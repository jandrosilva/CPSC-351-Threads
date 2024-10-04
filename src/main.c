/*
 * CSPSC 351 Group Project 2
 * Date began: 9/30/24
 * Due date: 10/9/24
 * Authors: Joshua Holman, Cameron Rosenthal, Noah Scott, Alejandro Silva
 * 
 * This program: Threads
 *     Sorts an array using merge sort and threads
 *
 * This file:  main.c
 */
#include <stdlib.h> /*qsort*/
#include <stdio.h> /*printf*/
#include <pthread.h> /*POSIX threads*/
#include <unistd.h> /*sleep()*/
#include <string.h>

#include "sort.h"

/* Wrapper for pthread_create for error checking purposes */
int create_thread(pthread_t* thread, void* (*start_routine) (void*), void* arg);

/* Takes Array type as arg and sorts array in place in a spawned thread */
void* thread_sort(void* arg);

typedef struct {
  int* arr;
  int size;
} Array;

#define SIZE 11


int main(void) {
  int array[SIZE] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};

  printf("Original array: ");
  disp_array(array, SIZE);

  // split array in half and send each to half to a thread to be merge sorted

  Array arr1, arr2;
  split_array(array, SIZE, &arr1.arr, &arr1.size, &arr2.arr, &arr2.size);

  printf("Left array: ");
  disp_array(arr1.arr, arr1.size);
  printf("Right array: ");
  disp_array(arr2.arr, arr2.size);

  pthread_t ptid1, ptid2;

  if (create_thread(&ptid1, &thread_sort, (void*)&arr1) != 0) {
    free(arr1.arr);
    free(arr2.arr);
    return 1;
  }
  if (create_thread(&ptid2, &thread_sort, (void*)&arr2) != 0) {
    free(arr1.arr);
    free(arr2.arr);
    return 1;
  }

  pthread_join(ptid1, NULL);
  pthread_join(ptid2, NULL);

  // threads are done, time to output and merge the two sorted halves

  printf("\nSorted left: ");
  disp_array(arr1.arr, arr1.size);
  printf("Sorted right: ");
  disp_array(arr2.arr, arr2.size);
  putchar('\n');

  int* result = combine_arrays(arr1.arr, arr1.size, arr2.arr, arr2.size);

  free(arr1.arr);
  free(arr2.arr);

  printf("After combining: ");
  disp_array(result, SIZE);

  merge(result, 0, arr1.size - 1, SIZE - 1);

  printf("After merging two sorted halves: ");
  disp_array(result, SIZE);

  free(result);
  return 0;
}

int create_thread(pthread_t* thread, void* (*start_routine) (void*), void* arg) {
  int ret = pthread_create(thread, NULL, start_routine, arg);
  if (ret != 0) {
    fprintf(stderr, "Error creating thread: %d\n", ret);
    return -1;
  }
  return 0;
}

void* thread_sort(void* arg) {
  pthread_detach(pthread_self());
  Array* arr_struct = (Array*)arg;
  merge_sort(arr_struct->arr, 0, arr_struct->size - 1);
  pthread_exit(NULL);
}

