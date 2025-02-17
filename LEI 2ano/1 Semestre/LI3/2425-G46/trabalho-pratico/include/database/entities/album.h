/**
 * @file album.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing Album entities.
 */

#ifndef _ALBUM_H_
#define _ALBUM_H_

// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "string_pool.h"

/**
 * @brief Opaque structure representing an Album.
 */
typedef struct album *Album;

/**
 * @brief Creates an Album entity from the given fields.
 *
 * Initializes an Album structure using the provided string pool and fields array.
 *
 * @param string_pool A pool to store strings for memory optimization.
 * @param fields Array of strings containing the album's data.
 * @return A pointer to the created Album.
 */
Album create_album(StringPool string_pool, char **fields);

/**
 * @brief Frees memory allocated for an Album entity.
 *
 * Releases all resources associated with the Album.
 *
 * @param album The Album to be freed.
 */
void free_album(Album album);

/**
 * @brief Gets the ID of the album.
 *
 * @param album The Album entity.
 * @return The album's ID.
 */
const char *get_album_id(Album album);

/**
 * @brief Gets the artist IDs associated with the album.
 *
 * @param album The Album entity.
 * @return A constant array of strings representing the album's artist IDs.
 */
const char **get_album_artist_ids(Album album);

#endif // _ALBUM_H_