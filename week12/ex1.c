#include <stdio.h>
#include <fcntl.h>

int main(){
	int lnk = open("/dev/random", O_RDONLY);
	char buffer[20];
	read(lnk, buffer, sizeof buffer);
	close(lnk);

	FILE *file = fopen("ex1.txt", "w");
	fprintf(file, "%s", buffer);
	fclose(file);
	return 0;
}