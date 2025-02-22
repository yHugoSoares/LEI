#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    time_t start = time(NULL);

    if (argc < 4)
    {
        perror("Usage: mycp <file1> <file2> <buffer_size>");
        return 1;
    }
    
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        perror("open");
        return 1;
    }

    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 == -1) {
        perror("open");
        return 1;
    }

    int buffer_size = atoi(argv[3]);
    char buf[buffer_size];
    ssize_t nread;
    while ((nread = read(fd1, buf, buffer_size)) > 0) {
        if (write(fd2, buf, nread) != nread) {
            perror("write");
            return 1;
        }
    }
    close(fd1);
    close(fd2);

    time_t end = time(NULL);
    printf("Time: %ld seconds\n", end - start);
    return 0;
}