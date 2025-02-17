/**
 * @file output.h
 * @author Francisco Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for managing output files and string arrays using GPtrArray.
 */

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

// Standard library headers
#include <stdio.h>

// Third-party library headers
#include <glib.h>
#include <ncurses.h>

// Project headers
#include "utils.h"

typedef struct output *Output;

/**
 * @brief Initializes a new Output structure.
 * 
 * Allocates memory and initializes an instance of the `Output` structure 
 * for managing dynamic string arrays.
 *
 * @return A pointer to the newly created Output instance.
 */
Output init_output();

/**
 * @brief Frees memory used by an Output instance.
 *
 * Deallocates memory for the `Output` structure, including all dynamically
 * allocated strings within the GPtrArray.
 *
 * @param output The Output instance to free.
 */
void free_output(Output output);

/**
 * @brief Adds a formatted line to the Output instance.
 *
 * Concatenates tokens using the specified spacer and adds the resulting string
 * to the Output structure's array.
 *
 * @param output The Output instance to modify.
 * @param tokens Array of string tokens to concatenate.
 * @param spacer The string used to separate tokens.
 */
void add_line_to_output(Output output, char **tokens, char *spacer);

/**
 * @brief Writes the Output instance's lines to a file.
 *
 * Writes each line stored in the Output instance to the specified file path.
 *
 * @param output The Output instance to write.
 * @param output_file_path The path of the file to write to.
 */
void write_output_to_file(Output output, char *output_file_path);

/**
 * @brief Displays the Output instance's lines in a terminal window.
 *
 * Renders the lines stored in the Output instance to an ncurses WINDOW.
 * Limits the display to the specified number of lines.
 *
 * @param output The Output instance to display.
 * @param output_win The ncurses WINDOW to render the output.
 * @param max_lines The maximum number of lines to display.
 */
void write_output_to_terminal(Output output, WINDOW *output_win, int max_lines);

#endif // _OUTPUT_H_
