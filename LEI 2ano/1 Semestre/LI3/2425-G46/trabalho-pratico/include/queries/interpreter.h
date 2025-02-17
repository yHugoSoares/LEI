/**
 * @file interpreter.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for interpreting and executing queries on a database.
 */

#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

// Project headers for handling database operations and output management
#include "database.h"
#include "output.h"

/**
 * @brief Executes a series of queries in batch mode by reading from a file.
 *
 * This function reads a file containing queries, executes them one by one, and stores the results 
 * in separate output files. It processes each query line by line, identifies the query type, 
 * and calls the appropriate function to handle the query. The results for each query are written to 
 * a file named `command{n}_output.txt`.
 *
 * @param queries_file_path The path to the file containing a list of queries to execute.
 * @param database The Database instance to use for executing the queries.
 */
void batch_interpreter(char *queries_file_path, Database database);

void interactive_interpreter(int query_type, int spacer_type, char *input, Database database, Output *output);

#endif // _INTERPRETER_H_
