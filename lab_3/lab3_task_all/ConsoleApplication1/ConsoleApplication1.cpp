#include <iostream>
#include <omp.h>

using namespace std;

void firstTask() {
    long long N;
    long long sum = 0;
    int num_threads = 2;
    printf("Task 1\n");
    printf("N: ");
    cin >> N;

    omp_set_dynamic(0);
#pragma omp parallel num_threads(num_threads) reduction(+:sum)
    {
        int thread_id = omp_get_thread_num();
        if (thread_id == 0) { // бежим по нечётным
            for (int i = 1; i <= N; i += num_threads) {
                sum += i;
            }
        }
        else if (thread_id == 1) { // бежим по чётным
            for (int i = 2; i <= N; i += num_threads) {
                sum += i;
            }
        }
        printf("[%d]: Sum = %lld \n", thread_id, sum);
    }

    printf("Sum = %lld \n", sum);
    printf("Answer = %lld \n", ((1 + N) * N / 2));
}

void secondTask() {
    long long N;
    long long sum = 0;
    int num_threads;

    printf("Task 1\n");
    printf("N: ");
    cin >> N;

    printf("num_threads: ");
    cin >> num_threads;

    omp_set_dynamic(0);

#pragma omp parallel num_threads(num_threads) reduction(+:sum)
    {
        int thread_id = omp_get_thread_num();
        //sum = 0;
        for (int i = thread_id + 1; i <= N; i += num_threads) {
            sum += i;
        }

        printf("[%d]: Sum = %lld \n", thread_id, sum);
    }

    printf("Sum = %lld \n", sum);
    printf("Answer = %lld \n", ((1 + N) * N / 2));
}


void thirdTask() {
    long long N;
    long long sum = 0;
    int num_threads;
    int nThreads = 0;
    printf("Task 1\n");
    printf("N: ");
    cin >> N;

    printf("num_threads: ");
    cin >> num_threads;

    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);

#pragma omp parallel 
    {


#pragma omp for
        for (int i = 0; i <= N; ++i) {
            int thread_id = omp_get_thread_num();
#pragma omp atomic
            sum += i;
            printf("[%d]: Sum = %lld \n", thread_id, sum);
        }
    }

    printf("Sum = %lld \n", sum);
    printf("Answer = %lld \n", ((1 + N) * N / 2));

}

void fourthTask() {
    long long N;
    long long sum = 0;
    int num_threads;
    int nThreads = 0;
    printf("Task 1\n");
    printf("N: ");
    cin >> N;

    printf("num_threads: ");
    cin >> num_threads;

    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);

#pragma omp parallel 
    {


#pragma omp for schedule(static)
        for (int i = 0; i <= N; ++i) {
            int thread_id = omp_get_thread_num();
#pragma omp atomic
            sum += i;
            printf("[%d]: Sum = %lld, caltulation of the iteration number %d \n", thread_id, sum, i);
        }
    }

    printf("Sum = %lld \n", sum);
    printf("Answer = %lld \n", ((1 + N) * N / 2));

}

int main() {
    firstTask();
    secondTask();
    thirdTask();
    fourthTask();
    return 0;
}
