#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main() {
    const char* str = "This is a nice day";
    int ln = strlen(str);

    int desc = open("ex1.txt", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP);
    ftruncate(desc, ln);
    char* address = mmap(NULL, ln, PROT_WRITE | PROT_READ, MAP_SHARED, desc, 0);

    strcpy(addr, str);
    munmap(addr, ln);
    close(desc);
    return 0;
}