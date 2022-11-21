//
// Created by Swift Sheng on 10/13/22.
//
#include <stdio.h>
#include "stdlib.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

void updateMax(int *localMax, int *globalMax){
    if (*localMax > *globalMax)
        *globalMax = *localMax;
}

int byteWise(char byte, int *localMax, int *globalMax){
    for (int i = 0; i < 8; ++i) {
        if((byte & 128) == 0 ) {
            *localMax = *localMax + 1;
            updateMax(localMax, globalMax);

        } else{
            *localMax = 0;
        }
        byte <<= 1;
    }
    return *localMax;

}

void singleFileCount(char* fileName, int* addr){
    struct stat stat;
    int globalMax = 0 , localMax =0;
    int fd = open(fileName, O_RDONLY); //Read Only
    if(fd == -1){
        char * str = fileName;
        perror(fileName);
        exit(2);
    }


    if (fstat(fd, &stat) == -1) {
        perror(fileName);
        exit(2);
    }

    char* newMap = mmap(NULL, stat.st_size,PROT_READ,MAP_SHARED,fd,0);

    for (int i = 0; i < stat.st_size; i++) {
        char byte = newMap[i];
        localMax = byteWise(byte, &localMax, &globalMax);
    }

    if (*addr < globalMax) {
        *addr = globalMax;
    }

    exit(0);

}

int main(int argc, char **argv){

    if(argc == 1){
        printf("%s\n", "USAGE: ./pccseq filename ..."); // filename is fixed or?
        exit(1);
    }

    pid_t pid;
    int *addr = mmap(NULL, sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANON, -1, 0 );

    for(int i = 1; i < argc; i ++){
        pid = fork();
        if(pid == 0) {
            singleFileCount(argv[i], addr);
        }

    }

    int status;
    while ((pid = wait(&status)) != -1){
        if (WEXITSTATUS(status) == 2){
            exit(2);
        }
        continue;
    };

    printf("%d\n", *addr);


    exit(0);

}


