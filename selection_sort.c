#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 256

int *input;

void SelectionSort(int arr[], int N);

int main(int argc, char* argv[]) {
	char buffer[MAX];
	unsigned int N, x, beforeCharIsNoSpace = 0, K = 0;
	clock_t start, stop;
	double elapsedTime = 0;

	N = atoi(argv[2]);

	input = (int*)malloc(sizeof(int) * N);

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
	SelectionSort(input, N);
	stop = clock();
	elapsedTime = (double)(stop - start) / CLOCKS_PER_SEC;

	for (int i = 0; i < N; i++) {
		printf("%d\n", input[i]);
	}

	printf("Running time = %lf ms\n", elapsedTime);

	fclose(fp);
	free(input);
	return 0;
}


void SelectionSort(int arr[], int N) {
	int temp, min;
	int i, j;

	for (i = 0; i < N - 1; i++) {
		min = i;

		for (j = i + 1; j < N; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
