// Standard library headers
#include <stdio.h>        
#include <stdlib.h>       
#include <string.h>      
#include <time.h>         
#include <sys/resource.h> 

// Project headers
#include "query_metrics.h"
#include "interpreter_timed.h"
#include "database.h"        
#include "utils.h"                 
#include "query_metrics.h"         


void check_for_discrepancies(QueryMetrics *query_metrics_array, int query_type, int query_number,
                             FILE *expected_output_file, FILE *actual_output_file) {


    char *expected_output_line = NULL;
    char *actual_output_line = NULL;
    size_t len_expected = 0;
    size_t len_actual = 0;
    int line_number = 0;

    while (1) {
        line_number++;

        int result_expected = getline(&expected_output_line, &len_expected, expected_output_file);
        int result_actual = getline(&actual_output_line, &len_actual, actual_output_file);

        if (result_expected == -1 && result_actual == -1) {
            increase_passed_query_count_array(query_metrics_array, query_type);
            break;
        }

        if (expected_output_line == NULL || actual_output_line == NULL) {
            add_query_descrepancy_list_array(query_metrics_array, query_type, query_number, line_number);
            break;
        }
        
        if (strcmp(expected_output_line, actual_output_line)) {
            add_query_descrepancy_list_array(query_metrics_array, query_type, query_number, line_number);
            break;
        }
    }

    free(expected_output_line);
    free(actual_output_line);
}

void compare_output_files(char *queries_file_path, char *expected_output_folder_path,
                          QueryMetrics *query_metrics_array, int number_of_query_types) {


    FILE *queries_file = fopen(queries_file_path, "r"); 
    CHECK_FILE_OPEN(queries_file, queries_file_path);  

    char *line = NULL;
    size_t len = 0;
    int query_number = 0;

    while (getline(&line, &len, queries_file) != -1) {
        query_number++;

        int query_type = atoi(&line[0]); 


        char *expected_output_file_path = g_strdup_printf("%s/command%d_output.txt", expected_output_folder_path, query_number);

        char *actual_output_file_path = g_strdup_printf("resultados/command%d_output.txt", query_number);

        FILE *expected_output_file = fopen(expected_output_file_path, "r");
        FILE *actual_output_file = fopen(actual_output_file_path, "r");


        if (expected_output_file == NULL || actual_output_file == NULL) {
            add_query_descrepancy_list_array(query_metrics_array, query_type, query_number, 0);
        } else {
            check_for_discrepancies(query_metrics_array, query_type, query_number, expected_output_file, actual_output_file);
        }

        if (expected_output_file != NULL)
            fclose(expected_output_file);
        if (actual_output_file != NULL)
            fclose(actual_output_file);
    }

    reorder_query_descrepancy_list_array(query_metrics_array, number_of_query_types);

    fclose(queries_file); 

    free(line); 
}

void measure_program_performance(char *dataset_folder_path, char *queries_file_path,
                                 QueryMetrics *query_metrics_array, double *total_execution_time, double *memory_usage_mb) {


    clock_t start_time_total = clock(); 
    Database data = load_database(dataset_folder_path); 
    process_queries_timed(queries_file_path, data, query_metrics_array); 
    free_database(data); 
    clock_t end_time_total = clock(); 


    *total_execution_time = (double)(end_time_total - start_time_total) / CLOCKS_PER_SEC;

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    *memory_usage_mb = (double)usage.ru_maxrss / 1024.0;
}

void output_test_results(QueryMetrics *query_metrics_array, int number_of_query_types,
                         double total_execution_time, double memory_usage_mb) {
    
    for (int i = 0; i < number_of_query_types; i++) {

        int query_count = get_query_count_array(query_metrics_array, i+1);
        int passed_query_count = get_passed_query_count_array(query_metrics_array, i+1);

        printf("Q%d: %d of %d passed!\n", i+1, passed_query_count, query_count);

        if (query_count > 0)
            print_query_descrepancy_list_array(query_metrics_array, i+1);
    }

    double total_queries_execution_time = 0;

    printf("Average execution time:\n");
    for (int i = 0; i < number_of_query_types; i++) {

        int query_count = get_query_count_array(query_metrics_array, i+1);
        double query_total_execution_time = get_query_total_execution_time_array(query_metrics_array, i+1);

        total_queries_execution_time += query_total_execution_time;

        double query_average_execution_time = 0.0;
        if (query_count > 0)
            query_average_execution_time = query_total_execution_time / query_count;

        printf("    Q%d: %.3f ms\n", i+1, query_average_execution_time);
    }

    double loading_data_time = total_execution_time - total_queries_execution_time/1000.0;

    printf("Loading and preprocessing time: %.2f seconds\n", loading_data_time);

    printf("Total execution time: %.2f seconds\n", total_execution_time);
    printf("Memory usage: %.2f MB\n", memory_usage_mb);
}

int main(int argc, char **argv) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <dataset_folder> <queries_file> <expected_output_folder>\n", argv[0]);
        return 1; 
    }

    char *dataset_folder_path = argv[1];
    char *queries_file_path = argv[2];
    char *expected_output_folder_path = argv[3];

    int number_of_query_types = 6; 
    QueryMetrics query_metrics_array[number_of_query_types]; 
    init_query_metrics_array(query_metrics_array, number_of_query_types); 
    double total_execution_time;
    double memory_usage_mb;

    measure_program_performance(dataset_folder_path, queries_file_path, query_metrics_array, &total_execution_time, &memory_usage_mb);

    compare_output_files(queries_file_path, expected_output_folder_path, query_metrics_array, number_of_query_types);

    output_test_results(query_metrics_array, number_of_query_types, total_execution_time, memory_usage_mb);

    free_query_metrics_array(query_metrics_array, number_of_query_types);

    return 0; 
}
