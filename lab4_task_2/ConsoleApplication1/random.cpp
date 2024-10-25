#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <iostream>


int rrand(int range_min, int range_max) {
	return rand() % (range_max - range_min + 1) + range_min;
}

void fillupRandomly(int* m, int size, unsigned int min, unsigned int max) {
#pragma parallel for
	for (int i = 0; i < size; i++)
		m[i] = rrand(min, max);
}


void printArray(int* a, int size) {
	for (int i = 0; i < size; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int isSorted(int* a, int size) {
	for (int i = 0; i < size - 1; i++)
		if (a[i] > a[i + 1])
			return 0;
	return 1;
}
