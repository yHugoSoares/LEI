/**
 * @file query2.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for query 2, which retrieves the top N largest artists by discography size for a given country.
 */

#ifndef _QUERY2_H  // Check if _QUERY2_H is not defined
#define _QUERY2_H  // Define _QUERY2_H to avoid double inclusion

// Project headers
#include "database.h" 
#include "output.h" 

void query2(Database database, char *args, Output output, char *spacer);

#endif  // _QUERY2_H
