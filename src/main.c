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

  merge_sort(result, 0, SIZE - 1);
  disp_array(result, SIZE);

  return 0;
}

void* thread_sort(void* arg) {
  pthread_detach(pthread_self());
  Array* arr_struct = (Array*)arg;
  merge_sort(arr_struct->arr, 0, arr_struct->size - 1);
  pthread_exit(NULL);
}

