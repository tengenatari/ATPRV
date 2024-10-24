#include <algorithm>
#include <iostream>
#include <omp.h>
#include <iterator>
#include <random>
#include <vector>
using namespace std;

void init_vec(int v[], int N) {
    int nThreads = 0;
    printf("bubble sort\n");
    
    

    
    for (int i = 0; i < N; i++) {
        v[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(*v, *v+N, g);

    for (int i = 0; i < N; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

void bubble_sort(int  v[], int start, int end) {
    for (int i = start; i < end; i++) {


        for (int j = i % 2 + start; j < end - 1; j = j + 2) {
            if (v[j] > v[j + 1]) {
                iter_swap(&v + j, &v + j + 1);
                printf("[%d]: swap %d, %d \n", omp_get_thread_num(), j, j + 1);
            }
        }
    }
    
    for (int i = 0; i < end; i++) {
        cout << v[i] << " ";;
    }
    cout << "\n";

}



void merge_vec(int v[], int start, int end) {
    int swap;
    while (start < end)
    {
        if (v[start] > v[end]) {
            swap = v[end];
            v[end] = v[start];
            v[start] = v[end];
            end++;
        }
        start++;
    }

}


void mergeSortRecursive(int v[], int left, int right, int num_threads) {
    

        omp_set_num_threads(num_threads);
        if (right - left > 10)
        {
#pragma omp parallel sections shared(v)
            {
#pragma omp section
                {
                    
                    mergeSortRecursive(v, left, right / 2, num_threads);
                }

#pragma omp section
                {
                    
                    mergeSortRecursive(v, (right + 1) / 2, right, num_threads);
                }


            }
            merge_vec(v, left, (right + 1) / 2);
        }
        else {
            bubble_sort(v, left, right);
        }

}





void init_merge_sort(){
    int N;
    cin >> N;
    int v[100000];
    init_vec(v, N);

    printf("num_threads: ");

    int num_threads;
    cin >> num_threads;

    omp_set_num_threads(num_threads);
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortRecursive(v, 0, N, num_threads);
    
    }
    
    for (int i = 0; i < N; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}





int main() {
    
    init_merge_sort();

    return 0;
}