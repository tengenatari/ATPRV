#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include "Header.h"
using namespace std;


void swap(int arr[], int pos1, int pos2) {
	int temp;
	temp = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = temp;
}

int partition(int arr[], int low, int high, int pivot) {
	
	int j = low;
#pragma parallel for 
	for(int i = low; i <= high; i++){
		if (arr[i] <= pivot) {
#pragma atomic
			swap(arr, i, j);
			j++;
		}
	}
	return j - 1;
}

void quickSort(int arr[], int low, int high) {
	if (low < high) {

		int pivot = arr[high];

		int pos = partition(arr, low, high, pivot);
		
		
#pragma omp task shared(arr)
		quickSort(arr, low, pos - 1);
#pragma omp task shared(arr)
		quickSort(arr, pos + 1, high);
	}
#pragma omp taskwait 
}

int start_quick_sort(int print, int N, int num_threads)
{
	
	int* X = (int*)malloc(N * sizeof(int));
	printf("quick sort\n");

	fillupRandomly(X, N, 0, N);
	omp_set_dynamic(0);
	omp_set_num_threads(num_threads);

	if (print) {
		printArray(X, N);
	}
	double begin = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp single
		quickSort(X, 0, N - 1);
	}
	double end = omp_get_wtime();
	
	
	if (print) {
		printArray(X, N);
	}
	printf("Time: %f (s) \n", end - begin);

}