/**
 * @file musics_preprocess.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for preprocessing music data.
 */

#ifndef _MUSICS_PREPROCESS_H_
#define _MUSICS_PREPROCESS_H_

// Project headers
#include "database.h"

/**
 * @brief Preprocesses music data, calculating artists discography size.
 *
 * This function processes music data and calculate the discography size of each artist.
 *
 * @param database The database instance that contains the necessary data for processing.
 */
void preprocess_musics(Database database);


#endif  // _MUSICS_PREPROCESS_H_
