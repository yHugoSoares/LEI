/**
 * @file repository_music.h
 * @author Francisco Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing Music repository operations.
 */

#ifndef _REPOSITORY_MUSIC_H_
#define _REPOSITORY_MUSIC_H_

// Project headers
#include "music.h"          
#include "defs.h"           
#include "string_pool.h"    
#include "data_container.h" 

/**
 * @brief Opaque structure representing a MusicRepository.
 *
 * This structure represents a repository that manages information related to songs
 * and allows storing and accessing music-related data in the system.
 */
typedef struct music_repository *MusicRepository;

/**
 * @brief Initializes a MusicRepository instance.
 *
 * Creates and initializes an instance of MusicRepository, which is used to store and manage
 * music data related to songs, artists, and albums.
 *
 * @return A pointer to the initialized MusicRepository instance.
 */
MusicRepository init_music_repository();

/**
 * @brief Frees the memory allocated for a MusicRepository instance.
 *
 * Frees the memory and resources associated with a MusicRepository, cleaning up the stored music data.
 *
 * @param music_data The MusicRepository instance to free.
 */
void free_music_repository(MusicRepository music_data);

/**
 * @brief Loads a music entity into the repository.
 *
 * Loads a Music entity into the music repository, adding it to the system's storage.
 *
 * @param string_pool A string pool to optimize memory usage.
 * @param music_repository The music repository where the entity will be stored.
 * @param music The Music entity to load into the repository.
 */
void load_music(StringPool string_pool, MusicRepository music_repository, Music music);

/**
 * @brief Checks if a music exists in the repository.
 *
 * Checks if a song exists in the repository using the song's unique ID.
 *
 * @param music_data The music repository.
 * @param music_id The ID of the song to check.
 * @return 1 if the song exists, 0 if the song does not exist.
 */
int check_music_exists(MusicRepository music_data, const char *music_id);

/**
 * @brief Gets the genre of a music by its ID.
 *
 * Retrieves the genre of a song based on its ID.
 *
 * @param music_repository The music repository.
 * @param music_id The ID of the song whose genre is to be retrieved.
 * @return The genre of the song.
 */
char *get_music_genre_by_id(MusicRepository music_repository, const char *music_id);

/**
 * @brief Gets the album ID of a music.
 *
 * Retrieves the album ID associated with a song.
 *
 * @param music_repository The music repository.
 * @param music_id The ID of the song whose album information is to be retrieved.
 * @return The album ID associated with the song.
 */
char *get_music_album_id_by_id(MusicRepository music_repository, const char *music_id);

/**
 * @brief Gets the duration of a music by its ID.
 *
 * Retrieves the duration of a song based on its ID.
 *
 * @param music_repository The music repository.
 * @param music_id The ID of the song whose duration is to be retrieved.
 * @return The duration of the song.
 */
char *get_music_duration_by_id(MusicRepository music_repository, const char *music_id);

/**
 * @brief Gets the artist IDs associated with a music.
 *
 * Retrieves a list of artist IDs associated with a song.
 *
 * @param music_repository The music repository.
 * @param music_id The ID of the song whose artist list is to be retrieved.
 * @return A list of artist IDs associated with the song.
 */
GList *get_music_artist_ids_by_id(MusicRepository music_repository, const char *music_id);

/**
 * @brief Gets a list of all genres in the music repository.
 *
 * Retrieves a list of all music genres available in the music repository.
 *
 * @param music_repository The music repository.
 * @return An array of strings containing the genres in the repository.
 */
char **get_genres(MusicRepository music_repository);

/**
 * @brief Gets the number of genres in the music repository.
 *
 * Retrieves the total number of music genres available in the music repository.
 *
 * @param music_repository The music repository.
 * @return The total number of music genres.
 */
int get_num_of_genres(MusicRepository music_repository);

/**
 * @brief Iterates over all artist music IDs in the repository.
 *
 * This function iterates over all music IDs related to artists in the repository.
 *
 * @param music_repository The music repository.
 * @param func The function to apply to each music ID associated with an artist.
 * @param container A data container that will be passed to the function for each iteration.
 */
void foreach_artist_music_ids(MusicRepository music_repository, IterDataFunc func, DataContainer container);

#endif // _REPOSITORY_MUSIC_H_
