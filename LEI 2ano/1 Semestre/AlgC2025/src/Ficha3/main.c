/* Main function of the C program. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashing.h"

int main(int argc, const char * argv[]) {

    HT h;
    int i, r, v;
    char* characters[] = {"Akamaru", "Sai", "Yamata", "Itachi", "Gaara", 
    "Hinata", "Sasuke", "Naruto", "Sakura", "Kakashi", "Gae"};
    
    initHT(&h, 11);

    // Inserts all elements in characters
    printf("** INSERTIONS **\n");
    for (i = 0; i < 11; i++) {
        writeHT(&h, characters[i], strlen(characters[i]));
        printf("%s inserted\n", characters[i]);
    }

    // Looks up all elements in characters
    printf("**  LOOKUPS **\n");
    for (i = 0; i < 11; i++) {
        r = readHT(&h, characters[i], &v);
        if (r >= 0) printf("(%8s, %d ) at index %d\n", characters[i], v, r);
        else printf("%s not found\n", characters[i]);
    }
    
    // Deletes elements in even positions of characters
    printf("** REMOVALS **\n");
    for (i = 0; i < 11; i += 2) {
        r = deleteHT(&h, characters[i]);
        if (r >= 0) printf("%s deleted\n", characters[i]);
        else printf("%s not found\n", characters[i]);
    }

    printf("** DUMP: **\n");
    for (i = 0; i < h.size; i++) {
        if ((h.tbl)[i].key != NULL) // Only print occupied slots
            printf("%s, %d\n", (h.tbl)[i].key, (h.tbl)[i].value);
    }
    
    // Inserts elements that have been removed
    printf("** REINSERTIONS **\n");
    for (i = 0; i < 11; i += 2) {
        writeHT(&h, characters[i], strlen(characters[i])); // Use strlen for consistency
        printf("%s inserted\n", characters[i]);
    }

    printf("** DUMP AFTER REINSERTIONS: **\n");
    for (i = 0; i < h.size; i++) {
        if ((h.tbl)[i].key != NULL)
            printf("%s, %d\n", (h.tbl)[i].key, (h.tbl)[i].value);
    }

    return 0;
}