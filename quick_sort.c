/**
 * "Quick Sort"
 * - ./quick_sort <input_file_name> <N> <pivot_option>
 * - measure running time of 'Quick Sort'
 * - count number of comparisons in 'Quick Sort'
 * - try different 'choose_pivot' methods
 *
 * name Seo Jaehoon / ID 20152577
  **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#define MAX 256

int m_pivot_option;

void choose_pivot(int *data, unsigned int n) {
	int pivot, i;
	int temp;

	switch (m_pivot_option) {
	case 1:	//first
		break;
	case 2:	//middle 
		pivot = (n - 1) / 2;
		temp = data[0];
		data[0] = data[pivot];
		data[pivot] = temp;
		break;
	case 3:	//random element
		pivot = random() % (n);
		temp = data[0];
		data[0] = data[pivot];
		data[pivot] = temp;
		break;
	case 4:	//median-of-three
		i = (n - 1) / 2;
		if (data[0] <= data[n - 1]) {
			if (data[i] <= data[0]) {	//first
				break;
			}
			else if (data[0] <= data[i]) {
				if (data[i] <= data[n - 1]) {	//middle
					temp = data[0];
					data[0] = data[i];
					data[i] = temp;
					break;
				}
				else {	//last
					temp = data[0];
					data[0] = data[n - 1];
					data[n - 1] = temp;
					break;
				}
			}
		}
		else {
			if (data[i] >= data[0]) {	//first
				break;
			}
			else if (data[i] <= data[0]) {
				if (data[i] <= data[n - 1]) {	//last
					temp = data[0];
					data[0] = data[n - 1];
					data[n - 1] = temp;
					break;
				}
				else {	//middle
					temp = data[0];
					data[0] = data[i];
					data[i] = temp;
					break;
				}
			}
		}
	}
}

unsigned long quick_sort(int *data, unsigned int n) {
	unsigned long cnt = (n - 1); // number of comparisons
	int pivot, i, j, temp;

	if (n <= 1) {
		return 0;
	}

	// choose pivot and  always place it at first element of array
	choose_pivot(data, n);
	pivot = data[0];

	i = 1;	//i starts at 1
	for (j = i; j < n; j++) {
		if (data[j] < pivot) {
			temp = data[j];
			data[j] = data[i];
			data[i] = temp;
			i++;
		}
	}
	//swap pivot with i
	temp = data[0];
	data[0] = data[i - 1];
	data[i - 1] = temp;

	cnt += quick_sort(data, i - 1);	// < pivot
	cnt += quick_sort(&data[i], j - i);	// > pivot

	return cnt;
}



int main(int argc, char* argv[]) {
	int *input/*, *data*/;
	char buffer[MAX];
	unsigned int N, x, beforeCharIsNoSpace = 0, K = 0;
	unsigned long comparisons = 0;
	clock_t start, stop;
	//int counter = 0;
	double /*elapsedTime = 0,*/ duration = 0;
	
	N = atoi(argv[2]);
	m_pivot_option = atoi(argv[3]);
	
	input = (int*)malloc(sizeof(int) * N);
	//data = (int*)malloc(sizeof(int) * N);

	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Cannot open the file.");
		exit(0);
	}

	while (!feof(fp)) {		//How many numbers are in the input file (K)
		if (fgets(buffer, MAX, fp) == NULL) break;
		for (x = 0; x < strlen(buffer); x++) {
			if (buffer[x] == ' ' || buffer[x] == '\n' || buffer[x] == '\r') {
				if (beforeCharIsNoSpace) {	//check whether previous character is also space or not
					K++;
					beforeCharIsNoSpace = 0;
				}
			}
			else {
				beforeCharIsNoSpace = 1;
			}
		}
	}
	fseek(fp, 0, SEEK_SET);		//Move the cursor to the first again

	if (N > K)		//if N > K, then program sort all K numbers in the file
		N = K;

	for (int i = 0; i < N; i++) {
		fscanf(fp, "%d", &input[i]);
	}
	/*
	do {
		memcpy(data, input, N);
		counter++;
		start = clock();
		quick_sort(data, N);
		stop = clock();
		elapsedTime += (double)(stop - start) / CLOCKS_PER_SEC * 1000;
		data[0] = '\0';
	} while (elapsedTime < 1000);
	duration = elapsedTime / counter;
	*/
	start = clock();
	comparisons = quick_sort(input, N);
	stop = clock();
	duration += (double)(stop - start) / CLOCKS_PER_SEC * 1000;

	//comparisons = quick_sort(input, N);
	for (int i = 0; i < N; i++) {
		printf("%d\n", input[i]);
	}
	
	// Please keep these printf statements!
	printf("N = %7d,\tRunning_Time = %.3f ms\n", N, duration);
	printf("Pivot option = %d\n", m_pivot_option);
	printf("Number of comparisons = %lu\n", comparisons);

	fclose(fp);
	//free(data);
	free(input);
	return 0;
}