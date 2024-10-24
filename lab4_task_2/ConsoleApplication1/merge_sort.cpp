#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define TASK_SIZE 100

unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

void fillupRandomly(int* m, int size, unsigned int min, unsigned int max) {
    for (int i = 0; i < size; i++)
        m[i] = rand_interval(min, max);
}

void mergeSortAux(int* X, int n, int* tmp) {
    int i = 0;
    int j = n / 2;
    int ti = 0;

    while (i < n / 2 && j < n) {
        if (X[i] < X[j]) {
            tmp[ti] = X[i];
            ti++; i++;
        }
        else {
            tmp[ti] = X[j];
            ti++; j++;
        }
    }
    while (i < n / 2) { /* finish up lower half */
        tmp[ti] = X[i];
        ti++; i++;
    }
    while (j < n) { /* finish up upper half */
        tmp[ti] = X[j];
        ti++; j++;
    }
    memcpy(X, tmp, n * sizeof(int));
}

void mergeSort(int* X, int n, int* tmp)
{
    if (n < 2) return;
#pragma omp task shared(X) if (n > TASK_SIZE)
    mergeSort(X, n / 2, tmp);

#pragma omp task shared(X) if (n > TASK_SIZE)
    mergeSort(X + (n / 2), n - (n / 2), tmp + n / 2);

#pragma omp taskwait
    mergeSortAux(X, n, tmp);
}

void init(int* a, int size) {
    for (int i = 0; i < size; i++)
        a[i] = 0;
}

void printArray(int* a, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int isSorted(int* a, int size) {
    for (int i = 0; i < size - 1; i++)
        if (a[i] > a[i + 1])
            return 0;
    return 1;
}

int start_merge_sort(int print, int N) {
    srand(123456);
 
    
    int numThreads = 4;
    int* X = (int*)malloc(N * sizeof(int));
    int* tmp = (int*)malloc(N * sizeof(int));

    omp_set_dynamic(0);              
    omp_set_num_threads(numThreads); 

    
    if (!X || !tmp)
    {
        if (X) free(X);
        if (tmp) free(tmp);
        return (EXIT_FAILURE);
    }
    
    fillupRandomly(X, N, 0, 5);


    if (print) {
        printArray(X, N);
    }
    double begin = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        mergeSort(X, N, tmp);
    }
    double end = omp_get_wtime();
    printf("Time: %f (s) \n", end - begin);

    assert(1 == isSorted(X, N));

    if (print) {
        printArray(X, N);
    }

    free(X);
    free(tmp);
    return (EXIT_SUCCESS);
}