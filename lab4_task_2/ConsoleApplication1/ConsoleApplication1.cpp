#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <omp.h>
#include "Header.h"
int (*sortFunc)(int, int, int, int[]) = NULL;

using namespace std;

void mera(int (*sortFunc)(int, int, int, int[])) {
	int N = 16;
	int num_threads;
	int threads[8] = {1, 2, 4, 6, 8, 12, 16, 20};
	int m = 8;
	int print = 0;
	for (int i = 0; i < m; i++) {
		num_threads = threads[i];
		printf("Threads % d ", num_threads);
		while (N < 1024 * 1024) {

			
			
			int* X = (int*)malloc(N * sizeof(int));
			fillupRandomly(X, N, 0, N * N * N);


			(*sortFunc)(print, N, num_threads, X);

			


			N *= 2;
		}
		cout << "\n";
		N = 16;
	}
}
int main() {
	
	cout << "quick sort\n";
	sortFunc = &start_quick_sort;
	mera(sortFunc);
	cout << "merge sort\n";
	sortFunc = &start_merge_sort;
	mera(sortFunc);
	cout << "shell sort\n";
	sortFunc = &shell_sort;
	mera(sortFunc);
	cout << "bubble sort\n";
	sortFunc = &bubble_sort;
	mera(sortFunc);

}