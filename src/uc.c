//
// Created by Swift Sheng on 11/20/22.
//
#include "stdlib.h"
#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include <fcntl.h> // file control options
#include <unistd.h>// Standard symbolic constant and types
#include "string.h"
#include <stdbool.h>


// concurrent list and hashtable comes from the book
typedef struct __node_t {
    char* str;
    struct __node_t *next;
} node_t;

typedef struct __list_t{
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L){
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}



bool exist(list_t *L, char* str) {
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (strcmp(curr->str, str) == 0) {
            pthread_mutex_unlock(&L->lock);
            return true; // exist
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return false; // doesn't exist
}

int List_Insert(list_t *L, char* str) {
    if(exist(L, str)){
        return 0;
    }
    pthread_mutex_lock(&L->lock);
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        pthread_mutex_unlock(&L->lock);
        return 0; // fail
    }
    new->str = malloc(sizeof str);
    strcpy(new->str, str);
    new->next = L->head;
    L->head = new;
    pthread_mutex_unlock(&L->lock);
    return 1; // success
}

int Print_List(list_t* L){
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        printf("%s\n", curr->str);
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
}





//-----Below is the hash table ------
#define BUCKETS (256)
typedef struct __hash_t {
    list_t lists[BUCKETS];
} hash_t;

void Hash_Init(hash_t *H) {
    for (int i=0;i<BUCKETS;i++){
        List_Init(&H->lists[i]);
    }
}

int hash(const char* s) {
    const int p = 31, m = 1e9 + 7;
    int hash = 0;
    long p_pow = 1;
    for(int i = 0; i < strlen(s); i++) {
        hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash;
}

int Hash_Insert(hash_t *H, char* str) {
    int bucket =  hash(str)% BUCKETS;
    return List_Insert(&H->lists[bucket], str);
}
int Hash_Lookup(hash_t *H, char* str) {
    int bucket = hash(str) % BUCKETS;
    return exist(&H->lists[bucket], str);
}

int readAndInsert(char* path, hash_t* h){
    FILE* filePtr = fopen(path, "r");
    if (filePtr == NULL){
        printf("%s: No such file or directory\n", path);
        exit(1);
    }

    char buf[100];
    int count = 0;

    while (fscanf(filePtr, "%s", buf) == 1) {
        count += Hash_Insert(h, buf);
    }

    return count;
}

int listReadAndInsert(char* path, list_t * l){
    FILE* filePtr = fopen(path, "r");
    if (filePtr == NULL){
        printf("%s: No such file or directory\n", path);
        exit(1);
    }

    char buf[100];
    int count = 0;

    while (fscanf(filePtr, "%S", buf) == 1) {
        count += List_Insert(l, buf);
    }

    return count;
}




int main(int argc, char** argv) {

    struct hash_t *h = malloc(sizeof (hash_t));
    Hash_Init(h);

//    printf("count is: %d", readAndInsert(argv[1], h));


    struct list_t  *l = malloc(sizeof (list_t));
    List_Init(l);

    printf("count is: %d\n", listReadAndInsert(argv[1], l));
    printf("count is: %d\n", listReadAndInsert(argv[2], l));
    printf("count is: %d\n", listReadAndInsert(argv[3], l));

    Print_List(l);



//todo: free everything before returning the value

}




