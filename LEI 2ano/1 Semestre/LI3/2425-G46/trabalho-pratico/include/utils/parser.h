/**
 * @file parser.h
 * @author Francisco Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for parsing and manipulating strings and lists for various data formats.
 */

#ifndef _PARSER_H_
#define _PARSER_H_

// Standard library headers
#include <stdio.h>

// Third-party library headers
#include <glib.h>

/**
 * @brief Removes all occurrences of a specified character from a string.
 *
 * This function takes a string and removes all instances of the specified character.
 *
 * @param str The input string from which characters will be removed.
 * @param c The character to be removed from the string.
 * @return A new string with the specified character removed.
 */
char *remove_char(const char *str, char c);

/**
 * @brief Parses a date string in the format "YYYY/MM/DD" into year, month, and day integers.
 *
 * This function extracts the year, month, and day components from a date string and stores them in the provided pointers.
 *
 * @param date The input date string in the format "YYYY/MM/DD".
 * @param year Pointer to store the parsed year.
 * @param month Pointer to store the parsed month.
 * @param day Pointer to store the parsed day.
 */
void parse_date(const char *date, int *year, int *month, int *day);

/**
 * @brief Parses a time string in the format "HH:MM:SS" into hours, minutes, and seconds integers.
 *
 * This function extracts the hours, minutes, and seconds components from a time string and stores them in the provided pointers.
 *
 * @param time The input time string in the format "HH:MM:SS".
 * @param hours Pointer to store the parsed hours.
 * @param minutes Pointer to store the parsed minutes.
 * @param seconds Pointer to store the parsed seconds.
 */
void parse_time(const char *time, int *hours, int *minutes, int *seconds);

/**
 * @brief Parses a comma-separated list into an array of strings.
 *
 * This function splits a string (representing a list of items separated by commas) into an array of strings.
 *
 * @param list The input string representing the list.
 * @return An array of strings representing the parsed list items.
 */
char **parse_list(const char *list);

/**
 * @brief Frees the memory allocated for a list of strings.
 *
 * This function frees the memory allocated for the array of strings returned by `parse_list`.
 *
 * @param list The array of strings to be freed.
 */
void free_list(char **list);

/**
 * @brief Parses a line of text into an array of fields.
 *
 * This function splits a line of text (representing a set of fields) into an array of strings, each representing a field.
 *
 * @param line The input string representing the line of fields.
 * @return An array of strings representing the parsed fields.
 */
char **parse_line(const char *line);

/**
 * @brief Frees the memory allocated for an array of fields.
 *
 * This function frees the memory allocated for the array of strings returned by `parse_line`.
 *
 * @param fields The array of fields to be freed.
 */
void free_fields(char **fields);

#endif  // _PARSER_H_
