//// Copyright 2022 Terence Kelly, all rights reserved.
//// Persistent memory programming example:  The essence of "laying out
//// data structures in a file-backed memory mapping" is simply casting
//// the return value of mmap() to a pointer to an application-defined
//// data type.
//
//#include <errno.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/mman.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//
//#define S2(s)      #s
//#define S1(s)      S2(s)
//#define COORDS     __FILE__ ":" S1(__LINE__) ": "
//#define FP(...)    (void)fprintf(stderr, __VA_ARGS__)
//#define DIE(r,...) do { FP(COORDS __VA_ARGS__);                   \
//                        if (errno) FP(": %s\n", strerror(errno)); \
//                        else       FP("\n");                      \
//                        exit(r); } while (0)
//
//int main(int argc, char *argv[]) {
//  int fd;  size_t fsz;  struct stat s;
//  struct foo { int bar; double qux; } *foop;
//  if (2 != argc)                        DIE(1, "usage: %s file", argv[0]);
//  if (0 > (fd = open(argv[1], O_RDWR))) DIE(2, "open '%s'",      argv[1]);
//  if (fstat(fd, &s))                    DIE(3, "fstat '%s'",     argv[1]);
//  fsz = (size_t)s.st_size;
//  foop = (struct foo *)
//         mmap(NULL, fsz, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//  if (MAP_FAILED == foop) DIE(4, "mmap");
//  if (foop->bar)
//    foop->qux += 47.0;
//  foop->bar++;
//  printf("size %zd  foop->bar == %d  foop->qux == %f\n",
//               fsz, foop->bar,       foop->qux);
//  return 0;
//}
