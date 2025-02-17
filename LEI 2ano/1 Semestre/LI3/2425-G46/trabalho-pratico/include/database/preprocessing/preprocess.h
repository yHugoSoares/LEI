/**
 * @file preprocess.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for preprocessing a Database entity.
 */

#ifndef _PREPROCESS_H_
#define _PREPROCESS_H_

// Project headers
#include "database.h"

/**
 * @brief Preprocesses the given Database by processing histories, musics, and users.
 *
 * This function processes the given Database by sequentially calling functions to 
 * preprocess the histories, musics, and users. It also measures and prints 
 * the execution time for each step.
 *
 * @param database The Database entity that will be preprocessed.
 */
void preprocess(Database database);

#endif // _PREPROCESS_H_
