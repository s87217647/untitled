//
// Created by Swift Sheng on 10/25/22.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "bigbag.h"
#include "endian.h"

struct bigbag_entry_s *entry_addr(void *hdr, uint32_t offset) {
    if (offset == 0) return NULL;
    return (struct bigbag_entry_s *)((char*)hdr + offset);
}

uint32_t entry_offset(void *hdr, void *entry) {
    return (uint32_t)((uint64_t)entry - (uint64_t)hdr);
}

void myStrCpy(char *src, char *dest){
    while (*src != '\n'){
        *dest = *src;
        src++;
        dest++;
    }

}



int main(int arc, char** argv){
    if (arc == 1){
        printf("%s\n", "USAGE: ./bigbag [-t] filename");
        exit(1);
    }


    int fd = open(argv[1], O_RDWR);
    if(fd == -1)fd = open(argv[1], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

    ftruncate(fd, 0);//TODO: remember to delete this
    ftruncate(fd,BIGBAG_SIZE);
    void *file_base = mmap(0, BIGBAG_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);


    struct stat stat;
    fstat(fd, &stat);
    struct bigbag_hdr_s *hdr = file_base;



    size_t charCount;
    char *userInput = NULL;
    size_t  zero = 0;
    char* trimedInput;
    char firstChar;
    size_t  validUserInputLen;


    while ((charCount = getline(&userInput, &zero, stdin)) != -1){
        struct bigbag_entry_s *current;
        int offset = sizeof(*hdr);

        switch (userInput[0]) {
            case 'a':
                if(strlen(userInput) > 3){validUserInputLen =  strlen(userInput) - 3;} else{break;}

                if(hdr->first_element == 0){
                    hdr->magic = BIGBAG_MAGIC;
                    hdr->first_element = offset; // Linked list, header
                    hdr->first_free += offset;
                }

                struct bigbag_entry_s *newNode = entry_addr(hdr, hdr->first_free);

                newNode->entry_magic = BIGBAG_USED_ENTRY_MAGIC;
                newNode->entry_len = validUserInputLen;
                myStrCpy(&userInput[2], newNode->str);
                printf("added %s\n", newNode->str);

                hdr->first_free += sizeof newNode + validUserInputLen;
                newNode->next = hdr->first_free;



                struct bigbag_entry_s *head = entry_addr(hdr, hdr->first_element);
                struct bigbag_entry_s *next, *previous;
                previous = head;
                current = head;

                while((next = entry_addr(hdr, current->next))->next != 0){
                    if ( (strcmp(current->str, newNode->str) > 0)&& ((strcmp(current->str, newNode->str) > 0)){

                    }

                    previous = current;
                    current = next;
                }
                break;

            case 'c':
                trimedInput = userInput + 2;

                while(offset < BIGBAG_SIZE){
                    current = entry_addr(hdr, offset);

                    if (current == NULL) break;

                    char *strWithEOL = malloc(current->entry_len + 2); // +1 for the null-terminator
                    strcpy(strWithEOL, current->str);
                    strcat(strWithEOL, "\n");

                    if(current->entry_magic == BIGBAG_USED_ENTRY_MAGIC){
                        if (strcmp(trimedInput, strWithEOL) == 0 ) {
                            printf("found\n");
                            break;
                        }
                    }

                    offset = current->next;
                    free(strWithEOL);
                }
                if (current == NULL) printf("not found\n");

                break;

            case 'd':
                break;


            case 'l':
                    if(hdr->first_element == 0){
                        printf("empty bag\n");
                        break;
                    }

                    while(offset < BIGBAG_SIZE){
                        current = entry_addr(hdr, offset);
                        if (current == NULL) break;

                        if(current->entry_magic == BIGBAG_USED_ENTRY_MAGIC){
                            printf("%s\n", current->str);
                        }
                        offset = current->next;
                    }

                    break;




            default:
                printf("%c not used correctly\n"
                       "possible commands:\n"
                       "a string_to_add\n"
                       "d string_to_delete\n"
                       "c string_to_check\n"
                       , userInput[0]);


        }


//        printf("charCount is %zu\n", charCount);
//        printf("You typed: %s \n", userInput);



    }
    free(userInput);
    exit(0);
}