#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <omp.h>
#include "Header.h"


using namespace std;

int main() {
	int print;
	int N;
	int num_threads;
	printf("print: ");
	cin >> print;
	printf("N: ");
	cin >> N;
	printf("num threads: ");
	cin >> num_threads;
	bubble_sort(print, N, num_threads);
	start_merge_sort(print, N, num_threads);
	start_quick_sort(print, N, num_threads);
	shell_sort(print, N, num_threads);
}