/**
 * @file histories_preprocess.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for preprocessing history data.
 */

#ifndef _HISTORIES_PREPROCESS_H_  
#define _HISTORIES_PREPROCESS_H_

// Project headers
#include "database.h"

/**
 * @brief Preprocesses history data, calculating top artists and updating user genre preferences.
 *
 * This function processes history data, updates genre preferences, and calculates the top 10 artists.
 *
 * @param database The database instance that contains the necessary data for processing.
 */
void preprocess_histories(Database database);  

#endif // _HISTORIES_PREPROCESS_H_

