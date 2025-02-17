/**
 * @file user.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing User entities.
 */

#ifndef USER_H
#define USER_H

// Project headers
#include "string_pool.h"
#include "data_container.h"

// Define the User structure
typedef struct user *User;

/**
 * @brief Creates a User entity from the given fields.
 *
 * Initializes a User structure using the provided string pool and fields array.
 *
 * @param string_pool A pool to store strings for memory optimization.
 * @param fields Array of strings containing the user data.
 * @return A pointer to the created User.
 */
User create_user(StringPool string_pool, char **fields);

/**
 * @brief Frees memory allocated for a User entity.
 *
 * Releases all resources associated with the User.
 *
 * @param user The User to be freed.
 */
void free_user(User user);

/**
 * @brief Gets the ID of the user.
 *
 * @param user The User entity.
 * @return The user's ID.
 */
const char *get_user_id(User user);

/**
 * @brief Gets the email of the user.
 *
 * @param user The User entity.
 * @return The user's email.
 */
const char *get_user_email(User user);

/**
 * @brief Gets the first name of the user.
 *
 * @param user The User entity.
 * @return The user's first name.
 */
const char *get_user_first_name(User user);

/**
 * @brief Gets the last name of the user.
 *
 * @param user The User entity.
 * @return The user's last name.
 */
const char *get_user_last_name(User user);

/**
 * @brief Gets the birth date of the user.
 *
 * @param user The User entity.
 * @return The user's birth date.
 */
const char *get_user_birth_date(User user);

/**
 * @brief Gets the country of the user.
 *
 * @param user The User entity.
 * @return The user's country.
 */
const char *get_user_country(User user);

/**
 * @brief Gets the liked music IDs associated with the user.
 *
 * @param user The User entity.
 * @return An array of liked music IDs associated with the user.
 */
const char **get_user_liked_music_ids(User user);

/**
 * @brief Gets the list of liked musics for the user.
 *
 * @param user The User entity.
 * @return A list of liked musics (GList).
 */
GList *get_user_liked_musics(User user);

/**
 * @brief Applies a function to each liked music of the user.
 *
 * This function iterates through each liked music and applies the provided callback.
 *
 * @param user The User entity.
 * @param func A function to be applied to each liked music.
 * @param container A data container for the iteration.
 */
void foreach_liked_musics_from_user(User user, IterDataFunc func, DataContainer container);

#endif // USER_H
