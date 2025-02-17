/**
 * @file repository_user.h
 * @author Francisco Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing User repository operations.
 */

#ifndef _REPOSITORY_USER_H_
#define _REPOSITORY_USER_H_

// Project headers
#include "user.h"
#include "string_pool.h" 

/**
 * @brief Opaque structure representing a UserRepository.
 *
 * This structure represents a repository that manages information related to users
 * and allows storing and accessing user data within the system.
 */
typedef struct user_repository *UserRepository;

/**
 * @brief Initializes a UserRepository instance.
 *
 * Creates and initializes an instance of UserRepository, which is used to store and manage
 * user-related data in the system.
 *
 * @return A pointer to the initialized UserRepository instance.
 */
UserRepository init_user_repository();

/**
 * @brief Frees the memory allocated for a UserRepository instance.
 *
 * Frees the memory and resources associated with a UserRepository, cleaning up the stored user data.
 *
 * @param user_data The UserRepository instance to free.
 */
void free_user_repository(UserRepository user_data);

/**
 * @brief Loads a user entity into the repository.
 *
 * Loads a User entity into the user repository, adding it to the system's storage.
 *
 * @param string_pool A string pool to optimize memory usage.
 * @param user_repository The user repository where the entity will be stored.
 * @param user The User entity to load into the repository.
 */
void load_user(StringPool string_pool, UserRepository user_repository, User user);

/**
 * @brief Checks if a user exists in the repository.
 *
 * Checks if a user exists in the repository using the user's unique ID.
 *
 * @param user_repository The user repository.
 * @param user_id The ID of the user to check.
 * @return 1 if the user exists, 0 if the user does not exist.
 */
int check_user_exists(UserRepository user_repository, char *user_id);

/**
 * @brief Gets the email of a user by their ID.
 *
 * Retrieves the email of a user based on their ID.
 *
 * @param user_repository The user repository.
 * @param user_id The ID of the user whose email is to be retrieved.
 * @return The email of the user.
 */
char *get_user_email_by_id(UserRepository user_repository, char *user_id);

/**
 * @brief Gets the first name of a user by their ID.
 *
 * Retrieves the first name of a user based on their ID.
 *
 * @param user_repository The user repository.
 * @param user_id The ID of the user whose first name is to be retrieved.
 * @return The first name of the user.
 */
char *get_user_first_name_by_id(UserRepository user_repository, char *user_id);

/**
 * @brief Gets the last name of a user by their ID.
 *
 * Retrieves the last name of a user based on their ID.
 *
 * @param user_repository The user repository.
 * @param user_id The ID of the user whose last name is to be retrieved.
 * @return The last name of the user.
 */
char *get_user_last_name_by_id(UserRepository user_repository, char *user_id);

/**
 * @brief Gets the age of a user by their ID.
 *
 * Retrieves the age of a user based on their ID.
 *
 * @param user_repository The user repository.
 * @param user_id The ID of the user whose age is to be retrieved.
 * @return The age of the user.
 */
char *get_user_age_by_id(UserRepository user_repository, char *user_id);

/**
 * @brief Gets the country of a user by their ID.
 *
 * Retrieves the country of a user based on their ID.
 *
 * @param user_repository The user repository.
 * @param user_id The ID of the user whose country is to be retrieved.
 * @return The country of the user.
 */
char *get_user_country_by_id(UserRepository user_repository, char *user_id);

/**
 * @brief Gets all user IDs from the repository.
 *
 * Retrieves a list of all user IDs stored in the repository.
 *
 * @param user_repository The user repository.
 * @return An array of strings containing the user IDs.
 */
char **get_user_ids(UserRepository user_repository);

/**
 * @brief Gets the number of users in the repository.
 *
 * Retrieves the total number of users stored in the repository.
 *
 * @param user_repository The user repository.
 * @return The total number of users.
 */
int get_num_of_users(UserRepository user_repository);

/**
 * @brief Iterates over all liked musics of a user.
 *
 * This function iterates over all songs that a user has marked as favorites or has listened to.
 *
 * @param user_repository The user repository.
 * @param func The function to apply to each song that the user has listened to or liked.
 * @param container A data container that will be passed to the function for each iteration.
 */
void foreach_user_liked_musics(UserRepository user_repository, IterDataFunc func, DataContainer container);

#endif // _REPOSITORY_USER_H_
