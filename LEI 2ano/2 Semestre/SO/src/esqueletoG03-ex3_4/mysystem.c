#include "mysystem.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem(const char* command) {
    int res = -1;

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return res;

    } else if (pid == 0) {
        execlp("sh", "sh", "-c", command, NULL);
        perror("execlp");
        _exit(-1);

    } else {
        int status;
        if (wait(&status) == -1) {
            perror("wait");
            return res;

        }
        if (WIFEXITED(status)) res = WEXITSTATUS(status);
    }

    return res;
}