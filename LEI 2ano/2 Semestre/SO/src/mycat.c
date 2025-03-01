#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            perror("open");
            return 1;
        }

        char buffer[1024];
        ssize_t bytesRead;
        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytesRead);
        }

        if (bytesRead == -1) {
            perror("read");
        }

        close(fd);
        write(STDOUT_FILENO, "\n", 1);
    } else if (argc == 3) {
        int fd1 = open(argv[1], O_RDONLY);
        int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
        if (fd1 == -1 || fd2 == -1) {
            perror("open");
            return 1;
        }

        char buffer[1024];
        ssize_t bytesRead;
        while ((bytesRead = read(fd1, buffer, sizeof(buffer))) > 0) {
            write(fd2, buffer, bytesRead);
        }

        if (bytesRead == -1) {
            perror("read");
        }

        close(fd1);
        close(fd2);
        
    } else {
        fprintf(stderr, "Usage: %s <source> [destination]\n", argv[0]);
        return 1;
    }

    return 0;
}