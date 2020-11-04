#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	char buffer[1024];
	int flag_a = (argc > 1) && (strlen(argv[1]) >= 2) && (argv[1][0] == '-' && argv[1][1] == 'a');
	int flag_stdout = (argc == 1);

	const int fileCnt = (flag_stdout) ? 1 : argc - flag_a - 1;
	int *files = (int *)malloc(sizeof(int) * fileCnt) ;

	if (flag_stdout){
		files[0] = STDOUT_FILENO;
	} else{
		for (int i = 0; i < argc - flag_a - 1; i++){
			files[i] = flag_a ?
					   open(argv[i + 2], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU) :
					   open(argv[i + 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		}
	}

	int chrts = read(STDIN_FILENO, buffer, 1024);
	while (chrts){
		for (int i = 0; i < fileCnt; ++i) {
			write(files[i], buffer, chrts);
		}
		chrts = read(0, buffer, 1024);
	}


	for (int i = 0; i < argc - flag_a - 1; ++i) {
		close(files[i]);
	}
}
