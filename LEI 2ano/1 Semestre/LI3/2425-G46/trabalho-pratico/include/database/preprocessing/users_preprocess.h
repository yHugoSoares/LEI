/**
 * @file users_preprocess.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for preprocessing user data.
 */

#ifndef __USERS_PREPROCESS_H_
#define __USERS_PREPROCESS_H_

// Project headers
#include "database.h"

/**
 * @brief Preprocesses user data, calculating users genres popularity.
 *
 * This function processes user data and calculate the genres popularity.
 *
 * @param database The database instance that contains the necessary data for processing.
 */
void preprocess_users(Database database);

#endif  // __USERS_PREPROCESS_H_
