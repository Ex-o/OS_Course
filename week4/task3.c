#include <stdio.h>

void main(){
	char str[512];
	printf("Enter your command:\n");
	gets(str);

	system(str);
}
