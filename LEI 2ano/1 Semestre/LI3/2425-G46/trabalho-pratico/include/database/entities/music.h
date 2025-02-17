/**
 * @file music.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing Music entities.
 */

#ifndef MUSIC_H
#define MUSIC_H

// Project headers
#include "string_pool.h"

/**
 * @brief Opaque structure representing a Music entity.
 */
typedef struct music *Music;

/**
 * @brief Creates a Music entity from the given fields.
 *
 * Initializes a Music structure using the provided string pool and fields array.
 *
 * @param string_pool A pool to store strings for memory optimization.
 * @param fields Array of strings containing the music data.
 * @return A pointer to the created Music.
 */
Music create_music(StringPool string_pool, char **fields);

/**
 * @brief Frees memory allocated for a Music entity.
 *
 * Releases all resources associated with the Music.
 *
 * @param music The Music to be freed.
 */
void free_music(Music music);

/**
 * @brief Gets the ID of the music.
 *
 * @param music The Music entity.
 * @return The music's ID.
 */
const char *get_music_id(Music music);

/**
 * @brief Gets the album ID associated with the music.
 *
 * @param music The Music entity.
 * @return The album ID associated with the music.
 */
const char *get_music_album_id(Music music);

/**
 * @brief Gets the duration of the music.
 *
 * @param music The Music entity.
 * @return The music's duration.
 */
const char *get_music_duration(Music music);

/**
 * @brief Gets the genre of the music.
 *
 * @param music The Music entity.
 * @return The music's genre.
 */
const char *get_music_genre(Music music);

/**
 * @brief Gets the artist IDs associated with the music.
 *
 * @param music The Music entity.
 * @return An array of artist IDs associated with the music.
 */
const char **get_music_artist_ids(Music music);

#endif // MUSIC_H
