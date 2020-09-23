#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <algorithm>

const int MAX = 50;

int arrival_time[MAX];
int burst_time[MAX];
int wait_time[MAX];
int turnaround_time[MAX];
int pId[MAX];
int completion_time[MAX];
int processCount;

int max(int a, int b){
	return (a >= b ? a : b);
}
void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void printData(){
	int waitingTime = 0, turnaroundTime = 0;

	printf("Completion Time\tTurn Around Time\tWaiting Time\n");
	for(int i = 0; i < processCount; i++){
		waitingTime += wait_time[i];
		turnaroundTime += turnaround_time[i];

		//int completion_time = arrival_time[i] + turnaround_time[i];
		printf("%d\t%d\t%d\n", completion_time[i], turnaround_time[i], wait_time[i]);
	}

	printf("Average Waiting Time: %d\nAverage Turn Around Time: %d\n", waitingTime / processCount, turnaroundTime / processCount);
}
int main(int argc, char const *argv[]){

	scanf("%d", &processCount);

	printf("Arrival times:");
	for(int i = 0; i < processCount; i++){
		scanf("%d", &arrival_time[i]);
	}

	printf("Burst times:");
	for(int i = 0; i < processCount; i++){
		scanf("%d", &burst_time[i]);
	}

	for(int i = 0; i < processCount; i++){
		for(int j = 0; j < processCount - i - 1; j++){
			if(arrival_time[j] > arrival_time[j + 1]){
				swap(&pId[j + 1], &pId[j]);
				swap(&arrival_time[j + 1], &arrival_time[j]);
				swap(&burst_time[j + 1], &burst_time[j]);
			}
		}
	}

	int currentTime;
	int curIdx;
	int minBurst;

	for(int i = 1; i < processCount; i++){
		currentTime = completion_time[i - 1];
		curIdx = i;
		minBurst = burst_time[i];

		for(int j = i + 1; j < processCount; j++){
			if(minBurst > burst_time[j]){
				minBurst = burst_time[j];
				curIdx = j;
			}
		}

		swap(&pId[i], &pId[curIdx]);
		swap(&arrival_time[i], &arrival_time[curIdx]);
		swap(&burst_time[i], &burst_time[curIdx]);

		completion_time[i] = currentTime + burst_time[i];
	}
	printData();
	return 0;
}
