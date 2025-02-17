#include <stdio.h>
#include "defs.h"
#include "database.h"
#include "utils.h"
#include "query_metrics.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"

void timed_interpreter(Database database, char *queries_file_path, char *output_file_path, QueryMetrics *query_metrics_array){

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
        clock_t start_time, end_time;
        double query_execution_time;

        Output output = init_output();

        switch (query_type) {
            case 1:
                start_time = clock();
                query1(database, args, output, spacer);
                end_time = clock();
                query_execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;
                increase_query_time_and_count_array(query_metrics_array, query_type, query_execution_time);
                break;
            case 2:
                start_time = clock();
                query2(database, args, output, spacer);
                end_time = clock();
                query_execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;
                increase_query_time_and_count_array(query_metrics_array, query_type, query_execution_time);
                break;
            case 3:
                start_time = clock();
                query3(database, args, output, spacer);
                end_time = clock();
                query_execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;
                increase_query_time_and_count_array(query_metrics_array, query_type, query_execution_time);
                break;
            case 4:
                start_time = clock();
                query4(database, args, output, spacer);
                end_time = clock();
                query_execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;
                increase_query_time_and_count_array(query_metrics_array, query_type, query_execution_time);
                break;
            case 5:
                start_time = clock();
                query5(database, args, output, spacer);
                end_time = clock();
                query_execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;
                increase_query_time_and_count_array(query_metrics_array, query_type, query_execution_time);
                break;
            case 6:
                start_time = clock();
                query6(database, args, output, spacer);
                end_time = clock();
                query_execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;
                increase_query_time_and_count_array(query_metrics_array, query_type, query_execution_time);
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

void process_queries_timed(char *queries_file_path, Database database, QueryMetrics *query_metrics_array) {

    int count = 1;

    char *output = g_strdup_printf("resultados/command%d_output.txt", count);

    timed_interpreter(database, queries_file_path, output, query_metrics_array);

    g_free(output);

    count++;

}
