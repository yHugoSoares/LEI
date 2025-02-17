/**
 * @file syntatic_validation.h
 * @author Francico Martins a106902
 *         Marco Sevegrand a106807
 *         Hugo Soares a107293
 * @date 28 Dec 2024
 * @brief Header file for syntactic validation functions.
 */

#ifndef _SYNTATIC_VALIDATION_H_
#define _SYNTATIC_VALIDATION_H_

/**
 * @brief Validates the syntactic format of a date.
 *
 * This function checks if the given date string follows a valid format (e.g., "YYYY/MM/DD").
 *
 * @param date A string representing the date to be validated.
 * @return 1 if the date format is valid, 0 otherwise.
 */
int validate_date(const char *date);

/**
 * @brief Validates the syntactic format of a duration.
 *
 * This function checks if the given duration string is in a valid format.
 *
 * @param duration A string representing the duration to be validated.
 * @return 1 if the duration format is valid, 0 otherwise.
 */
int validate_duration(const char *duration);

/**
 * @brief Validates the syntactic format of an email.
 *
 * This function checks if the given email string follows a valid email format (e.g., "user@exemple.com").
 *
 * @param email A string representing the email to be validated.
 * @return 1 if the email format is valid, 0 otherwise.
 */
int validate_email(const char *email);

/**
 * @brief Validates the syntactic format of a subscription.
 *
 * This function checks if the given subscription string follows the expected format (e.g., "normal", "premium"). 
 *
 * @param subscription A string representing the subscription type to be validated.
 * @return 1 if the subscription format is valid, 0 otherwise.
 */
int validate_subscription(const char *subscription);

/**
 * @brief Validates the syntactic format of a platform name.
 *
 * This function checks if the given platform name string follows the expected format (e.g., "mobile", "desktop").
 *
 * @param platform A string representing the platform name to be validated.
 * @return 1 if the platform name is valid, 0 otherwise.
 */
int validate_platform(const char *platform);

/**
 * @brief Validates the syntactic format of a list.
 *
 * This function checks if the given list string follows a valid format (e.g., "[...]").
 *
 * @param list A string representing the list to be validated.
 * @return 1 if the list format is valid, 0 otherwise.
 */
int validate_list(const char *list);

#endif
