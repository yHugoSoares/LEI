#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define NOT_FOUND 255


int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);

    int *vector = (int *)malloc(ROWS * sizeof(int));
    

    int value = atoi(argv[1]);
    for (int i = 0; i < ROWS; i++)
    {
        pid_t pid = fork();
        if (pid < 0) { 
            perror("On fork"); 
            exit(1);
        }
        else if (pid == 0) {
            for (int j = 0; j < COLUMNS; j++)
            {
                if (matrix[i][j] == value) _exit(i);
            }
            _exit(NOT_FOUND); 
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            int result = WEXITSTATUS(status);
            if (result < ROWS) {
                printf("Found %d in line %d\n", value, result);
            }
        }
    }
    
    
    

    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}