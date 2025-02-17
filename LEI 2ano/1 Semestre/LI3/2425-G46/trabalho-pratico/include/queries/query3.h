/**
 * @file query3.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for query 3, which retrieves the popularity of music genres within a given age range.
 */

#ifndef _QUERY3_H_  // Check if _QUERY3_H is not defined
#define _QUERY3_H_  // Define _QUERY3_H to avoid double inclusion

// Project headers
#include "database.h"
#include "output.h"

void query3(Database data, char *args, Output output, char *spacer);

#endif  // _QUERY3_H_
