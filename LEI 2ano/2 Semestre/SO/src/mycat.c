#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 2)
    {
        for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            perror("fopen");
        }

        int c;
        while ((c = fgetc(file)) != EOF) {
            putchar(c);
        }

        fclose(file);
        }
        putchar('\n');
    }
    if (argc == 3)
    {
        FILE *file = fopen(argv[1], "r");
        FILE *file2 = fopen(argv[2], "w");
        if (file == NULL) {
            perror("fopen");
        }

        int c;
        while ((c = fgetc(file)) != EOF) {
            fputc(c, file2);
        }

        fclose(file);
        fclose(file2);
    }
    
    

    

    return 0;
}