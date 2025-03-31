#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFERSIZE 1024

int main(int argc, char const *argv[]) {

    int fd = open("bin/fifo", O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("Writing to FIFO...\n");

    char buf[BUFFERSIZE];
    ssize_t bytesRead;
    while ((bytesRead = read(0, buf, BUFFERSIZE)) > 0) 
        write(fd, buf, bytesRead);
    
    close(fd);

    return 0;
}