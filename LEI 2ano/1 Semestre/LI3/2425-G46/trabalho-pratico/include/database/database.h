/**
 * @file database.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing the database and its repositories.
 */

#ifndef _DATABASE_H_
#define _DATABASE_H_

// Project headers for the various repositories
#include "string_pool.h"         
#include "repository_artist.h"   
#include "repository_music.h"     
#include "repository_user.h"      
#include "repository_album.h"     
#include "repository_history.h"   
#include "repository_data.h"      

/**
 * @brief Opaque structure representing the entire database.
 *
 * This structure represents the entire database containing all the repositories/tables.
 */
typedef struct database *Database;

/**
 * @brief Loads a database from the given folder path.
 *
 * Loads a database from a specified folder. This folder contains all the necessary data files
 * to load the database and its associated repositories.
 *
 * @param dataset_folder_path Path to the folder containing the dataset files.
 * @return A pointer to the loaded database.
 */
Database load_database(const char *dataset_folder_path);

/**
 * @brief Frees memory allocated for a database.
 *
 * Frees all resources and memory associated with the database, including all repositories and internal data structures.
 *
 * @param database The database to be freed.
 */
void free_database(Database database);

/**
 * @brief Gets the string pool associated with the database.
 *
 * Retrieves the string pool associated with the database. The string pool is used to store strings efficiently
 * to avoid duplication in memory.
 *
 * @param database The database.
 * @return A pointer to the StringPool associated with the database.
 */
StringPool get_string_pool(Database database);

/**
 * @brief Gets the artist repository associated with the database.
 *
 * Retrieves the repository that manages artists within the database. This repository contains functions
 * to access and modify information related to artists.
 *
 * @param database The database.
 * @return A pointer to the artist repository.
 */
ArtistRepository get_artist_repository(Database database);

/**
 * @brief Gets the music repository associated with the database.
 *
 * Retrieves the repository that manages music within the database. This repository allows access and
 * modification of music-related data.
 *
 * @param database The database.
 * @return A pointer to the music repository.
 */
MusicRepository get_music_repository(Database database);

/**
 * @brief Gets the user repository associated with the database.
 *
 * Retrieves the repository that manages users within the database. This repository allows access and
 * modification of user-related data.
 *
 * @param database The database.
 * @return A pointer to the user repository.
 */
UserRepository get_user_repository(Database database);

/**
 * @brief Gets the album repository associated with the database.
 *
 * Retrieves the repository that manages albums within the database. This repository contains functions
 * to access and modify information related to albums.
 *
 * @param database The database.
 * @return A pointer to the album repository.
 */
AlbumRepository get_album_repository(Database database);

/**
 * @brief Gets the history repository associated with the database.
 *
 * Retrieves the repository that manages playback histories within the database. It allows access and
 * modification of history data related to user music streams.
 *
 * @param database The database.
 * @return A pointer to the history repository.
 */
HistoryRepository get_history_repository(Database database);

/**
 * @brief Gets the data repository associated with the database.
 *
 * Retrieves the repository that handles additional data related to the database, such as statistics, streams,
 * and other data.
 *
 * @param database The database.
 * @return A pointer to the data repository.
 */
DataRepository get_data_repository(Database database);

#endif // _DATABASE_H_
