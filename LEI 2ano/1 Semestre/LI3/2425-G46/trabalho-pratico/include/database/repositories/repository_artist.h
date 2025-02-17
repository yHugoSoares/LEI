/**
 * @file repository_artist.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing Artist repository operations.
 */

#ifndef _REPOSITORY_ARTIST_H_
#define _REPOSITORY_ARTIST_H_

// Project headers
#include "data_container.h"  
#include "artist.h"          
#include "string_pool.h"     

/**
 * @brief Opaque structure representing an ArtistRepository.
 *
 * This structure is used to represent the repository that holds the artists.
 * It is implemented as an opaque type to hide the internal details.
 */
typedef struct artist_repository *ArtistRepository;

/**
 * @brief Initializes an ArtistRepository instance.
 *
 * This function creates and initializes an empty ArtistRepository.
 *
 * @return A pointer to the initialized ArtistRepository.
 */
ArtistRepository init_artist_repository();

/**
 * @brief Frees memory allocated for an ArtistRepository instance.
 *
 * This function releases the memory and resources associated with an ArtistRepository.
 *
 * @param artist_data The ArtistRepository instance to be freed.
 */
void free_artist_repository(ArtistRepository artist_data);

/**
 * @brief Loads an Artist into the repository.
 *
 * This function loads an Artist into the given ArtistRepository, associating it 
 * with the provided string pool for memory optimization.
 *
 * @param string_pool A pool of strings for efficient memory management.
 * @param artist_repository The ArtistRepository where the artist will be loaded.
 * @param artist The Artist entity to be loaded into the repository.
 */
void load_artist(StringPool string_pool, ArtistRepository artist_repository, Artist artist);

/**
 * @brief Checks if an artist exists in the repository.
 *
 * This function checks if an artist with the specified artist_id exists in 
 * the ArtistRepository.
 *
 * @param artist_data The ArtistRepository where the artist should be checked.
 * @param artist_id The ID of the artist to check.
 * @return 1 if the artist exists, 0 otherwise.
 */
int check_artist_exists(ArtistRepository artist_data, const char *artist_id);

/**
 * @brief Gets the name of the artist by their ID.
 *
 * This function retrieves the name of the artist corresponding to the given artist_id.
 *
 * @param artist_repository The ArtistRepository containing the artist data.
 * @param artist_id The ID of the artist whose name is to be retrieved.
 * @return The name of the artist as a string.
 */
char *get_artist_name_by_id(ArtistRepository artist_repository, const char *artist_id);

/**
 * @brief Gets the country of the artist by their ID.
 *
 * This function retrieves the country of the artist corresponding to the given artist_id.
 *
 * @param artist_repository The ArtistRepository containing the artist data.
 * @param artist_id The ID of the artist whose country is to be retrieved.
 * @return The country of the artist as a string.
 */
char *get_artist_country_by_id(ArtistRepository artist_repository, const char *artist_id);

/**
 * @brief Gets the type of the artist by their ID.
 *
 * This function retrieves the type (e.g., solo, band, etc.) of the artist corresponding 
 * to the given artist_id.
 *
 * @param artist_repository The ArtistRepository containing the artist data.
 * @param artist_id The ID of the artist whose type is to be retrieved.
 * @return The type of the artist as a string.
 */
char *get_artist_type_by_id(ArtistRepository artist_repository, const char *artist_id);

/**
 * @brief Gets the recipe per stream of the artist by their ID.
 *
 * This function retrieves the recipe (or earnings) per stream for the artist corresponding 
 * to the given artist_id.
 *
 * @param artist_repository The ArtistRepository containing the artist data.
 * @param artist_id The ID of the artist whose recipe per stream is to be retrieved.
 * @return The recipe per stream of the artist as a string.
 */
char *get_artist_recipe_per_stream_by_id(ArtistRepository artist_repository, const char *artist_id);

/**
 * @brief Gets the number of constituents of the artist by their ID.
 *
 * This function retrieves the number of constituents (members or collaborators) of the 
 * artist corresponding to the given artist_id.
 *
 * @param artist_repository The ArtistRepository containing the artist data.
 * @param artist_id The ID of the artist whose number of constituents is to be retrieved.
 * @return The number of constituents as an integer.
 */
int get_artist_num_of_constituents_by_id(ArtistRepository artist_repository, const char *artist_id);

/**
 * @brief Iterates through artist IDs from a constituent's ID.
 *
 * This function iterates through the artist IDs that are associated with a given constituent 
 * ID and applies the provided function to each of them.
 *
 * @param artist_repository The ArtistRepository containing the artist data.
 * @param constituent_id The ID of the constituent whose artist IDs are to be iterated.
 * @param func The function to apply to each artist ID.
 * @param container A container holding data to be passed to the function.
 */
void foreach_artist_id_from_constituent_id(ArtistRepository artist_repository, const char *constituent_id, IterDataFunc func, DataContainer container);

#endif // _REPOSITORY_ARTIST_H_
