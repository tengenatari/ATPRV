#include <algorithm>
#include <iostream>
#include <omp.h>
#include <iterator>
#include <random>
#include <vector>
using namespace std;

vector<int> init_vec() {
    long long N;
    int nThreads = 0;
    printf("bubble sort\n");
    printf("N: ");
    cin >> N;

    std::vector<int> v{};
    for (int i = 0; i < N; i++) {
        v.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(v.begin(), v.end(), g);

    for (int i = 0; i < N; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
    return v;
}

void bubble_sort() {

    vector<int> v = init_vec();

    printf("num_threads: ");

    int N = v.size();
    int num_threads;

    cin >> num_threads;

    omp_set_num_threads(num_threads);

#pragma omp parallel 
    {
        int swap;
        for (int i = 0; i < N; i++) {

#pragma omp for schedule(static) 
            for (int j = i % 2; j < N - 1; j = j + 2) {
                if (v[j] > v[j + 1]) {
                    swap = v[j + 1];
                    v[j + 1] = v[j];
                    v[j] = swap;
                    printf("[%d]: swap %d, %d \n", omp_get_thread_num(), j, j + 1);
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        cout << v[i] << " ";;
    }

}

void merge_sort() {
#pragma omp parallel sections
    {
#pragma omp section
        {
            printf("section 1 id = %d, \n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("section 2 id = %d, \n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("section 3 id = %d, \n", omp_get_thread_num());
        }
    }
}


void init_merge_sort() {
    vector<int> v = init_vec();

    printf("num_threads: ");

    int N = v.size();
    int num_threads;
    cin >> num_threads;

    omp_set_num_threads(num_threads);



}


