#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define SAIDA "etc/saida.txt"
#define ERROS "etc/erros.txt"
#define ENTRADA "etc/passwd"


int main() {
    // Abrir os ficheiros etc/passwd
    int fd_in = open(ENTRADA, O_RDONLY);
    int fd_out = open(SAIDA, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd_err = open(ERROS, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_err < 0 || fd_out < 0 || fd_in < 0) {
        perror("Erro ao abrir ficheiros");
        close(fd_in);
        close(fd_out);
        close(fd_err);
        exit(1);
    }

    // Redirecionar o standard input para /etc/passwd
    if (dup2(fd_in, 0) < 0) {
        perror("Erro ao redirecionar o standard input");
        close(fd_in);
        close(fd_out);
        close(fd_err);
        exit(1);
    }

    int fdSTDOUT = dup(1);

    // Redirecionar o standard output para saida.txt
    if (dup2(fd_out, 1) < 0) {
        perror("Erro ao redirecionar o standard output");
        close(fd_in);
        close(fd_out);
        close(fd_err);
        exit(1);
    }

    // Redirecionar o standard error para erros.txt
    if (dup2(fd_err, 2) < 0) {
        perror("Erro ao redirecionar o standard error");
        close(fd_in);
        close(fd_out);
        close(fd_err);
        exit(1);
    }

    // Fechar os ficheiros originais, pois já foram duplicados
    close(fd_in);
    close(fd_out);
    close(fd_err);

    pid_t pid = fork();
    if (pid < 0) {
        perror("Erro ao criar o processo filho");
        exit(1);
    } else if (pid == 0) {
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(0, buffer, sizeof(buffer))) > 0) {
            write(1, buffer, bytes_read);
            write(2, buffer, bytes_read);
        }

        if (bytes_read < 0) {
            perror("Erro ao ler do standard input");
            exit(1);
        }
        _exit(0);
    } else {
        // Processo pai
        // Esperar pelo processo filho
        wait(NULL);
    }



    dup2(fdSTDOUT, 1);
    close(fdSTDOUT);
    printf("Terminei\n");
    

    return 0;
}
