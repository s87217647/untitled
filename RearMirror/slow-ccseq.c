////
//// Created by Swift Sheng on 9/6/22.
////
//#include <stdio.h>
//#include "stdlib.h"
//#include <fcntl.h> // file control options
//#include <unistd.h>// Standard symbolic constant and types
//
//void updateMax(int *localMax, int *globalMax){
//    if (*localMax > *globalMax)
//        *globalMax = *localMax;
//}
//
//int byteWise(char byte, int *localMax, int *globalMax){
//    for (int i = 0; i < 8; ++i) {
//        if((byte & 128) == 0 ) {
//            *localMax = *localMax + 1;
//            updateMax(localMax, globalMax);
//
//        } else{
//            *localMax = 0;
//        }
//        byte <<= 1;
//    }
//    return *localMax;
//
//}
//
//
//int main(int argc, char **argv){
//
//    if(argc != 2){
//        printf("%s\n", "USAGE: ./ccseq filename"); // filename is fixed or?
//        exit(1);
//    }
//
//    // handle open file failure
//    char *filename = argv[1];
//    int fd = open(filename, O_RDONLY); //Read Only
//
//    if(fd == -1){
//        perror(filename);
//        exit(2);
//    }
//
//    char buffer[1024]; // depend on the size, could run into problems
//    int globalMax = 0 , localMax =0;
//
//    while (1) {
//        int rc = read(fd, buffer, sizeof buffer);
//        if (rc == 0){
//            break;
//        }
//
//        for (int i = 0; i < rc; i++) {
//            char byte = buffer[i];
//            localMax = byteWise(byte, &localMax, &globalMax);
//
//        }
//    }
//
//
//    printf("%d\n", globalMax);
//    exit(0);
//
//}
//
//
///*--
// #include <stdio.h>
//#include "stdlib.h"
//#include <fcntl.h> // file control options
//#include <unistd.h>// Standard symbolic constant and types
//#include <tic.h>
//#include "string.h"
//void plusOne(int *someInt){
//    *someInt = *someInt + 1;
//}
//
//void updateMax(int *localMax, int *globalMax){
//    if (*localMax > *globalMax)
//        *globalMax = *localMax;
//}
//
//int byteWise(char byte, int *localMax, int *globalMax){
//    for (int i = 0; i < 8; ++i) {
//        if((byte & 128) == 0 ) {
//            *localMax = *localMax + 1;
//            updateMax(localMax, globalMax);
//
//        } else{
//            *localMax = 0;
//        }
//        byte <<= 1;
//    }
//    return *localMax;
//
//}
//
//int main(int argc, char **argv) {
//    char *filename = "/Users/swift/CLionProjects/untitled/filewithholes.txt";
//    int fd = open(filename, O_RDONLY);//Read Only
//
//    if(fd == -1){
//        perror(filename);
//        exit(2);
//    }
//    char buffer[10]; // depend on the size, could run into problems
//    int globalMax = 0 , localMax =0;
//
//    while (true) {
//        int rc = read(fd, buffer, sizeof buffer);
//        if (rc == 0){
//            break;
//        }
//
//        for (int i = 0; i < rc; i++) {
//            char byte = buffer[i];
//            localMax = byteWise(byte, &localMax, &globalMax);
//
//        }
//    }
//
//
//
//
//
//
//
//
////    printf("%s",byte);
//
//
//    printf("%s%d", "global max is:", globalMax);
//    close(fd);
//    exit(0);
//}
//
// */