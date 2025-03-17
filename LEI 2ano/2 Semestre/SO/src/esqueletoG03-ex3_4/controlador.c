#include <stdio.h>
#include "mysystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "mysystem.h"

void controller(int N, char** commands) {
    int exec_counts[N];
    memset(exec_counts, 0, sizeof(exec_counts));

    pid_t pids[N];

    for (int i = 0; i < N; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork");
            exit(1);
        } else if (pids[i] == 0) {
            while (1) {
                int res = mysystem(commands[i]);
                exec_counts[i]++;
                if (res == 0) {
                    _exit(0);
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        int status;
        waitpid(pids[i], &status, 0);
    }

    for (int i = 0; i < N; i++) {
        printf("%s %d\n", commands[i], exec_counts[i]);
    }
}

int main(int argc, char* argv[]) {

    char *commands[argc-1];
    int N = 0;
	for(int i=1; i < argc; i++){
		commands[N] = strdup(argv[i]);
		printf("command[%d] = %s\n", N, commands[N]);
        N++;
	}

    controller(N, commands);

	return 0;
}