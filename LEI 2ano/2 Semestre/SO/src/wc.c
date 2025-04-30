#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Erro ao criar o pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Erro ao criar o processo filho");
        exit(1);
    } else if (pid == 0) {
        // Processo filho
        close(pipe_fd[1]); // Fecha o descritor de escrita no pipe
        dup2(pipe_fd[0], 0); // Redireciona o standard input para o descritor de leitura do pipe
        close(pipe_fd[0]); // Fecha o descritor de leitura do pipe
        execlp("wc", "wc", NULL); // Executa o comando wc
        perror("Erro ao executar wc");
        exit(1);
    } else {
        // Processo pai
        close(pipe_fd[0]); // Fecha o descritor de leitura no pipe
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            write(pipe_fd[1], buffer, strlen(buffer)); // Envia dados para o pipe
        }
        close(pipe_fd[1]); // Fecha o descritor de escrita no pipe para sinalizar EOF
        wait(NULL); // Espera pelo término do processo filho
    }

    return 0;
}
