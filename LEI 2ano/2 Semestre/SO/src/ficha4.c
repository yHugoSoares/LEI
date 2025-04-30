#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // filho
        close(pipefd[0]);
        int values[5] = {1, 2, 3, 4, 5};
        for (int i = 0; i < 5; i++) {
            printf("Sent value %d\n", values[i]);
            write(pipefd[1], &values[i], sizeof(values[i]));
        }
        close(pipefd[1]);
    } else {
        // pai
        close(pipefd[1]);
        int values[5];
        for (int i = 0; i < 5; i++) {
            read(pipefd[0], &values[i], sizeof(values[i]));
        }
        for (int i = 0; i < 5; i++)
        {
            printf("Received value %d\n", values[i]);
        }
        
        close(pipefd[0]);
        wait(NULL);
    }
    return 0;
}