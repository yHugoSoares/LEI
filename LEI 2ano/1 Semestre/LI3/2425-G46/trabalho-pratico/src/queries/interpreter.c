#include <stdio.h>
#include "interpreter.h"
#include "database.h"
#include "utils.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"

void batch_interpreter(char *queries_file_path, Database database){

    FILE *queries_file = fopen(queries_file_path, "r"); 
    CHECK_FILE_OPEN(queries_file, queries_file_path);  

    char *line = NULL;
    size_t len = 0;
    int count = 1;

    while (getline(&line, &len, queries_file) != -1) {

        g_strchomp(line);

        int query_type = line[0] - '0';

        char *spacer;
        char *args;

        if (line[1] == 'S') {
            spacer = "=";
            args = line + 3;
        } else {
            spacer = ";";
            args = line + 2;
        }

        Output output = init_output();

        switch (query_type) {
            case 1:
                query1(database, args, output, spacer);
                break;
            case 2:
                query2(database, args, output, spacer);
                break;
            case 3:
                query3(database, args, output, spacer);
                break;
            case 4:
                query4(database, args, output, spacer);
                break;
            case 5:
                query5(database, args, output, spacer);
                break;
            case 6:
                query6(database, args, output, spacer);
                break;
            default:
                break;
        }

        char *output_file_path = g_strdup_printf("resultados/command%d_output.txt", count);
        write_output_to_file(output, output_file_path);
        free_output(output);
        g_free(output_file_path);

        count++;
    }

    free(line);
    fclose(queries_file);
}


void interactive_interpreter(int query, int spacer, char *input, Database database, Output *output) {

    char *spacers[] = SPACERS;

    switch (query) {
        case 1:
            query1(database, input, *output, spacers[spacer]);
            break;
        case 2:
            query2(database, input, *output, spacers[spacer]);
            break;
        case 3:
            query3(database, input, *output, spacers[spacer]);
            break;
        case 4:
            query4(database, input, *output, spacers[spacer]);
            break;
        case 5:
            query5(database, input, *output, spacers[spacer]);
            break;
        case 6:
            query6(database, input, *output, spacers[spacer]);
            break;
        default:
            break;
    }
}
