#ifndef _DEFS_H_
#define _DEFS_H_

// Standard library headers
#include <stdio.h>
#include <stdlib.h>

#include <glib.h>

// Definition of the value of an empty field
#define Empty NULL

// Definition of a generic function for iterating over key-value pairs
typedef void (*IterDataFunc) (void *data_container, const char *key, const void *value);

// Definition of a generic repository type
typedef void* Repository;

// Definition of a generic validation function
typedef int (*ValidateFunc)(char **fields, void *database);

// Definition of a generic creation function
typedef void* (*CreateFunc)(void *string_pool, char **fields);

// Definition of a generic loading function
typedef void (*LoadFunc)(void *string_pool, void *repository, void *entity);

// Definition of a maximum buffer size
#define BUFFER_SIZE 64

// Definition of the default dataset folder path
#define DEFAULT_DATASET_FOLDER_PATH "dataset"

// Files
#define FILES_NUM 5
#define FILES { "artists.csv",\
                "albums.csv",\
                "users.csv",\
                "musics.csv",\
                "history.csv", NULL };

// Queries
#define QUERIES_NUM 6
#define QUERIES { "Query 1", "Query 2", "Query 3", "Query 4", "Query 5", "Query 6" , NULL };

// Spacers
#define SPACERS_NUM 2
#define SPACERS_FULL { "Spacer (;)", "Spacer (=)", NULL };
#define SPACERS { ";", "=", NULL };

// Definition of the current date
#define TD_YEAR 2024
#define TD_MONTH 9
#define TD_DAY 9
#define TD_DATE "2024/09/09"

// Macro to check for failed memory allocation
#define CHECK_ALLOC(ptr) if ((ptr) == NULL) { \
    fprintf(stderr, "Memory allocation for '%s' failed at %s:%d\n", #ptr, __FILE__, __LINE__); \
    exit(EXIT_FAILURE); \
}

// Macro to check for failed file opening
#define CHECK_FILE_OPEN(fp, filename) if ((fp) == NULL) { \
    fprintf(stderr, "Failed to open file '%s' at %s:%d\n", filename, __FILE__, __LINE__); \
    exit(EXIT_FAILURE); \
}

#endif
