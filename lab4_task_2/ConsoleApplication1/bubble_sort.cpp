#include <algorithm>
#include <iostream>
#include <omp.h>
#include <iterator>
#include <random>
#include <vector>
using namespace std;

vector<int> init_vec(int N) {
    
    int nThreads = 0;
    

    std::vector<int> v{};
    for (int i = 0; i < N; i++) {
        v.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(v.begin(), v.end(), g);

    
    cout << "\n";
    return v;
}

void bubble_sort(int print, int N) {
    printf("bubble sort\n");
    
    vector<int> v = init_vec(N);

    if (print) {
        for (int i = 0; i < N; i++) {
            cout << v[i] << " ";
        }
        cout << "\n";
    }


    printf("num_threads: ");


    int num_threads;

    cin >> num_threads;

    omp_set_num_threads(num_threads);

    double begin = omp_get_wtime();
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
                    if (print) {
                        printf("[%d]: swap %d, %d \n", omp_get_thread_num(), j, j + 1);
                    }
                    
                }
            }
        }
    }
    double end = omp_get_wtime();
    if(print){
        for (int i = 0; i < N; i++) {
            cout << v[i] << " ";;
        }
        cout << '\n';
    }
    
    printf("Time: %f (s) \n", end - begin);

}


