#include<stdio.h>
#include<stdlib.h>

const int N = 10;
const int MEMORY = 10 * 1024 * 1024;

int main(){

	char *arr;
	for(int i = 0; i < N; i++){
		arr = (char*) malloc(MEMORY);
		memset(arr, '0', MEMORY);
		sleep(1);	
	}
	return 0;
}
