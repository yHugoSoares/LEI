// Standard library headers
#include <stdio.h>
#include <stdlib.h>

// Project headers
#include "query_metrics.h"
#include "defs.h"
#include "utils.h"
#include "defs.h"

typedef struct descrepancy_linked_list {
    int query_number;                     
    int file_line;        
    struct descrepancy_linked_list *next; 
} *LDescrepancy;

typedef struct query_metrics {
    int query_count;       
    int passed_query_count;      
    double total_execution_time;  
    LDescrepancy descrepancy_linked_list; 
} *QueryMetrics;


LDescrepancy prepend_descrepancy(LDescrepancy head, int query_number, int file_line) {

    LDescrepancy new_descrepancy = malloc(sizeof(struct descrepancy_linked_list));
    CHECK_ALLOC(new_descrepancy);

    new_descrepancy->query_number = query_number;
    new_descrepancy->file_line = file_line;
    new_descrepancy->next = head;
    return new_descrepancy;
}

LDescrepancy append_descrepancy(LDescrepancy head, int query_number, int file_line) {

    LDescrepancy new_descrepancy = malloc(sizeof(struct descrepancy_linked_list));
    CHECK_ALLOC(new_descrepancy);

    new_descrepancy->query_number = query_number;
    new_descrepancy->file_line = file_line;
    new_descrepancy->next = NULL;

    if (head == NULL) {
        return new_descrepancy;
    }

    LDescrepancy current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_descrepancy;
    return head;
}

LDescrepancy reverse_descrepancy_list(LDescrepancy head) {

    LDescrepancy new_head = NULL;
    while (head != NULL) {
        LDescrepancy new_next = head->next;
        head->next = new_head;
        new_head = head;
        head = new_next;
    }
    return new_head;
}

void print_descrepancy_list(LDescrepancy head) {

    while (head != NULL) {
        printf("    Discrepancy in query %d: line %d of resultados/command%d_output.txt\n",
               head->query_number, head->file_line, head->query_number);
        head = head->next;
    }
}

void free_descrepancy_list(LDescrepancy head) {

    while (head != NULL) {
        LDescrepancy next = head->next;
        free(head);
        head = next;
    }
}


QueryMetrics init_query_metrics() {

    QueryMetrics query_metrics = malloc(sizeof(struct query_metrics));
    CHECK_ALLOC(query_metrics);

    query_metrics->query_count = 0;
    query_metrics->passed_query_count = 0;
    query_metrics->total_execution_time = 0.0;
    query_metrics->descrepancy_linked_list = NULL;

    return query_metrics;
}

void free_query_metrics(QueryMetrics query_metrics) {

    free_descrepancy_list(query_metrics->descrepancy_linked_list);
    free(query_metrics);
}


int get_query_count(QueryMetrics query_metrics) {

    return query_metrics->query_count;
}

int get_passed_query_count(QueryMetrics query_metrics) {

    return query_metrics->passed_query_count;
}

double get_total_execution_time(QueryMetrics query_metrics) {

    return query_metrics->total_execution_time;
}

LDescrepancy get_query_descrepancy_list(QueryMetrics query_metrics) {

    return query_metrics->descrepancy_linked_list;
}


void increase_query_count(QueryMetrics query_metrics) {

    query_metrics->query_count++;
}

void increase_passed_query_count(QueryMetrics query_metrics) {

    query_metrics->passed_query_count++;
}

void increase_total_execution_time(QueryMetrics query_metrics, double query_execution_time) {

    query_metrics->total_execution_time += query_execution_time;
}

void increase_time_and_count(QueryMetrics query_metrics, double query_execution_time) {

    query_metrics->query_count++;
    query_metrics->total_execution_time += query_execution_time;
}

void add_descrepancy(QueryMetrics query_metrics, int query_number, int file_line) {

    query_metrics->descrepancy_linked_list = prepend_descrepancy(query_metrics->descrepancy_linked_list, query_number, file_line);
}


void reorder_descrepancy_list(QueryMetrics query_metrics) {

    query_metrics->descrepancy_linked_list = reverse_descrepancy_list(query_metrics->descrepancy_linked_list);
}

void init_query_metrics_array(QueryMetrics *query_metrics_array, int number_of_query_types) {

    for (int i = 0; i < number_of_query_types; i++)
        query_metrics_array[i] = init_query_metrics();
}

void free_query_metrics_array(QueryMetrics *query_metrics_array, int number_of_query_types) {

    for (int i = 0; i < number_of_query_types; i++)
        free_query_metrics(query_metrics_array[i]);
}


QueryMetrics get_query_from_array(QueryMetrics *query_metrics_array, int query_type) {

    return query_metrics_array[query_type - 1];
}

int get_query_count_array(QueryMetrics *query_metrics_array, int query_type) {

    return query_metrics_array[query_type - 1]->query_count;
}

int get_passed_query_count_array(QueryMetrics *query_metrics_array, int query_type) {

    return query_metrics_array[query_type - 1]->passed_query_count;
}

double get_query_total_execution_time_array(QueryMetrics *query_metrics_array, int query_type) {

    return query_metrics_array[query_type - 1]->total_execution_time;
}

LDescrepancy get_query_descrepancy_list_array(QueryMetrics *query_metrics_array, int query_type) {

    return query_metrics_array[query_type - 1]->descrepancy_linked_list;
}


void increase_passed_query_count_array(QueryMetrics *query_metrics_array, int query_type) {

    increase_passed_query_count(query_metrics_array[query_type - 1]);
}

void increase_query_time_and_count_array(QueryMetrics *query_metrics_array, int query_type, double query_execution_time) {

    increase_time_and_count(query_metrics_array[query_type - 1], query_execution_time);
}

void add_query_descrepancy_list_array(QueryMetrics *query_metrics_array, int query_type, int query_number, int file_line) {

    add_descrepancy(query_metrics_array[query_type - 1], query_number, file_line);
}

void reorder_query_descrepancy_list_array(QueryMetrics *query_metrics_array, int number_of_query_types) {

    for (int i = 0; i < number_of_query_types; i++)
        reorder_descrepancy_list(query_metrics_array[i]);
}

void print_query_descrepancy_list_array(QueryMetrics *query_metrics_array, int query_type) {

    print_descrepancy_list(query_metrics_array[query_type - 1]->descrepancy_linked_list);
}
