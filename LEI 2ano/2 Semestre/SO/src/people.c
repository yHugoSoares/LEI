#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct person {
    char name[100];
    int age;
} Person;

int add_person(const char *filename, const char *name, int age) {
    
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    Person p;
    strcpy(p.name, name);
    p.name[sizeof(p.name) - 1] = '\0';
    p.age = age;

    write(fd, &p, sizeof(Person));

    close(fd);

    return 0;
}

void list_people(const char *filename, int n) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    Person p;
    for (int i = 0; i < n; i++) {
        if (read(fd, &p, sizeof(Person)) != sizeof(Person)) {
            break;
        }
        printf("Name: %s | Age: %d\n", p.name, p.age);
    }

    close(fd);
}

void update_person(const char *filename, const char *name, int new_age) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    Person p;
    ssize_t bytes;
    while ((bytes = read(fd, &p, sizeof(Person))) == sizeof(Person)) {
        if (strcmp(p.name, name) == 0) {
            p.age = new_age;
            lseek(fd, -sizeof(Person), SEEK_CUR);
            if (write(fd, &p, sizeof(Person)) != sizeof(Person)) {
                perror("write");
                close(fd);
                exit(1);
            }
            break;
        }
    }

    if (bytes == -1) {
        perror("read");
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s -i name age | -l N | -u name new_age\n", argv[0]);
        return 1;
    }
    clock_t start = clock();

    const char *filename = "people.dat";

    if (strcmp(argv[1], "-i") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s -i name age\n", argv[0]);
            return 1;
        }
        add_person(filename, argv[2], atoi(argv[3]));
    } else if (strcmp(argv[1], "-l") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s -l N\n", argv[0]);
            return 1;
        }
        list_people(filename, atoi(argv[2]));
    } else if (strcmp(argv[1], "-u") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s -u name new_age\n", argv[0]);
            return 1;
        }
        update_person(filename, argv[2], atoi(argv[3]));
    } else {
        fprintf(stderr, "Invalid option\n");
        return 1;
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f\n", time_spent);

    return 0;
}