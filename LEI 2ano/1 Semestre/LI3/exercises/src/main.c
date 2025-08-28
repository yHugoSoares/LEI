#include "deque.h"
#include "command_parser.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


//==============
//Esta resolução mostra como exemplo uma deque que guarda valores do tipo int. 
//==============


/* Operations to test the deque */
typedef enum dequeOp {
    PUSH,
    PUSH_FRONT,
    POP,
    POP_FRONT,
    REVERSE,
    SIZE,
    IS_EMPTY
} DequeOp;



/* Returns a random DequeOp */
DequeOp randomOp() {
    return rand() % 7;
}


/* Allocates and returns a random integer between 0 and 99 */
int* randomInt() {
    int* data = malloc(sizeof(int));
    *data = rand() % 100;
    return data;
}

/* Prints the value of an integer pointer */
void printInt(void* i) {
    int* i_ = i;
    printf("%d", *i_);
}

/* Tests a deque of integers */
void testDeque(int nOps) {
    /* initial deque with three random elements */
    Deque* deque = create();
    push(deque, randomInt());
    push(deque, randomInt());
    push(deque, randomInt());

    printf("Initial deque: ");
    printDeque(deque, &printInt);
    printf("\n");

    /* do nOps random operations on the deque */
    for (int i = 0; i < nOps; i++) {
        DequeOp op = randomOp();
        int* data = NULL;

        switch (op) {
        case PUSH:
            data = randomInt();
            printf("PUSH(%d) = ", *data);
            push(deque, data);
            break;
        
        case PUSH_FRONT:
            data = randomInt();
            printf("PUSH_FRONT(%d) = ", *data);
            pushFront(deque, data);
            break;

        case POP:
            printf("POP = ");
            data = pop(deque);
            if (data) {
                free(data);
            }
            break;

        case POP_FRONT:
            printf("POP_FRONT = ");
            data = popFront(deque);
            if (data) {
                free(data);
            }
            break;

        case REVERSE:
            printf("REVERSE = ");
            reverse(deque);
            break;

        case SIZE:
            printf("SIZE: %d ", size(deque));
            break;

        case IS_EMPTY:
            printf("IS_EMPTY: %d ", isEmpty(deque));
            break;
        }

        printDeque(deque, &printInt);
        printf("\n");
    }

    /* free any remaining elements */
    int* data = pop(deque);
    while (data) {
        free(data);
        data = pop(deque);
    }

    destroy(deque);
}

/* Main */
int main(int argc, char **argv) 
{
    Deque* deque = create();
    if (argc < 2) 
    {
        fprintf(stderr, "Missing filename.\n");
        return 1;
    }

    char* filename = argv[1];
    FILE* fp = fopen(filename, "r");
    
    if (!fp) 
    {
        perror("Error"); // imprime "Error: No such file or directory" caso o ficheiro n~ao exista
        return 2;
    }

    char* line = NULL;
    ssize_t read;
    size_t len; // Ser´a definido pela fun¸c~ao getline quando alocar espa¸co para a string
    while ((read = getline(&line, &len, fp)) != -1) 
    {
        Cmd* command = parseLine(line);
        processCommand(deque, command);
    }
    // free(line); // ´E preciso libertar a mem´oria alocada

    // char str[100];
    // while(fgets(str, 100, fp)) 
    // {
    //     printf("%s", str);
    // }
    
    printf("\n");
    fclose(fp);
    return 0;
}