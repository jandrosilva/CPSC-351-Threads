#include <stdlib.h> /*qsort*/
#include <stdio.h> /*printf*/
#include <pthread.h> /*POSIX threads*/
#include <unistd.h> /*sleep()*/

#include "test.h"

const int THREAD_MAX = 2;
const int VALUES[] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
const int SORTED_ARRAY[11];
int compare (const void * a, const void * b);

int main() {

  pthread_t threads[THREAD_MAX];
  // creating 2 threads to sort
  for(int i = 0; i < THREAD_MAX; i++) {
    /*pthread_create(&threads[i], NULL, func_to_be_exec, args_passed);*/
  }

  // joining the threads together
  for(int i = 0; i < THREAD_MAX; i++) {
    /*pthread_join(threads[i], NULL);*/
  }

  say_hi();



  return 0;
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
