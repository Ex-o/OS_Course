#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <algorithm>

const int MAX = 50;

int arrival_time[MAX];
int burst_time[MAX];
int wait_time[MAX];
int turnaround_time[MAX];
int remaining[MAX];
int quantum;
int processCount;

int max(int a, int b){
	return (a >= b ? a : b);
}

void printData(){
	int waitingTime = 0, turnaroundTime = 0;

	printf("Completion Time\tTurn Around Time\tWaiting Time\n");
	for(int i = 0; i < processCount; i++){
		waitingTime += wait_time[i];
		turnaroundTime += turnaround_time[i];

		int completion_time = arrival_time[i] + turnaround_time[i];
		printf("%d\t%d\t%d\n", completion_time, turnaround_time[i], wait_time[i]);
	}

	printf("Average Waiting Time: %d\nAverage Turn Around Time: %d\n", waitingTime / processCount, turnaroundTime / processCount);
}
int main(int argc, char const *argv[]){

	scanf("%d", %processCount);

	printf("Arrival times:");
	for(int i = 0; i < processCount; i++){
		scanf("%d", &arrival_time[i]);
	}

	printf("Burst times:");
	for(int i = 0; i < processCount; i++){
		scanf("%d", &burst_time[i]);
	}
	printf("Quantum:");
	scanf("%d", &quantum);

	for(int i = 0; i < processCount; i++){
		remaining[i] = burst_time[i];
	}
	int current_time = 0;

	for(;;){
		bool ok = true;
		for(int i = 0; i < processCount; i++){
			if(remaining[i] > 0){
				ok = false;
				if(remaining[i] > quantum){
					remaining[i] -= quantum;
					current_time += quantum;
				}
				else{
					current_time += remaining[i];
					wait_time[i] = current_time - burst_time[i];
					remaining[i] = 0;
				}
			}
		}
		if(ok){
			break;
		}
	}

	for(int  i = 0; i < processCount; i++){
		turnaround_time[i] = burst_time[i] + wait_time[i];
	}

	printData();
	return 0;
}
