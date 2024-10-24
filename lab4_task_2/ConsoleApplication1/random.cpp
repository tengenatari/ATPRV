#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <iostream>


unsigned int rand_interval(unsigned int min, unsigned int max)
{
	int r;
	const unsigned int range = 1 + max - min;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit = buckets * range;

	do
	{
		r = rand();
	} while (r >= limit);

	return min + (r / buckets);
}

void fillupRandomly(int* m, int size, unsigned int min, unsigned int max) {
	for (int i = 0; i < size; i++)
		m[i] = rand_interval(min, max);
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
