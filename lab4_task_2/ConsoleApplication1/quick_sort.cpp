#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <iostream>
#include "Header.h"
using namespace std;


int partition(int* a, int l, int r)
{
	int v = a[(l + r) / 2];
	int i = l, j = r;
	while (i <= j)
	{
		while (a[i] < v)
			i++;
		while (a[j] > v)
			j--;
		if (i >= j)
			break;
		swap(a[i++], a[j--]);
	}
	return j;
}

void quicksort(int* a, int l, int r)
{
	if (l >= r)
		return;
	int q = partition(a, l, r);

#pragma omp task
	quicksort(a, l, q);
#pragma omp task
	quicksort(a, q + 1, r);
}


int start_quick_sort(int print, int N, int num_threads, int X[])
{
	
	


	
	omp_set_dynamic(0);
	omp_set_num_threads(num_threads);

	if (print) {
		printArray(X, N);
	}
	double begin = omp_get_wtime();
#pragma omp parallel num_threads(num_threads)
#pragma omp single
	quicksort(X, 0, N - 1);
	double end = omp_get_wtime();
	if(print){ printf("Is arrau sorted % d \n", isSorted(X, N)); }
	
	
	if (print) {
		printArray(X, N);
	}
	printf("%f ", end - begin);

}