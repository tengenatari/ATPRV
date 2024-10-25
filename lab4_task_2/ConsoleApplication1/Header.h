#pragma once
int bubble_sort(int print, int N, int num_threads, int v[]);
int start_merge_sort(int print, int N, int num_threads, int X[]);
int start_quick_sort(int print, int N, int num_threads, int X[]);
int shell_sort(int print, int n, int num_threads, int arr[]);
void fillupRandomly(int* m, int size, unsigned int min, unsigned int max);
void printArray(int* a, int size);
int isSorted(int* a, int size);
void another_quicksort(int print, int* a, int n, int threads);
