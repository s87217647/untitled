////
//// Created by Swift Sheng on 8/30/22.
////
//#include <stdio.h>
//#include "stdlib.h"
//#include "string.h"
//
//int main(int argc, char** argv){
//    int ans = 0;
//    char *ptr;
//    int invalidCount = 0;
//
//    for(int i = 1; i < argc; i++) {
//        long result = strtol(argv[i], &ptr, 10);
//        if (*ptr) {
//            fprintf(stderr, "%s %s\n", "skipping", argv[i]);
//            invalidCount++;
//        }
//    }
//
//    if (invalidCount == argc - 1) {
//        printf("%s\n", "USAGE: ./addup numbers ...");
//        return ans;
//    }
//
//
//    for(int i = 1; i < argc; i++){
//        long result = strtol(argv[i], &ptr, 10);
//        if (!*ptr){
//        ans += result;
//        }
//    }
//
////    if(argc == 0) {
////        printf("%s\n" );
////    }
////
////    int answer = 0;
////    for(int i = 1; i < sizeof (argv); i ++){
////        answer += argv[i];
////    }
////    printf("%d \n",ans);
//    printf("%d\n", ans);
//    return 0;
//}