#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFERSIZE 1024

int main(int argc, char const *argv[]) {

    int fd = open("bin/fifo", O_RDONLY);
    int fd_write = open("bin/fifo", O_WRONLY);

    printf("Reading from FIFO...\n");

    char buf[BUFFERSIZE];
    
    // DOESNT TERMINATE    
    
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buf, BUFFERSIZE)) > 0) {
        write(1, buf, bytesRead);
    }
    close(fd);

    return 0;
}