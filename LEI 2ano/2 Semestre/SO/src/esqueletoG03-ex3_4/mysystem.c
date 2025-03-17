#include "mysystem.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem(const char* command) {
    int res = -1;
    char *copia = strdup(command);
    char *args[100];

    int i = 0;
    for (i = 0; copia != NULL; i++) {
        args[i] = strsep(&copia, " ");
    }
    args[i] = NULL;

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return res;

    } else if (pid == 0) {
        execvp(args[0], args);
        _exit(-1);

    } else {
        free(copia);
        int status;

        if (wait(&status) >= 0 && WIFEXITED(status)) res = WEXITSTATUS(status) == 255 ? 1 : WEXITSTATUS(status);
    }

    return res;
}