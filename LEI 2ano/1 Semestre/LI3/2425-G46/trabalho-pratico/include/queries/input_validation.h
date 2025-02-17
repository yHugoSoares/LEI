/**
 * @file input_validation.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for validating inputs.
 */

#ifndef _INPUT_VALIDATION_H_
#define _INPUT_VALIDATION_H_

/**
 * @brief Validates the directory path to ensure it contains required files.
 * 
 * @param directory Path to the directory to validate.
 * @return int 1 if valid, 0 otherwise.
 */
int validate_directory(const char *directory);

/**
 * @brief Validates user input based on the selected query.
 * 
 * @param selected_query The query type for which the input is validated.
 * @param input The input string to validate.
 * @return int 1 if valid, 0 otherwise.
 */
int validate_input(int selected_query, char *input);

#endif // _INPUT_VALIDATION_H_
