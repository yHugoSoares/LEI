/**
 * @file repository_data.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing Data repository operations.
 */

#ifndef _REPOSITORY_DATA_H_
#define _REPOSITORY_DATA_H_

// Third-party library headers
#include <glib.h> 

// Project headers
#include "string_pool.h"

/**
 * @brief Opaque structure representing a DataRepository.
 *
 * This structure is used to represent a repository for handling various data
 * related to artists, genres, and users. It is implemented as an opaque type
 * to hide its internal details from the user.
 */
typedef struct data_repository *DataRepository;

/**
 * @brief Initializes a DataRepository instance.
 *
 * Creates and initializes a DataRepository, which is used for storing and
 * managing data related to artists, genres, users, and other relevant information.
 *
 * @return A pointer to the initialized DataRepository instance.
 */
DataRepository init_data_repository();

/**
 * @brief Frees the memory allocated for a DataRepository instance.
 *
 * This function releases the memory and associated resources used by the
 * DataRepository.
 *
 * @param data_repository The DataRepository instance to be freed.
 */
void free_data_repository(DataRepository data_repository);

/**
 * @brief Increments the number of streams for a given artist by their artist_id.
 *
 * This function updates the stream count for an artist based on their unique ID.
 *
 * @param string_pool A pool of strings for memory optimization.
 * @param data_repository The DataRepository where the artist's data is stored.
 * @param artist_id The ID of the artist whose stream count will be incremented.
 */
void increment_num_of_streams_by_artist_id(StringPool string_pool, DataRepository data_repository, const char *artist_id);

/**
 * @brief Gets the number of streams for a given artist.
 *
 * Retrieves the number of streams associated with an artist based on their artist_id.
 *
 * @param data_repository The DataRepository where the artist's data is stored.
 * @param artist_id The ID of the artist whose stream count is to be fetched.
 * @return The number of streams for the specified artist.
 */
int get_artist_num_of_streams_by_id(DataRepository data_repository, const char *artist_id);

/**
 * @brief Increases the size of an artist's discography.
 *
 * This function increases the discography size (number of albums or tracks) for an artist.
 *
 * @param string_pool A pool of strings for memory optimization.
 * @param data_repository The DataRepository where the artist's data is stored.
 * @param artist_id The ID of the artist whose discography size is to be updated.
 * @param increase The amount by which the discography size should be increased.
 */
void increase_discography_size_by_artist_id(StringPool string_pool, DataRepository data_repository, const char *artist_id, int increase);

/**
 * @brief Gets the total duration of an artist's discography.
 *
 * This function retrieves the total duration (in minutes or another unit) of the artist's discography.
 *
 * @param data_repository The DataRepository where the artist's data is stored.
 * @param artist_id The ID of the artist whose discography duration is to be fetched.
 * @return The total duration of the artist's discography.
 */
char *get_artist_discography_duration_by_id(DataRepository data_repository, const char *artist_id);

/**
 * @brief Creates a sorted list of artists based on their discography size.
 *
 * This function generates a sorted list of artists based on their discography size 
 * using a provided comparison function.
 *
 * @param data_repository The DataRepository containing artist data.
 * @param compare_keys_by_value A comparison function used to sort the artists.
 */
void make_sorted_artist_list_from_discography_size_hashtable(DataRepository data_repository, GCompareDataFunc compare_keys_by_value);

/**
 * @brief Adds a country to an artist's profile.
 *
 * This function associates a country with an artist based on their artist_id.
 *
 * @param string_pool A pool of strings for memory optimization.
 * @param data_repository The DataRepository where the artist's data is stored.
 * @param artist_id The ID of the artist.
 * @param country The country to be associated with the artist.
 */
void add_country_by_artist_id(StringPool string_pool, DataRepository data_repository, const char *artist_id, const char *country);

/**
 * @brief Gets the top N largest artists by their discography size.
 *
 * This function returns the top N artists who have the largest discographies, optionally filtered by country.
 *
 * @param data_repository The DataRepository containing the artist data.
 * @param n The number of artists to return.
 * @param country The country filter for the artists (optional).
 * @return An array of artist IDs corresponding to the largest artists.
 */
char **get_n_largest_artists_by_discography_size(DataRepository data_repository, int n, char *country);

/**
 * @brief Updates the list of artist IDs sorted by their discography size.
 *
 * This function updates the list of artist IDs in the DataRepository, sorting them 
 * by the size of their discography.
 *
 * @param data_repository The DataRepository containing the artist data.
 * @param list A list of artist IDs to be sorted by their discography size.
 */
void update_artist_ids_sorted_by_discography_size(DataRepository data_repository, GList *list);

/**
 * @brief Increments the popularity of a genre based on the age group.
 *
 * This function updates the popularity of a genre within a specific age group.
 *
 * @param string_pool A pool of strings for memory optimization.
 * @param data_repository The DataRepository where genre popularity data is stored.
 * @param age The age group whose genre popularity will be updated.
 * @param genre The genre whose popularity will be increased.
 */
void increment_genre_popularity_by_age(StringPool string_pool, DataRepository data_repository, const char *age, const char *genre);

/**
 * @brief Adds the popularity of genres for a specific age group.
 *
 * This function adds the popularity data for multiple genres within a specified age range.
 *
 * @param string_pool A pool of strings for memory optimization.
 * @param data_repository The DataRepository where genre popularity data is stored.
 * @param genres_popularity_within_age_interval A hash table containing genre popularity data.
 * @param age The age group for which the genre popularity is being added.
 */
void add_genres_popularity_for_age(StringPool string_pool, DataRepository data_repository, GHashTable *genres_popularity_within_age_interval, char *age);

/**
 * @brief Adds an artist ID to a specific date.
 *
 * This function associates an artist with a specific date, perhaps for tracking 
 * streams or appearances.
 *
 * @param string_pool A pool of strings for memory optimization.
 * @param data_repository The DataRepository where the data is stored.
 * @param date The date when the artist appeared or performed.
 * @param artist_id The ID of the artist associated with the date.
 */
void add_artist_id_by_week(StringPool string_pool, DataRepository data_repository, const char *date, const char *artist_id);

/**
 * @brief Sets the top 10 all-time artist ID.
 *
 * This function sets an artist as the top 10 artist of all time.
 *
 * @param string_pool A pool of strings for memory optimization.
 * @param data_repository The DataRepository where the data is stored.
 * @param artist_id The ID of the artist to be set as the top 10.
 */
void set_top10_all_time_artist_id(StringPool string_pool, DataRepository data_repository, const char *artist_id);

/**
 * @brief Sets the number of top 10 occurrences.
 *
 * This function sets the number of occurrences of artists in the top 10 chart.
 *
 * @param data_repository The DataRepository where the data is stored.
 * @param most_top10_occurences The number of times an artist has appeared in the top 10.
 */
void set_most_top10_occurences(DataRepository data_repository, int most_top10_occurences);

/**
 * @brief Iterates over all artist IDs for a specific date.
 *
 * This function applies a provided function to each artist ID for a specific date.
 *
 * @param data_repository The DataRepository containing the artist data.
 * @param func The function to apply to each artist ID.
 * @param data The container of data to be passed to the function.
 */
void foreach_date_artist_ids(DataRepository data_repository, IterDataFunc func, DataContainer data);

/**
 * @brief Iterates over artist IDs for a specific date.
 *
 * This function iterates through the artist IDs associated with a specific date.
 *
 * @param data_repository The DataRepository containing the artist data.
 * @param date The date for which to fetch artist IDs.
 * @param func The function to apply to each artist ID.
 * @param data The container of data to be passed to the function.
 */
void foreach_artist_id_from_date(DataRepository data_repository, const char *date, IterDataFunc func, DataContainer data);

/**
 * @brief Gets the top 10 all-time artist ID.
 *
 * This function retrieves the artist ID that is set as the top 10 all-time artist.
 *
 * @param data_repository The DataRepository containing the artist data.
 * @return The artist ID of the top 10 all-time artist.
 */
char *get_top10_all_time_artist_id(DataRepository data_repository);

/**
 * @brief Gets the most number of top 10 occurrences.
 *
 * This function retrieves the highest number of times any artist has appeared in the top 10.
 *
 * @param data_repository The DataRepository containing the artist data.
 * @return The most top 10 occurrences as a string.
 */
char *get_most_top10_occurences(DataRepository data_repository);

/**
 * @brief Initializes user genre preferences.
 *
 * This function initializes the genre preferences for a set of users.
 *
 * @param data_repository The DataRepository where the data is stored.
 * @param user_ids An array of user IDs whose genre preferences are to be initialized.
 * @param genres An array of genre names.
 * @param num_of_users The number of users.
 * @param num_of_genres The number of genres.
 */
void init_users_genres_preferences(DataRepository data_repository, char **user_ids, char **genres, int num_of_users, int num_of_genres);

/**
 * @brief Increments a user's preference for a genre.
 *
 * This function increases the preference score for a specific genre for a user.
 *
 * @param data_repository The DataRepository containing the user preferences.
 * @param user_idx The index of the user whose genre preference will be incremented.
 * @param genre_idx The index of the genre whose preference will be increased.
 */
void increment_user_genre_preference(DataRepository data_repository, int user_idx, int genre_idx);

/**
 * @brief Gets the index of a genre.
 *
 * This function retrieves the index of a genre within the DataRepository.
 *
 * @param data_repository The DataRepository containing the genre data.
 * @param genre The name of the genre whose index is to be fetched.
 * @return The index of the specified genre.
 */
int get_genre_index(DataRepository data_repository, const char *genre);

/**
 * @brief Gets a list of recommended users for a given user.
 *
 * This function retrieves a list of users who are recommended based on their genre preferences.
 *
 * @param data_repository The DataRepository containing user data.
 * @param user_id The ID of the user for whom the recommendations are made.
 * @param n The number of recommended users to return.
 * @return An array of user IDs who are recommended.
 */
char **get_recommended_users(DataRepository data_repository, char *user_id, int n);

#endif // _REPOSITORY_DATA_H_
