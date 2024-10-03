#include <bits/types/clockid_t.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

struct thread_args
{
    int* array;
    int begin;
    int end;
};

void mergeArray(int* array, int center_index, int array_size)
{
    int* temp = (int*)malloc(array_size * sizeof(int));
    int i = 0;
    int j = center_index;
    int k = 0;

    while (i < center_index && j < array_size)
    {
        if (array[i] < array[j])
        {
            temp[k++] = array[i++];
        }
        else
        {
            temp[k++] = array[j++];
        }
    }

    while (i < center_index)
    {
        temp[k++] = array[i++];
    }

    while (j < array_size)
    {
        temp[k++] = array[j++];
    }

    for (int i = 0; i < array_size; i++)
    {
        array[i] = temp[i];
    }

    free(temp);
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void* sorting_thread(void* arg)
{
    int begin = ((struct thread_args*)arg)->begin;
    int end = ((struct thread_args*)arg)->end;
    
    int array_size = end - begin + 1;
    
    // Take the original array and move the pointer to the proper begin position.
    int* array = ((struct thread_args*)arg)->array + begin;

    qsort(array, array_size, sizeof(int), compare);

    pthread_exit(NULL);
}

int get_random_num(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main()
{
    const int ARRAY_SIZE = 1000000;
    const int MAX_INT = 1000;
    const int MIN_INT = 0;
    
    int my_array[ARRAY_SIZE];
    int my_array_2[ARRAY_SIZE];

    pthread_t thread_1_id;
    pthread_t thread_2_id;

    struct thread_args t_args_1;
    struct thread_args t_args_2;

    // Populate array with random values between MIN_INT and MAX_INT inclusive.
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        int rand_int = get_random_num(MIN_INT, MAX_INT);
        my_array[i] = rand_int;
        my_array_2[i] = rand_int;
    }

    int center_index = ARRAY_SIZE / 2; // Integer division takes care of odd.

    t_args_1.array = &my_array;
    t_args_1.begin = 0;
    t_args_1.end = center_index - 1;

    t_args_2.array = &my_array;
    t_args_2.begin = center_index;
    t_args_2.end = ARRAY_SIZE - 1;
    
    // Thread for each half of array.

    // measure performance

    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_create(&thread_1_id, NULL, &sorting_thread, (void*)&t_args_1); 
    pthread_create(&thread_2_id, NULL, &sorting_thread, (void*)&t_args_2); 

    pthread_join(thread_1_id, NULL); 
    pthread_join(thread_2_id, NULL); 

    // Sort two side into one.
    mergeArray(&my_array, center_index, ARRAY_SIZE);

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Time elapsed threaded: %f\n", elapsed);

    // Sort my_array_2 for comparison.
    clock_gettime(CLOCK_MONOTONIC, &start);

    // merge sort
    qsort(my_array_2, ARRAY_SIZE, sizeof(int), compare);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("Time elapsed for qsort: %f\n", elapsed);


    // for (int i = 0; i < ARRAY_SIZE; i++)
    // {
    //     printf("%d ", my_array[i]);
    // }



    return 0;
}
