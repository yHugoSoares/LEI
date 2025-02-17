/**
 * @file repository_history.h
 * @author Francisco Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing History repository operations.
 */

#ifndef _REPOSITORY_HISTORY_H_
#define _REPOSITORY_HISTORY_H_

// Project headers
#include "utils.h"
#include "history.h" 
#include "string_pool.h"
#include "data_container.h"

/**
 * @brief Opaque structure representing a HistoryRepository.
 *
 * This structure represents a repository that handles historical data related to
 * music plays or events, allowing access to user history data.
 */
typedef struct history_repository *HistoryRepository;

/**
 * @brief Initializes a HistoryRepository instance.
 *
 * Creates and initializes an instance of HistoryRepository, which is used to store and manage
 * historical data related to music plays by users.
 *
 * @return A pointer to the initialized HistoryRepository instance.
 */
HistoryRepository init_history_repository();

/**
 * @brief Frees the memory allocated for a HistoryRepository instance.
 *
 * Frees the memory and resources associated with a HistoryRepository, cleaning up the stored historical data.
 *
 * @param history_data The HistoryRepository instance to free.
 */
void free_history_repository(HistoryRepository history_data);

/**
 * @brief Loads a history into the repository.
 *
 * Loads a History entity into the history repository, adding it to the system's storage.
 *
 * @param string_pool A string pool to optimize memory usage.
 * @param history_repository The history repository where the entity will be stored.
 * @param history The History entity to load into the repository.
 */
void load_history(StringPool string_pool, HistoryRepository history_repository, History history);

/**
 * @brief Checks if a history exists in the repository.
 *
 * Checks if a history exists in the repository using the unique ID of the history.
 *
 * @param history_repository The history repository.
 * @param history_id The ID of the history to check.
 * @return 1 if the history exists, 0 if the history does not exist.
 */
int check_history_exists(HistoryRepository history_repository, const char *history_id);

/**
 * @brief Gets the music ID of a history.
 *
 * Retrieves the music ID associated with a history in the repository.
 *
 * @param history_repository The history repository.
 * @param history_id The ID of the history whose music ID is to be retrieved.
 * @return The music ID associated with the history.
 */
char *get_history_music_id_by_id(HistoryRepository history_repository, const char *history_id);

/**
 * @brief Gets the year of a history.
 *
 * Retrieves the year in which a specific history occurred.
 *
 * @param history_repository The history repository.
 * @param history_id The ID of the history whose year is to be retrieved.
 * @return The year associated with the history.
 */
char *get_history_year_by_id(HistoryRepository history_repository, const char *history_id);

/**
 * @brief Gets the date of a history.
 *
 * Retrieves the date when a history occurred in the repository.
 *
 * @param history_repository The history repository.
 * @param history_id The ID of the history whose date is to be retrieved.
 * @return The date associated with the history.
 */
char *get_history_date_by_id(HistoryRepository history_repository, const char *history_id);

/**
 * @brief Gets the duration of a history.
 *
 * Retrieves the duration of the history event, for example, the duration of a played song.
 *
 * @param history_repository The history repository.
 * @param history_id The ID of the history whose duration is to be retrieved.
 * @return The duration associated with the history.
 */
char *get_history_duration_by_id(HistoryRepository history_repository, const char *history_id);

/**
 * @brief Gets the hour of a history.
 *
 * Retrieves the time when a history occurred in the repository.
 *
 * @param history_repository The history repository.
 * @param history_id The ID of the history whose hour is to be retrieved.
 * @return The hour associated with the history.
 */
char *get_history_hour_by_id(HistoryRepository history_repository, const char *history_id);

/**
 * @brief Gets the elapsed time for a history.
 *
 * Retrieves the elapsed time of the history from its start to the current time or the end of the event.
 *
 * @param history_repository The history repository.
 * @param history_id The ID of the history whose elapsed time is to be retrieved.
 * @return The elapsed time of the history in seconds.
 */
int get_history_elapsed_time_by_id(HistoryRepository history_repository, const char *history_id);

/**
 * @brief Iterates over all histories, adjusting the date.
 *
 * This function iterates over all histories in the repository and applies a date adjustment function.
 *
 * @param history_repository The history repository.
 * @param func The function to apply to each history (likely to adjust the date).
 * @param data Data container associated with the function to be passed during iteration.
 */
void foreach_history_adjusted_date(HistoryRepository history_repository, IterDataFunc func, DataContainer data);

/**
 * @brief Iterates over histories based on a specific date.
 *
 * This function iterates over all histories in a repository, filtering those corresponding to a specific date.
 *
 * @param history_repository The history repository.
 * @param date The date to filter the histories by.
 * @param func The function to apply to each history matching the date.
 * @param data Data container associated with the function to be passed during iteration.
 */
void foreach_history_id_from_date(HistoryRepository history_repository, const char *date, IterDataFunc func, DataContainer data);

/**
 * @brief Iterates over histories based on a specific user ID.
 *
 * This function iterates over all histories in a repository, filtering those belonging to a specific user.
 *
 * @param history_repository The history repository.
 * @param user_id The user ID whose histories are to be iterated.
 * @param func The function to apply to each of the user's histories.
 * @param data Data container associated with the function to be passed during iteration.
 */
void foreach_history_id_from_user_id(HistoryRepository history_repository, const char *user_id, IterDataFunc func, DataContainer data);

#endif // _REPOSITORY_HISTORY_H_
