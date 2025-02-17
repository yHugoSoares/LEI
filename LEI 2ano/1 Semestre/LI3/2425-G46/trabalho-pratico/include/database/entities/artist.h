/**
 * @file artist.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing Artist entities.
 */

#ifndef _ARTIST_H_
#define _ARTIST_H_

// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "string_pool.h"

/**
 * @brief Opaque structure representing an Artist.
 */
typedef struct artist *Artist;

/**
 * @brief Creates an Artist entity from the given fields.
 *
 * Initializes an Artist structure using the provided string pool and fields array.
 *
 * @param string_pool A pool to store strings for memory optimization.
 * @param fields Array of strings containing the artist's data.
 * @return A pointer to the created Artist.
 */
Artist create_artist(StringPool string_pool, char **fields);

/**
 * @brief Frees memory allocated for an Artist entity.
 *
 * Releases all resources associated with the Artist.
 *
 * @param artist The Artist to be freed.
 */
void free_artist(Artist artist);

/**
 * @brief Gets the ID of the artist.
 *
 * @param artist The Artist entity.
 * @return The artist's ID.
 */
const char *get_artist_id(Artist artist);

/**
 * @brief Gets the name of the artist.
 *
 * @param artist The Artist entity.
 * @return The artist's name.
 */
const char *get_artist_name(Artist artist);

/**
 * @brief Gets the recipe per stream of the artist.
 *
 * @param artist The Artist entity.
 * @return The artist's recipe per stream.
 */
const char *get_artist_recipe_per_stream(Artist artist);

/**
 * @brief Gets the country of the artist.
 *
 * @param artist The Artist entity.
 * @return The artist's country.
 */
const char *get_artist_country(Artist artist);

/**
 * @brief Gets the type of the artist.
 *
 * @param artist The Artist entity.
 * @return The artist's type.
 */
const char *get_artist_type(Artist artist);

/**
 * @brief Gets the constituent IDs of the artist.
 *
 * @param artist The Artist entity.
 * @return A constant array of strings representing the artist's constituent IDs.
 */
const char **get_artist_constituent_ids(Artist artist);

#endif // _ARTIST_H_
