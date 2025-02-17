#include <stdio.h>

#include <glib.h>

#include "database.h"
#include "string_pool.h"
#include "defs.h"
#include "parser.h"

void load(const char *dataset_folder_path, const char *data_file_name, const char *errors_file_path,
          Database database, StringPool string_pool, Repository repository,
          ValidateFunc validate_func, CreateFunc create_func, LoadFunc load_func) {

    char *data_file_path = g_strconcat(dataset_folder_path, "/", data_file_name, NULL);
    FILE *data_file = fopen(data_file_path, "r");
    CHECK_FILE_OPEN(data_file, data_file_path);
    
    g_free(data_file_path);

    FILE *errors_file = fopen(errors_file_path, "w");
    CHECK_FILE_OPEN(errors_file, errors_file_path);

    char *line = NULL;
    size_t len = 0;
    int header_flag = 1;
    while (getline(&line, &len, data_file) != -1) {

        if (header_flag) {
            header_flag = 0;
            fputs(line, errors_file);
            continue;
        }

        char **fields = parse_line(line);

        if (validate_func(fields, database) == 0) {
            fputs(line, errors_file);
            free_fields(fields);
            continue;
        }

        void *entity = create_func(string_pool, fields);

        free_fields(fields);

        load_func(string_pool, repository, entity);
    }
    
    free(line);
    fclose(data_file);
    fclose(errors_file);

}

