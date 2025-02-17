/**
 * @file history.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing History entities.
 */

#ifndef _HISTORY_H_
#define _HISTORY_H_

// Project headers
#include "string_pool.h"

/**
 * @brief Opaque structure representing a History entity.
 */
typedef struct history *History;

/**
 * @brief Creates a History entity from the given fields.
 *
 * Initializes a History structure using the provided string pool and fields array.
 *
 * @param string_pool A pool to store strings for memory optimization.
 * @param fields Array of strings containing the history data.
 * @return A pointer to the created History.
 */
History create_history(StringPool string_pool, char **fields);

/**
 * @brief Frees memory allocated for a History entity.
 *
 * Releases all resources associated with the History.
 *
 * @param history The History to be freed.
 */
void free_history(History history);

/**
 * @brief Gets the ID of the history.
 *
 * @param history The History entity.
 * @return The history's ID.
 */
const char *get_history_id(History history);

/**
 * @brief Gets the user ID associated with the history.
 *
 * @param history The History entity.
 * @return The user ID associated with the history.
 */
const char *get_history_user_id(History history);

/**
 * @brief Gets the music ID associated with the history.
 *
 * @param history The History entity.
 * @return The music ID associated with the history.
 */
const char *get_history_music_id(History history);

/**
 * @brief Gets the date of the history.
 *
 * @param history The History entity.
 * @return The history's date.
 */
const char *get_history_date(History history);

/**
 * @brief Gets the time of the history.
 *
 * @param history The History entity.
 * @return The history's time.
 */
const char *get_history_time(History history);

/**
 * @brief Gets the duration of the history.
 *
 * @param history The History entity.
 * @return The history's duration.
 */
const char *get_history_duration(History history);

#endif // _HISTORY_H_
