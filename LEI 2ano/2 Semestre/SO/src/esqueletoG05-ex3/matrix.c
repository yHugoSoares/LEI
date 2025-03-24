#include "matrix.h"


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void lookupNumber(int** matrix, int value, int* vector) {
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pid;
    for (int i = 0; i < ROWS; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Filho
            close(pipefd[0]); // Fecha o descritor de leitura no filho
            int count = 0;
            for (int j = 0; j < COLUMNS; j++) {
                if (matrix[i][j] == value) {
                    count++;
                }
            }
            write(pipefd[1], &count, sizeof(count)) != sizeof(count);
            close(pipefd[1]);
            exit(0);
        }
    }

    // Pai
    close(pipefd[1]); // Fecha o descritor de escrita no pai
    for (int i = 0; i < ROWS; i++) {
        int count;
        read(pipefd[0], &count, sizeof(count)) != sizeof(count);
        vector[i] = count;
    }
    close(pipefd[0]);

    // Espera todos os filhos terminarem
    for (int i = 0; i < ROWS; i++) {
        wait(NULL);
    }
}
