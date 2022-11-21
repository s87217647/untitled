////
//// Created by Swift Sheng on 10/26/22.
////
//// Copyright 2022 Terence Kelly, all rights reserved.
//// mmap example:  replace "abc" -> "ABC"
//#include <errno.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/mman.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#define S2(s)      #s
//#define S1(s)      S2(s)
//#define COORDS     __FILE__ ":" S1(__LINE__) ": "
//#define FP(...)    (void)fprintf(stderr, __VA_ARGS__)
//#define DIE(r,...) do { FP(COORDS __VA_ARGS__);                   \
//                        if (errno) FP(": %s\n", strerror(errno)); \
//                        else       FP("\n");                      \
//                        exit(r); } while (0)
//int main(int argc, char *argv[]) {
//    int fd;  size_t fs;  struct stat s;
//    char *start, *end, *p;
//    if (2 != argc)                        DIE(1, "usage: %s file", argv[0]);
//    if (0 > (fd = open(argv[1], O_RDWR))) DIE(2, "open '%s'",      argv[1]);
//    if (fstat(fd, &s))                    DIE(3, "fstat '%s'",     argv[1]);
//    fs = (size_t)s.st_size;
//    start = (char *)
//            mmap(NULL, fs, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//    if (MAP_FAILED == start) DIE(4, "mmap");
//    end = start + fs - 2;
//    for (p = start; p < end; p++)  // access persistent data in file...
//        if ('a'==p[0] && 'b'==p[1] && 'c'==p[2])  {  // ...via LOADs...
//            p[0] = 'A';  p[1] = 'B';  p[2] = 'C'; }  // ...and STOREs
//    return 0;
//}