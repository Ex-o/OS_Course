#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define resourceCnt 3
#define processCnt  5

int E[resourceCnt];
int A[resourceCnt];
int alloc[processCnt][resourceCnt];
int request[processCnt][resourceCnt];

int check(int req[resourceCnt], int src[resourceCnt]) {
	for (int i = 0; i < resourceCnt; ++i)
		if (req[i] > src[i])
			return 0;
	return 1;
}


int main() {
	FILE *input = fopen("input_ok.txt", "r");
	if (input == NULL) {
		fprintf(stderr, "No file input.txt\n");
		return 1;
	}

	for (int i = 0; i < resourceCnt; ++i) {
		fscanf(input, "%d", &E[i]);
	}

	for (int i = 0; i < resourceCnt; ++i) {
		fscanf(input, "%d", &A[i]);
	}

	for (int i = 0; i < processCnt; ++i) {
		for (int j = 0; j < resourceCnt; ++j) {
			fscanf(input, "%d", &alloc[i][j]);
		}
	}

	for (int i = 0; i < processCnt; ++i) {
		for (int j = 0; j < resourceCnt; ++j) {
			fscanf(input, "%d", &request[i][j]);
		}
	}

	fclose(input);

	int finish[processCnt];
	int closing = 1;
	
	while (closing) {
		closing = 0;
		for (int i = 0; i < processCnt; ++i) {
			if (!finish[i] && check(request[i], A)) {
				for (int j = 0; j < resourceCnt; ++j) {
					A[j] += alloc[i][j];
				}
				finish[i] = 1;
				closing = 1;
			}
		}
	}

	FILE *output = fopen("output.txt", "w");
	int dlocked = 0;

	for (int i = 0; i < processCnt; ++i) {
		if (!finish[i]) {
			dlocked = 1;
			fprintf(output, "Process %d is dead locked.\n", i);
		}
	}

	if (!dlocked) {
		fprintf(output, "No deadlock.\n");
	}

	fclose(output);
	return 0;
}
