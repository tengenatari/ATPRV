#include <algorithm>
#include <iostream>
#include <omp.h>
#include <iterator>
#include <random>
#include <vector>
#include "Header.h"
using namespace std;


int bubble_sort(int print, int N, int num_threads, int v[]) {
    
    
    omp_set_dynamic(0);

    if (print) {
        for (int i = 0; i < N; i++) {
            cout << v[i] << " ";
        }
        cout << "\n";
    }    

    omp_set_num_threads(num_threads);

    double begin = omp_get_wtime();

        int swap;
#pragma omp parallel for shared(v) schedule(static) 
    for (int i = 0; i < N; i++) {


        for (int j = i % 2; j < N - 1; j = j + 2) {
            if (v[j] > v[j + 1]) {
                swap = v[j + 1];
                v[j + 1] = v[j];
                v[j] = swap;
                if (print >= 2) {
                    printf("[%d]: swap %d, %d \n", omp_get_thread_num(), j, j + 1);
                }
                    
            }
        }
    }

    double end = omp_get_wtime();
    if (print) { printf("Is arrau sorted % d \n", isSorted(v, N)); }
    if(print){
        for (int i = 0; i < N; i++) {
            cout << v[i] << " ";;
        }
        cout << '\n';
    }
    
    printf("%f ", end - begin);
}


