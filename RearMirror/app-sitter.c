//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <unistd.h>
//#include <string.h>
//
//void printArr(char **arr){
//    for (int i = 0; i < sizeof arr; ++i) {
//        printf("%s\n", arr[i]);
//    }
//}
//
//int main(int argc, char **argv){
//
//    if(argc == 1){
//        printf("%s\n", "USAGE: ./app-sitter program0 space_separated_args0 . program1 space_separated_args1 ...");
//        //exit(1);
//    }
//    char** cmd[5] = {"1 ", " 2", " 3"};
//
//    for (int i = 1; i < argc; i++){
//        const char *seperator = '.';
//        int j = 0;
//        while (strcmp(argv[i], seperator) == 0) {
//            cmd[i] = argv[i];
//            j++;
//            i++;
//        }
//        printArr(cmd);
//    }
//
//
//    //    printf("Hey world\n");
//
////
////    pid_t child = fork();
////
////    if(child == 0){
////        printf("%s", "Child\n");
////        char *cmd[] = {"echo-wrong", "hi"};
////        execvp(cmd[0], cmd);
////
////    } else{
////        execvp("sleep", 3);
////
////        printf("parent\n");
////    }
//
////    printf("started\n");
////    pid_t c = fork();
////    if (c == 0) {
////        char *cmd[3] = {"echo", "hi", NULL};
////        char *argv[3];
////        argv[0] = "echo";
////        argv[1] = "hahah";
////        argv[2] = NULL;
////
////        execvp(cmd[0], cmd);
////        printf("child problem\n");
////        exit(1);
////    }
////    printf("waiting for the child\n");
////    int status;
////    pid_t finished = wait(&status);
////    printf("%d finished\n", finished);
//}