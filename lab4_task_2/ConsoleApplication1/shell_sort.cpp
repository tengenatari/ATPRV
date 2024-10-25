#include  <iostream>
#include <omp.h>
#include "Header.h"
using namespace std;
void insertionsort(int a[], int n, int stride) {
    for (int j = stride; j < n; j += stride) {
        int key = a[j];
        int i = j - stride;
        while (i >= 0 && a[i] > key) {
            a[i + stride] = a[i];
            i -= stride;
        }
        a[i + stride] = key;
    }
}

int shell_sort(int print, int N, int num_threads, int arr[])
{


    int i, m;


    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);

    if (print) {
        printArray(arr, N);
    }
    double begin = omp_get_wtime();

    for (m = N / 2; m > 0; m /= 2)
    {
#pragma omp parallel for shared(arr,m,N) private (i) default(none)
        for (i = 0; i < m; i++)
            insertionsort(&(arr[i]), N - i, m);
    }
 
    double end = omp_get_wtime();
    if (print) { printf("Is arrau sorted % d \n", isSorted(arr, N)); }
    
    if (print) {
        cout << "The sorted array is: ";
        printArray(arr, N);
    }
    printf("%f ", end - begin);
    return 0;
}