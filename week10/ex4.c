#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
 
int main() {
    DIR* tmp = opendir("tmp");
    struct dirent *dir = readdir(tmp);
    struct stat file;
    char cmd[512];
 
    while (dir != NULL){
        if (dir->d_name[0] != '.'){ // a file read
            char name[512];
            sprintf(name, "./tmp/%s", dir->d_name);
            stat(name, &file);
            if (file.st_nlink >= 2){
                sprintf(cmd, "echo %s count: %ld >> ex4.txt", name, file.st_nlink);
                system(cmd);
 
                unsigned int inode = file.st_ino;
                sprintf(cmd, "find -inum %u >> ex4.txt", inode);
                system(cmd);
            }
 
        }
 
        dir = readdir(tmp);
    }
 
    return 0;
}
