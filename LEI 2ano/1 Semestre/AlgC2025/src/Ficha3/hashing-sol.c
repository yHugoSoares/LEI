#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "hashing.h"

int hash_sol(char key[], int size) {

    int i = 0, sum = 0;
    while (key[i] != '\0') { sum += key[i]; i++; }
    return sum % size;
}


void initHT_sol(HT *h, int size) {
    int i;
    h->tbl = calloc(size, sizeof(struct pair));
    h->size = size;
    h->used = 0;
    for (i=0; i<size; i++) strcpy(h->tbl[i].key, EMPTY);
}

int freeHT_sol(HT *h, int k) {
    if (strcmp(h->tbl[k].key, EMPTY) == 0) return 1;
    if (strcmp(h->tbl[k].key, DELETED) == 0) return 1;
    return 0;
}

int writeHT_sol(HT *h, char key[], int value){
    float load = h->used / h->size;
    
    int i = hash(key, h->size);
    
    while (!freeHT_sol(h, i)) {
        i = (i + 1) % h->size;
        printf("* ");
    }

    strcpy(h->tbl[i].key, key);
    h->tbl[i].value = value;
    h->used++;

    return i;
}

int readHT_sol(HT *h, char key[]) {
    int i = hash(key, h->size);
    int start = i;

    while (strcmp(h->tbl[i].key, EMPTY) != 0) {
        if (strcmp(h->tbl[i].key, key) == 0) {
            return h->tbl[i].value;
        }
        i = (i + 1) % h->size;
        if (i == start) break; // Avoid infinite loop
    }

    return -1; // Not found
}