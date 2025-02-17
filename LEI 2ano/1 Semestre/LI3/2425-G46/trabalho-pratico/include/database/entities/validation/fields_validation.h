/**
 * @file fields_validation.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for field validation functions in the project.
 */

#ifndef _FIELDS_VALIDATION_H_
#define _FIELDS_VALIDATION_H_

// Project headers
#include "database.h"  

/**
 * @brief Validates the fields for an artist entry.
 *
 * This function checks the validity of the fields provided for creating or updating an artist in the database.
 * It ensures that all required fields are present and valid according to the database schema.
 *
 * @param fields An array of strings representing the fields for the artist entry.
 * @param database The database object used to validate the artist fields.
 * @return 1 if the artist fields are valid, 0 otherwise.
 */
int validate_artist_fields(const char **fields, Database database);

/**
 * @brief Validates the fields for a music entry.
 *
 * This function checks the validity of the fields provided for creating or updating a music track in the database.
 * It ensures that all required fields are present and valid.
 *
 * @param fields An array of strings representing the fields for the music entry.
 * @param database The database object used to validate the music fields.
 * @return 1 if the music fields are valid, 0 otherwise.
 */
int validate_music_fields(const char **fields, Database database);

/**
 * @brief Validates the fields for a user entry.
 *
 * This function checks the validity of the fields provided for creating or updating a user in the database.
 * It ensures that all required fields are present and valid.
 *
 * @param fields An array of strings representing the fields for the user entry.
 * @param database The database object used to validate the user fields.
 * @return 1 if the user fields are valid, 0 otherwise.
 */
int validate_user_fields(const char **fields, Database database);

/**
 * @brief Validates the fields for a history entry.
 *
 * This function checks the validity of the fields provided for creating or updating a history record in the database.
 * It ensures that all required fields are present and valid.
 *
 * @param fields An array of strings representing the fields for the history entry.
 * @param database The database object used to validate the history fields.
 * @return 1 if the history fields are valid, 0 otherwise.
 */
int validate_history_fields(const char **fields, Database database);

/**
 * @brief Validates the fields for an album entry.
 *
 * This function checks the validity of the fields provided for creating or updating an album in the database.
 * It ensures that all required fields are present and valid.
 *
 * @param fields An array of strings representing the fields for the album entry.
 * @param database The database object used to validate the album fields.
 * @return 1 if the album fields are valid, 0 otherwise.
 */
int validate_album_fields(const char **fields, Database database);

#endif
