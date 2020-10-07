#include<stdio.h>
#include<stdlib.h>
#include<sys/resource.h>
#include<unistd.h>

const int N = 10;
const int MEMORY = 10 * 1024 * 1024;

struct rusage usage;

int main(){

	char *arr;
	for(int i = 0; i < N; i++){
		arr = (char*) malloc(MEMORY);
		memset(arr, '0', MEMORY);

		getrusage(RUSAGE_SELF, &usage);
		printf("Memory Used: %ld\n", usage.ru_maxrss);
		sleep(1);	
	}
	return 0;
}
