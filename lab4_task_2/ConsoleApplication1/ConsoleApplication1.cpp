#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <omp.h>
#include "Header.h"


using namespace std;

int main() {
	int N;
	printf("N: ");
	cin >> N;

	bubble_sort(1, N);
	start_merge_sort(1, N);
}