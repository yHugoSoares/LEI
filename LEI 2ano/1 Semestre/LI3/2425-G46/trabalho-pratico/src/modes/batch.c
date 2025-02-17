// Standard library headers
#include <stdio.h>
#include <sys/resource.h> 

// Project headers
#include "database.h"
#include "interpreter.h"
#include "utils.h"

int main(int argc, char **argv) {

    if (argc != 3) {
        fprintf(stderr, "Usage: ./programa-principal <dataset_folder> <queries_file>\n");
        return 1;
    }

    char *dataset_folder_path = argv[1];
    char *queries_file_path = argv[2];

    Database database = load_database(dataset_folder_path);
    
    batch_interpreter(queries_file_path, database);

    free_database(database);

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    double memory_usage_mb = (double)usage.ru_maxrss / 1024.0;
    printf("Memory usage: %.2f MB\n", memory_usage_mb);

    return 0;
}
