#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Erro ao criar o pipe");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("Erro ao criar o primeiro processo filho");
        exit(1);
    } else if (pid1 == 0) {
        // Primeiro processo filho (ls /etc)
        close(pipe_fd[0]); // Fecha o descritor de leitura no pipe
        dup2(pipe_fd[1], 1); // Redireciona o standard output para o descritor de escrita do pipe
        close(pipe_fd[1]); // Fecha o descritor de escrita no pipe
        execlp("ls", "ls", "/etc", NULL); // Executa o comando ls
        perror("Erro ao executar ls");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("Erro ao criar o segundo processo filho");
        exit(1);
    } else if (pid2 == 0) {
        // Segundo processo filho (wc -l)
        close(pipe_fd[1]); // Fecha o descritor de escrita no pipe
        dup2(pipe_fd[0], 0); // Redireciona o standard input para o descritor de leitura do pipe
        close(pipe_fd[0]); // Fecha o descritor de leitura no pipe
        execlp("wc", "wc", "-l", NULL); // Executa o comando wc -l
        perror("Erro ao executar wc");
        exit(1);
    }

    // Processo pai
    close(pipe_fd[0]); // Fecha o descritor de leitura no pipe
    close(pipe_fd[1]); // Fecha o descritor de escrita no pipe
    wait(NULL); // Espera pelo término do primeiro processo filho
    wait(NULL); // Espera pelo término do segundo processo filho

    return 0;
}
