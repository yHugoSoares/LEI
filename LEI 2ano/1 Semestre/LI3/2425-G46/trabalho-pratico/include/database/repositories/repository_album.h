/**
 * @file repository_album.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing Album repository operations.
 */

#ifndef _REPOSITORY_ALBUM_H_
#define _REPOSITORY_ALBUM_H_

// Project headers
#include "album.h"       
#include "string_pool.h" 

/**
 * @brief Opaque structure representing an AlbumRepository.
 *
 * This structure is used to represent the repository that holds the albums.
 * It is implemented as an opaque type to hide the internal details.
 */
typedef struct album_repository *AlbumRepository;

/**
 * @brief Initializes an AlbumRepository instance.
 *
 * This function creates and initializes an empty AlbumRepository.
 *
 * @return A pointer to the initialized AlbumRepository.
 */
AlbumRepository init_album_repository();

/**
 * @brief Frees memory allocated for an AlbumRepository instance.
 *
 * This function releases the memory and resources associated with an AlbumRepository.
 *
 * @param album_repository The AlbumRepository instance to be freed.
 */
void free_album_repository(AlbumRepository album_repository);

/**
 * @brief Loads an Album into the repository.
 *
 * This function loads an Album into the given AlbumRepository, associating it 
 * with the provided string pool for memory optimization.
 *
 * @param string_pool A pool of strings for efficient memory management.
 * @param album_repository The AlbumRepository where the album will be loaded.
 * @param album The Album entity to be loaded into the repository.
 */
void load_album(StringPool string_pool, AlbumRepository album_repository, Album album);

/**
 * @brief Checks if an album exists in the repository.
 *
 * This function checks if an album with the specified album_id exists in 
 * the AlbumRepository.
 *
 * @param album_repository The AlbumRepository where the album should be checked.
 * @param album_id The ID of the album to check.
 * @return 1 if the album exists, 0 otherwise.
 */
int check_album_exists(AlbumRepository album_repository, const char *album_id);

/**
 * @brief Gets the number of individual albums by an artist.
 *
 * This function retrieves the number of albums associated with a specific 
 * artist in the AlbumRepository, identified by the artist's ID.
 *
 * @param album_repository The AlbumRepository containing the albums.
 * @param artist_id The ID of the artist whose albums are being counted.
 * @return A string representing the number of albums associated with the artist.
 */
char *get_artist_num_of_individual_albums_by_id(AlbumRepository album_repository, const char *artist_id);

#endif // _REPOSITORY_ALBUM_H_
