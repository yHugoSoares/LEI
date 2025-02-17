/**
 * @file data_container.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for DataContainer functions, which encapsulate various data types 
 *        like integer, double, void pointers, and a GHashTable.
 * 
 * This header provides functions to create, manipulate, and retrieve elements from a 
 * container structure that holds an integer, a double, a pointer to some data, an array of data, 
 * and a GHashTable. The functions allow for flexible handling of different types of data within 
 * a single container.
 */

#ifndef _DATA_CONTAINER_H_
#define _DATA_CONTAINER_H_

#include <glib.h>

/**
 * @brief A structure that holds different types of data.
 * 
 * The structure contains:
 * - An integer (i)
 * - A double (d)
 * - A void pointer (data) for arbitrary data storage
 * - A pointer to an array of void pointers (data_array)
 * - A GHashTable for key-value pair storage
 */
typedef struct data_container *DataContainer;

/**
 * @brief Initializes a DataContainer structure.
 * 
 * This function allocates memory for a DataContainer and sets its fields.
 * 
 * @param i The integer to set in the container.
 * @param d The double to set in the container.
 * @param data A pointer to arbitrary data.
 * @param data_array An array of void pointers.
 * @param hashtable A GHashTable to store key-value pairs.
 * @return A newly created DataContainer.
 */
DataContainer init_data_container(int i, double d, void *data, void **data_array, GHashTable *hashtable);

/**
 * @brief Sets the integer value in the DataContainer.
 * 
 * @param container The DataContainer to modify.
 * @param i The integer value to set.
 */
void set_i(DataContainer container, int i);

/**
 * @brief Sets the double value in the DataContainer.
 * 
 * @param container The DataContainer to modify.
 * @param d The double value to set.
 */
void set_d(DataContainer container, double d);

/**
 * @brief Sets the arbitrary data pointer in the DataContainer.
 * 
 * @param container The DataContainer to modify.
 * @param data A pointer to the arbitrary data to set.
 */
void set_data(DataContainer container, void *data);

/**
 * @brief Sets the array of data pointers in the DataContainer.
 * 
 * @param container The DataContainer to modify.
 * @param data_array A pointer to the array of data pointers to set.
 */
void set_data_array(DataContainer container, void **data_array);

/**
 * @brief Sets the GHashTable in the DataContainer.
 * 
 * @param container The DataContainer to modify.
 * @param hashtable A GHashTable to set.
 */
void set_hashtable(DataContainer container, GHashTable *hashtable);

/**
 * @brief Gets the integer value from the DataContainer.
 * 
 * @param container The DataContainer from which to retrieve the integer.
 * @return The integer stored in the DataContainer.
 */
int get_i(DataContainer container);

/**
 * @brief Gets the double value from the DataContainer.
 * 
 * @param container The DataContainer from which to retrieve the double.
 * @return The double stored in the DataContainer.
 */
double get_d(DataContainer container);

/**
 * @brief Gets the arbitrary data pointer from the DataContainer.
 * 
 * @param container The DataContainer from which to retrieve the data pointer.
 * @return A pointer to the data stored in the DataContainer.
 */
void *get_data(DataContainer container);

/**
 * @brief Gets the array of data pointers from the DataContainer.
 * 
 * @param container The DataContainer from which to retrieve the data array.
 * @return A pointer to the array of data pointers stored in the DataContainer.
 */
void **get_data_array(DataContainer container);

/**
 * @brief Gets the GHashTable from the DataContainer.
 * 
 * @param container The DataContainer from which to retrieve the GHashTable.
 * @return A GHashTable stored in the DataContainer.
 */
GHashTable *get_hashtable(DataContainer container);

/**
 * @brief Frees the memory used by the DataContainer.
 * 
 * This function frees the memory allocated for the DataContainer structure.
 * 
 * @param container The DataContainer to destroy.
 */
void destroy_data_container(DataContainer container);

#endif // _DATA_CONTAINER_H_
