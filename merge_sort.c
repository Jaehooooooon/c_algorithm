#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 256

int *input;
int *mergeTemp;

void MergeSort(int arr[], int lo, int hi);
void merge(int arr[], int lo, int mid, int hi);

int main(int argc, char* argv[]) {
	char buffer[MAX];
	unsigned int N, x, beforeCharIsNoSpace = 0, K = 0;
	clock_t start, stop;
	double elapsedTime = 0;

	N = atoi(argv[2]);
	
	input = (int*)malloc(sizeof(int) * N);
	mergeTemp = (int*)malloc(sizeof(int) * N);

	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Cannot open the file.");
		exit(0);
	}

	while (!feof(fp)) {
		if (fgets(buffer, MAX, fp) == NULL) break;
		for (x = 0; x < strlen(buffer); x++) {
			if (buffer[x] == ' ' || buffer[x] == '\n' || buffer[x] == '\r' || buffer[x] == '\r\n') {
				if (beforeCharIsNoSpace) {
					K++;
					beforeCharIsNoSpace = 0;
				}
			}
			else {
				beforeCharIsNoSpace = 1;
			}
		}
	}
	fseek(fp, 0, SEEK_SET);

	if (N > K)
		N = K;

	for (int i = 0; i < N; i++) {
		fscanf(fp, "%d", &input[i]);
	}

	start = clock();
	MergeSort(input, 0, N-1);
	stop = clock();
	elapsedTime = (double) (stop - start) / CLOCKS_PER_SEC *1000;
	
	for (int i = 0; i < N; i++) {
		printf("%d\n", input[i]);
	}
	
	printf("Running time = %.3lf ms\n", elapsedTime);

	fclose(fp);
	free(mergeTemp);
	free(input);
	return 0;
}

void MergeSort(int arr[], int lo, int hi) {
	int mid;

	if (lo < hi) {
		mid = (lo + hi) / 2;
		MergeSort(arr, lo, mid);
		MergeSort(arr, mid + 1, hi);

		merge(arr, lo, mid, hi);
	}
}

void merge(int arr[], int lo, int mid, int hi) {
	int left = lo, right = mid + 1;
	int i = lo;

	while (left <= mid && right <= hi) {
		if (arr[left] <= arr[right]) {
			mergeTemp[i++] = arr[left++];
		}
		else {
			mergeTemp[i++] = arr[right++];
		}
	}

	if (left > mid) {
		for (right; right <= hi; right++) {
			mergeTemp[i++] = arr[right];
		}
	}
	else if (right > hi) {
		for (left; left <= mid; left++)
			mergeTemp[i++] = arr[left];
	}

	for (int x = lo; x <= hi; x++) {
		arr[x] = mergeTemp[x];
	}
}