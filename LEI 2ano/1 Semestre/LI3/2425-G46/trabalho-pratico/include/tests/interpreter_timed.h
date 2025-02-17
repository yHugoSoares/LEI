/**
 * @file interpreter_timed.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for timed query interpreter functions.
 * 
 * This file contains function prototypes for interpreting and executing
 * database queries with time measurement. It includes functions for
 * reading queries, executing them, and storing the results while tracking
 * query execution times.
 */

#ifndef _INTERPRETER_TIMED_H_ 
#define _INTERPRETER_TIMED_H_

// Standard libraries
#include <stdio.h>

// Project headers
#include "interpreter_timed.h"
#include "database.h"      
#include "utils.h"      
#include "query_metrics.h"  
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"

/**
 * @brief Executes queries from a file, measures execution time, and writes output.
 *
 * This function reads queries from a file, executes each query using
 * the appropriate query handler, measures the
 * execution time for each query, updates the query metrics, and writes
 * the results to an output file.
 *
 * @param database The database object containing the data to query.
 * @param queries_file_path Path to the file containing the queries.
 * @param output_file_path Path to the file where results will be written.
 * @param query_metrics_array Array holding the metrics for each query type.
 */
void timed_interpreter(Database database, char *queries_file_path, char *output_file_path, QueryMetrics *query_metrics_array);

/**
 * @brief Processes queries from a file with time measurement and stores the results.
 * 
 * This function serves as a wrapper to initiate the timed interpreter
 * for executing queries and measuring execution times. It writes the 
 * results of the queries to output files with the corresponding metrics.
 * 
 * @param queries_file_path Path to the file containing the queries.
 * @param database The database object to execute the queries on.
 * @param query_metrics_array Array holding the metrics for each query type.
 */
void process_queries_timed(char *queries_file_path, Database data, QueryMetrics *query_metrics_array);

#endif  // _INTERPRETER_TIMED_H_
