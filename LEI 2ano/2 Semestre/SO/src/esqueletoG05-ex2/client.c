#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

int main (int argc, char * argv[]){

	if (argc < 2) {
		printf("Missing argument.\n");
		_exit(1);
	}

	int fd = open(CLIENT, O_WRONLY);
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

