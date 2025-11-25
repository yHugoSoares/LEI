
//
//  hashing.c
//  Hashing
//
//  Created by Jorge Sousa Pinto on 22/11/17.
//  Copyright © 2017 Jorge Sousa Pinto. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "hashing.h"


int hash(char key[], int size) {

    return hash_sol(key, size);
}


void initHT(HT *h, int size) {
 
    initHT_sol(h, size);
}


int freeHT(HT *h, int k) {
    
    return freeHT_sol(h, k);
}



int writeHT (HT *h, char key[], int value) {

    return writeHT_sol (h, key, value);
}



int readHT (HT *h, char key[], int* value) {
    
    return readHT_sol (h, key, value);
}



int deleteHT (HT *h, char key[]) {

    return deleteHT_sol (h, key);
}
