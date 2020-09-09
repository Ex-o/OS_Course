#include <stdio.h>
#include <sys/types.h>

void main(int argc, char* argv[]){
	if(argc >= 2){
		char* args[argc];
		for(int i = 1; i < argc; i++){
			args[i - 1] = argv[i];
			
		}
		args[argc - 1] = NULL;
		pid_t id = fork();
		execvp(args[0], args, 0);	
	}
}

	
