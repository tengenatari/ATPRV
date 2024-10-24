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

void bubble_sort(vector<int> v, int start, int end) {




#pragma omp parallel 
    {
        int swap;
        for (int i = start; i < end; i++) {

#pragma omp for schedule(static) 
            for (int j = i % 2 + start; j < end - 1; j = j + 2) {
                if (v[j] > v[j + 1]) {
                    swap = v[j + 1];
                    v[j + 1] = v[j];
                    v[j] = swap;
                    printf("[%d]: swap %d, %d \n", omp_get_thread_num(), j, j + 1);
                }
            }
        }
    }
    for (int i = 0; i < end; i++) {
        cout << v[i] << " ";;
    }
    cout << "\n";

}



void merge_vec(vector<int> v, int start, int end) {
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


void mergeSortRecursive(vector<int> v, int left, int right, int threads) {
    omp_set_num_threads(2);

#pragma omp parallel 
    {
        if (right - left > 10)
        {
#pragma omp sections
            {
#pragma omp section
                {
                    mergeSortRecursive(v, left, right / 2, threads);
                }

#pragma omp section
                {
                    mergeSortRecursive(v, (right + 1) / 2, right, threads);
                }


            }
            merge_vec(v, left, (right + 1) / 2);
        }
        else {
            bubble_sort(v, left, right);
        }

    }
}





void init_merge_sort(){
    vector<int> v = init_vec();

    printf("num_threads: ");

    int N = v.size();
    int num_threads;
    cin >> num_threads;

    omp_set_num_threads(num_threads);
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortRecursive(v, 0, v.size() - 1, num_threads);
    
    }
    
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}





int main() {
    
    init_merge_sort();

    return 0;
}