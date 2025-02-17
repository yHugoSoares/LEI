/**
 * @file string_pool.h
 * @author Francisco Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file defining the String Pool structure and functions for managing strings.
 */

#ifndef STRING_POOL_H
#define STRING_POOL_H

#include <glib.h>

/**
 * @struct string_pool
 * @brief A structure representing a string pool that holds unique strings.
 */
typedef struct string_pool *StringPool;

/**
 * @brief Initializes a new string pool.
 *
 * This function creates a new instance of a string pool, which is a data structure used
 * to store and manage unique strings. The pool ensures that only one copy of each string
 * exists, helping save memory by reusing identical strings.
 *
 * @return A pointer to the newly created string pool.
 */
StringPool init_string_pool();

/**
 * @brief Gets the size of the string pool.
 *
 * This function returns the current number of unique strings stored in the pool.
 *
 * @param string_pool A pointer to the string pool.
 * @return The number of unique strings in the pool.
 */
int get_string_pool_size(StringPool string_pool);

/**
 * @brief Adds a string to the pool or retrieves it if it already exists.
 *
 * This function checks if the specified string is already present in the pool. If it exists,
 * it returns the existing string. If not, it adds the string to the pool and returns it.
 *
 * @param string_pool A pointer to the string pool.
 * @param str The string to be added to the pool.
 * @return The string from the pool (either newly added or already existing).
 */
const char *add_string(StringPool string_pool, const char *str);

/**
 * @brief Adds a list of strings to the pool.
 *
 * This function parses a comma-separated list of strings and adds each string to the pool.
 * It ensures that only unique strings are stored. The result is a list of strings, each
 * pointing to the pooled version.
 *
 * @param string_pool A pointer to the string pool.
 * @param str The string representing a comma-separated list.
 * @return A list of strings (pointers to the pooled strings).
 */
const char **add_list(StringPool string_pool, const char *str);

/**
 * @brief Frees the memory used by the string pool.
 *
 * This function deallocates the memory used by the string pool, including the underlying
 * hash table and any dynamically allocated strings.
 *
 * @param string_pool A pointer to the string pool to be freed.
 */
void free_string_pool(StringPool string_pool);

#endif // STRING_POOL_H
