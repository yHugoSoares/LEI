#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

    mkfifo("bin/fifo", 0666);
    printf("Creating FIFO...\n");

    return 0;
}