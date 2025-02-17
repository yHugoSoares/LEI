/**
 * @file load.h
 * @author Francisco Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for loading data into the database and validating it.
 */

#ifndef _LOAD_H_
#define _LOAD_H_

// Project headers for managing database and utility functions
#include "database.h"
#include "string_pool.h"
#include "utils.h"

/**
 * @brief Loads data from a dataset file, validates each entry, and stores it in a repository.
 *
 * This function opens the dataset file, reads each line, and validates the data using the provided 
 * `validate_func`. If the data is valid, it is processed and inserted into the database and repository 
 * using the provided `create_func` and `load_func`. Invalid entries are written to an errors file.
 *
 * @param dataset_folder_path The path to the folder containing the dataset.
 * @param data_file_name The name of the file containing the dataset to be loaded.
 * @param errors_file_path The path to the file where invalid entries will be logged.
 * @param database The database where valid data will be stored.
 * @param string_pool A pool for managing string memory used in the dataset.
 * @param repository The repository where the valid entities will be loaded.
 * @param validate_func A function pointer to a validation function that checks if an entry is valid.
 * @param create_func A function pointer to a creation function that processes a line into an entity.
 * @param load_func A function pointer to a loading function that stores the created entity in the repository.
 */
void load(const char *dataset_folder_path, const char *data_file_name, const char *errors_file_path,
          Database database, StringPool string_pool, Repository repository,
          ValidateFunc validate_func, CreateFunc create_func, LoadFunc load_func);

#endif // _LOAD_H_
