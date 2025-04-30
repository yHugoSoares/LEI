#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        printf("Usage: ./ficha3 <command> <argument(s)>\n");
        return 1;
    }
    
    pid_t pid = fork();
    if (pid == 0) {
        int success = execlp(argv[1], argv[1], argv[2], NULL);
        if (success == -1)
        {
            perror("Error: command not found\n");
        }
    }
    wait(NULL);
    
    
    printf("Done\n");
    
    
    return 0;
}