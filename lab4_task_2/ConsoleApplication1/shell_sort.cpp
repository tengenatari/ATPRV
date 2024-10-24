#include  <iostream>
#include <omp.h>
#include "Header.h"
using namespace std;


int shell_sort(int print, int N, int num_threads)
{



    int* arr = (int*)malloc(N * sizeof(int));

    printf("shell sort\n");
    fillupRandomly(arr, N, 0, N);
    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);

    if (print) {
        printArray(arr, N);
    }
    double begin = omp_get_wtime();
#pragma omp parallel 
    {
        for (int gap = N / 2; gap > 0; gap /= 2)
        {
#pragma omp for 
            for (int i = gap; i < N; i += 1)
            {

                int temp = arr[i];


                int j;

                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];

                arr[j] = temp;
            }
        }
    }
    double end = omp_get_wtime();
    
    
    if (print) {
        cout << "The sorted array is: ";
        printArray(arr, N);
    }
    printf("Time: %f (s) \n", end - begin);
    return 0;
}