/**
 * @file query_metrics.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for query metrics functions, which manage and track the execution of queries and their discrepancies.
 * 
 * This file defines structures and function prototypes related to managing query metrics, including tracking the number of queries,
 * the total execution time, and discrepancies that occur during query processing. The linked list of discrepancies provides information 
 * about where mismatches or errors occurred in the query results. These metrics are essential for analyzing the performance and correctness 
 * of the queries executed.
 */

#ifndef _QUERY_METRICS_H_
#define _QUERY_METRICS_H_

// Standard library headers
#include <stdio.h>
#include <stdlib.h>

// Type definition for linked list of discrepancies
typedef struct descrepancy_linked_list *LDescrepancy;

// Type definition for query metrics structure
typedef struct query_metrics *QueryMetrics;

/**
 * @brief Initializes an array of query metrics structures.
 * 
 * This function initializes an array of `QueryMetrics` structures, where each element corresponds to a different query type. 
 * It sets up the query count, passed query count, total execution time, and the linked list of discrepancies.
 * 
 * @param query_metrics_array The array of `QueryMetrics` to be initialized.
 * @param number_of_query_types The total number of query types for which metrics will be initialized.
 */
void init_query_metrics_array(QueryMetrics *query_metrics_array, int number_of_query_types);

/**
 * @brief Frees the memory allocated for an array of query metrics structures.
 * 
 * This function releases the memory used by the array of `QueryMetrics` structures and their associated linked lists of discrepancies.
 * 
 * @param query_metrics_array The array of `QueryMetrics` to be freed.
 * @param number_of_query_types The number of query types for which metrics need to be freed.
 */
void free_query_metrics_array(QueryMetrics *query_metrics_array, int number_of_query_types);

/**
 * @brief Retrieves the query metrics for a specific query type.
 * 
 * This function returns the `QueryMetrics` structure for a specific query type.
 * 
 * @param query_metrics_array The array of `QueryMetrics` to retrieve the metrics from.
 * @param query_type The query type for which the metrics are needed.
 * @return The `QueryMetrics` structure for the specified query type.
 */
QueryMetrics get_query_from_array(QueryMetrics *query_metrics_array, int query_type);

/**
 * @brief Retrieves the total number of queries processed for a specific query type.
 * 
 * @param query_metrics_array The array of `QueryMetrics`.
 * @param query_type The query type for which the count is requested.
 * @return The total number of queries processed for the specified query type.
 */
int get_query_count_array(QueryMetrics *query_metrics_array, int query_type);

/**
 * @brief Retrieves the number of passed queries for a specific query type.
 * 
 * @param query_metrics_array The array of `QueryMetrics`.
 * @param query_type The query type for which the count is requested.
 * @return The number of queries that passed for the specified query type.
 */
int get_passed_query_count_array(QueryMetrics *query_metrics_array, int query_type);

/**
 * @brief Retrieves the total execution time for queries of a specific type.
 * 
 * @param query_metrics_array The array of `QueryMetrics`.
 * @param query_type The query type for which the execution time is requested.
 * @return The total execution time for the specified query type.
 */
double get_query_total_execution_time_array(QueryMetrics *query_metrics_array, int query_type);

/**
 * @brief Retrieves the list of discrepancies for a specific query type.
 * 
 * @param query_metrics_array The array of `QueryMetrics`.
 * @param query_type The query type for which the discrepancies are requested.
 * @return The linked list of discrepancies for the specified query type.
 */
LDescrepancy get_query_descrepancy_list_array(QueryMetrics *query_metrics_array, int query_type);

/**
 * @brief Increments the count of passed queries for a specific query type.
 * 
 * @param query_metrics_array The array of `QueryMetrics`.
 * @param query_type The query type for which the passed query count should be incremented.
 */
void increase_passed_query_count_array(QueryMetrics *query_metrics_array, int query_type);

/**
 * @brief Increments the total execution time and the query count for a specific query type.
 * 
 * @param query_metrics_array The array of `QueryMetrics`.
 * @param query_type The query type for which the execution time and count should be updated.
 * @param query_execution_time The execution time of the query to be added.
 */
void increase_query_time_and_count_array(QueryMetrics *query_metrics_array, int query_type, double query_execution_time);

/**
 * @brief Adds a discrepancy to the list of discrepancies for a specific query type.
 * 
 * @param query_metrics_array The array of `QueryMetrics`.
 * @param query_type The query type for which the discrepancy should be added.
 * @param query_number The number of the query with the discrepancy.
 * @param file_line The line number where the discrepancy was found.
 */
void add_query_descrepancy_list_array(QueryMetrics *query_metrics_array, int query_type, int query_number, int file_line);

/**
 * @brief Reverses the order of discrepancies in the linked list for all query types.
 * 
 * @param query_metrics_array The array of `QueryMetrics`.
 * @param number_of_query_types The total number of query types whose discrepancy lists should be reversed.
 */
void reorder_query_descrepancy_list_array(QueryMetrics *query_metrics_array, int number_of_query_types);

/**
 * @brief Prints the list of discrepancies for a specific query type.
 * 
 * @param query_metrics_array The array of `QueryMetrics`.
 * @param query_type The query type for which the discrepancies should be printed.
 */
void print_query_descrepancy_list_array(QueryMetrics *query_metrics_array, int query_type);

#endif  // _QUERY_METRICS_H_
