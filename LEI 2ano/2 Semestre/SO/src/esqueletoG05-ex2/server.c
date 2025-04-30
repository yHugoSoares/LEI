#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

int main (int argc, char * argv[]){

	init_vector();
	print_vector();

	int fd = open(SERVER, O_RDONLY);
    int fd_write = open(CLIENT, O_WRONLY);

    printf("Reading from FIFO...\n");

    char buf[BUFFERSIZE];
    
    // DOESNT TERMINATE
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buf, BUFFERSIZE)) > 0) {
        write(1, buf, bytesRead);
        printf(".");
    }
    close(fd);
	
	return 0;
}
