/**
 * @file utils.h
 * @author Francisco Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file containing utility functions for string manipulation, time calculations,
 *        and memory management.
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <glib.h>

/**
 * @brief Gets the length of an array of strings.
 *
 * This function iterates through an array of strings (terminated by a NULL pointer)
 * and calculates the number of strings in the array.
 *
 * @param array A pointer to the array of strings.
 * @return The number of strings in the array.
 */
int get_array_length(const char **array);

/**
 * @brief Frees all memory allocated for multiple pointers.
 *
 * This function allows freeing of multiple pointers passed as arguments in a
 * variadic fashion. The function frees each pointer and continues until a NULL
 * pointer is encountered in the argument list.
 *
 * @param first The first pointer to be freed.
 * @param ... The rest of the pointers to be freed.
 */
void g_free_all(gpointer first, ...);

/**
 * @brief Destroys multiple GHashTable structures.
 *
 * This function allows for the destruction of multiple GHashTables. The function
 * will iterate through all tables and free each one passed as an argument in a
 * variadic list.
 *
 * @param first The first GHashTable to be destroyed.
 * @param ... Additional GHashTables to be destroyed.
 */
void g_hash_table_destroy_all(GHashTable *first, ...);

/**
 * @brief Converts a string to lowercase.
 *
 * This function takes a string as input and returns a new string where all the
 * characters have been converted to lowercase.
 *
 * @param str The string to be converted to lowercase.
 * @return A newly allocated string in lowercase.
 */
char *to_lower_case(const char *str);

/**
 * @brief Converts a duration in the format "hh:mm:ss" to the total number of seconds.
 *
 * This function takes a time string in the format "hh:mm:ss" and converts it to an integer
 * representing the total number of seconds.
 *
 * @param duration The duration string in "hh:mm:ss" format.
 * @return The total number of seconds represented by the duration.
 */
int duration_to_seconds(const char *duration);

/**
 * @brief Converts a number of seconds to a time string in the format "hh:mm:ss".
 *
 * This function takes a number of seconds and returns a string formatted as "hh:mm:ss".
 *
 * @param seconds The total number of seconds to be converted.
 * @return A string representing the time in "hh:mm:ss" format.
 */
char *seconds_to_duration(int seconds);

/**
 * @brief Extracts the year from a date string.
 *
 * This function takes a date string in the format "yyyy/mm/dd" and returns the year as a string.
 *
 * @param date The date string in "yyyy/mm/dd" format.
 * @return A newly allocated string containing only the year.
 */
char *get_year_from_date(const char *date);

/**
 * @brief Extracts the hour from a time string.
 *
 * This function takes a time string in the format "hh:mm:ss" and returns the hour as a string.
 *
 * @param time The time string in "hh:mm:ss" format.
 * @return A newly allocated string containing the hour.
 */
char *get_hour_from_time(const char *time);

/**
 * @brief Calculates the age based on a birthdate.
 *
 * This function calculates the age of a person given their birthdate. The date should
 * be in the format "yyyy/mm/dd". The function returns the calculated age as a string.
 *
 * @param birth_date The birthdate string in "yyyy/mm/dd" format.
 * @return A string representing the calculated age.
 */
char *calculate_age(const char *birth_date);

/**
 * @brief Adjusts a date to the nearest Sunday.
 *
 * This function takes a date in the format "yyyy/mm/dd" and returns a new date string
 * that represents the closest Sunday to the given date. The date is adjusted backward
 * if necessary to align with Sunday.
 *
 * @param date The input date string in "yyyy/mm/dd" format.
 * @return A string representing the adjusted date that is the nearest Sunday.
 */
char *adjust_date(const char *date);

/**
 * @brief Calculates the date for the next week.
 *
 * This function takes a date string in the format "yyyy/mm/dd" and returns a string
 * representing the same day of the next week.
 *
 * @param date The input date string in "yyyy/mm/dd" format.
 * @return A string representing the date exactly one week after the input date.
 */
char *get_next_week(const char *date);

#endif // _UTILS_H_
