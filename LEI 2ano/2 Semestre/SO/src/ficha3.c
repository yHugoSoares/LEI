#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char* argv[]) {
    
    int value = 10;

    int pd[2];
    int pipereturn = pipe(pd);
    if (pipereturn == -1) {
        perror("pipe");
        return -1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return -1;

    } else if (pid == 0) {
        close(pd[1]);
        int received = 0;
        read(pd[0], &received, sizeof(received));
        printf("Received value %d\n", received);
        close(pd[0]);
    } else {
        close(pd[0]);
        sleep(5);
        write(pd[1], &value, sizeof(value));
        printf("Sent value %d\n", value);
        close(pd[1]);
    }

    
}
