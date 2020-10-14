#include <stdio.h>
#include <stdlib.h>

unsigned int *age;
int *pgTable;

int missCount = 0;
int hitCount = 0;
int pgFrames;

void swapOldest(int page){
	int oldestIdx = 0;
	for (int i = 1; i < pgFrames; i++){
		if (pgTable[i] == -1){
			oldestIdx = i;
			break;
		}
		if (age[i] < age[oldestIdx]) {
			oldestIdx = i;
		}
	}

	pgTable[oldestIdx] = page;
	age[oldestIdx] = 0;
}

bool InMemory(int page){
	for (int i = 0; i < pgFrames; i++)
		if (pgTable[i] == page){
			hitCount++;
			return true;
		}

	missCount++;
	return false;
}

int main(){
	printf("Enter the number of page frames:\n");
	scanf("%d", &pgFrames);

	pgTable = static_cast<int *>(calloc(pgFrames, sizeof(int)));
	age = static_cast<unsigned int *>(calloc(pgFrames, sizeof(int)));


	for (int i = 0; i < pgFrames; i++) {
		pgTable[i] = -1;
	}

	FILE *inputFile = fopen("in.txt", "r");
	int page;
	while (fscanf(inputFile, "%d", &page) > 0){
		if (!InMemory(page)) {
			swapOldest(page);
		}
		for (int i = 0; i < pgFrames; i++){
			age[i] >>= 1;
			if (pgTable[i] == page) {
				age[i] |= (1 << (sizeof(unsigned int) * 8 - 1));
			}
		}
	}
	printf("Hit Count: %d\n", hitCount);
	printf("Miss Count: %d\n", missCount);
	printf("Hit/Miss ratio: %.9f\n", hitCount * 1.0 / missCount);

	return 0;
}