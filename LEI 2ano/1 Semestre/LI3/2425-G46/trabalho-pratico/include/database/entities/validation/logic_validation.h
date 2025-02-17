/**
 * @file logic_validation.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for logical validation functions in the project.
 */

#ifndef _LOGIC_VALIDATION_H_
#define _LOGIC_VALIDATION_H_

// Third-party library headers
#include <glib.h>       

// Project headers
#include "repository_music.h"  
#include "repository_artist.h"  

/**
 * @brief Validates the constituents in a list for a given type.
 *
 * This function checks if the constituents list is valid.
 *
 * @param list A string representing the list of constituents to be validated.
 * @param type A string indicating the type of artist (e.g., "individual", "group").
 * @return 1 if the constituents are valid, 0 otherwise.
 */
int validate_constituents(const char* list, const char* type);

/**
 * @brief Validates the artists in a list against the provided artist repository.
 *
 * This function checks if all artists in the list exist in the provided artist repository.
 *
 * @param list A string representing the list of artist IDs.
 * @param artist_repository The artist repository to check the artists presence.
 * @return 1 if all artists exist, 0 otherwise.
 */
int validate_artists(const char *list, ArtistRepository artist_repository);

/**
 * @brief Validates the music in a list against the provided music repository.
 *
 * This function checks if all music in the list exist in the provided music repository.
 *
 * @param list A string representing the list of music IDs.
 * @param artist_repository The music repository to check the music presence.
 * @return 1 if all music exist, 0 otherwise.
 */
int validate_musics(const char *list, MusicRepository music_repository);

/**
 * @brief Validates if the provided album ID exists in the album repository.
 *
 * This function checks if the given album ID is valid by ensuring it exists in the provided album repository.
 *
 * @param album_id A string representing the album ID to be validated.
 * @param album_repository The album repository to check if the album exists.
 * @return 1 if the album ID exists, 0 otherwise.
 */
int validate_album(const char *album_id, AlbumRepository album_repository);

#endif
