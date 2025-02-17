/**
 * @file query4.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for query 4, which retrieves the top 10 artists by occurrences within a specified date range or overall.
 */

#ifndef QUERY4_H  
#define QUERY4_H  

// Project headers
#include "database.h"
#include "output.h"  

void query4(Database database, char *args, Output output, char *spacer);

#endif  // _QUERY4_H
