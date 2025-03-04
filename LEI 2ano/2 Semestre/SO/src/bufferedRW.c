#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFSIZE 4096

ssize_t bufferedWrite (int fd, void* buf, size_t size) {
    if (fd < 0) return -1;
    if (size < 0) perror("Invalid size\n");
    if (buf == NULL) perror("Invalid buffer\n");
    ssize_t bytesWritten = 0;
    for (int i = 0; i * BUFSIZE < size; i++)
    {
        bytesWritten += write(fd, buf + i * BUFSIZE, BUFSIZE);
        if (bytesWritten < 0) perror("Could not write from file\n");
    }
    if (bytesWritten < size) {
        bytesWritten += write(fd, buf + bytesWritten, size - bytesWritten);
        if (bytesWritten < 0) perror("Could not write from file\n");
    }

    return bytesWritten;
}

ssize_t bufferedRead (int fd, void* buf, size_t size) {
    if (fd < 0) return -1;
    if (size < 0) perror("Invalid size\n");
    if (buf == NULL) perror("Invalid buffer\n");
    ssize_t bytesRead = 0;
    for (int i = 0; i * BUFSIZE < size; i++)
    {
        bytesRead += read(fd, buf + i * BUFSIZE, BUFSIZE);
        if (bytesRead < 0) perror("Could not read from file\n");
    }
    if (bytesRead < size) {
        bytesRead += read(fd, buf + bytesRead, size - bytesRead);
        if (bytesRead < 0) perror("Could not read from file\n");
    }

    return bytesRead;
}