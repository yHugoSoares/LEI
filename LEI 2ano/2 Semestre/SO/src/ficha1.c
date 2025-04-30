#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, const char *argv[]) {
    
    if (argc < 1) {
        printf("Usage: %s <processes>\n", argv[0]);
        return 1;
    }

    int no_children = atoi(argv[1]);

    for (int i = 0; i < no_children; i++)
    {
        pid_t pid = fork();
        if (pid < 0) perror("On fork");
        else if (pid == 0) {
            printf("I am the child %d (i: %d) || My parent is: %d\n", getpid(), i, getppid());
            _exit(0);
        }
        else {
            int status;
            wait(&status);
            if (WIFEXITED(status)) printf("The child %d has finished\n", WEXITSTATUS(status));
        }
    }
    
    
    


}