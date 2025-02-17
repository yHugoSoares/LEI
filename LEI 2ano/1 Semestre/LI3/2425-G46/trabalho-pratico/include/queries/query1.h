/**
 * @file query1.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for query 1 functions, which fetch user and artist details from the database.
 */

#ifndef _QUERY1_H_  
#define _QUERY1_H_

// Project headers
#include "database.h"  
#include "output.h"    

void query1(Database data, char *args, Output output, char *spacer);

#endif  // _QUERY1_H_
