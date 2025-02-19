#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        int c;
        while ((c = fgetc(file)) != EOF) {
            putchar(c);
        }

        fclose(file);
    }
    putchar('\n');

    return 0;
}