#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) perror("Could not create a child process\n");
    else if (pid == 0) printf("I am the child process: %d\n", getpid());
    else {
        printf("I am the parent process: %d\n", getpid());
        printf("Childs proccess received by father: %d\n", pid);
        pid_t pid2 = fork();
        if (pid2 < 0) perror("Could not create a child process\n");
        else if (pid2 == 0) printf("I am the child process: %d\n", pid2);
        else {
            printf("I am the parent process: %d\n", getpid());
            printf("Childs proccess received by father: %d\n", pid2);
        }

    }
    
    return 0;
}