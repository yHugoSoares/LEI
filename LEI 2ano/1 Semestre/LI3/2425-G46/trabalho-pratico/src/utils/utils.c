// Standard library headers 
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>

// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "parser.h"
#include "string_pool.h"

int get_array_length(const char **array) {
    int size = 0;
    while(array[size] != NULL) size++;
    return size;
}

void g_free_all(gpointer first, ...) {
    va_list args;
    va_start(args, first);

    // Free the first pointer
    if (first != NULL) {
        g_free(first);
    }

    gpointer ptr = first;
    while ((ptr = va_arg(args, gpointer)) != NULL) {
        g_free(ptr);
    }

    va_end(args);
}

void g_hash_table_destroy_all(GHashTable *first, ...) {
    va_list args;
    va_start(args, first);

    if (first != NULL) {
        g_hash_table_destroy(first);
    }

    GHashTable *table = first;
    while ((table = va_arg(args, GHashTable *)) != NULL) {
        g_hash_table_destroy(table);
    }

    va_end(args);
}

char *to_lower_case(const char *str) {
    int len = strlen(str);
    char *lower_case_str = g_malloc(len + 1);

    for (int i = 0; i < len; i++) {
        lower_case_str[i] = tolower((unsigned char)str[i]);
    }
    lower_case_str[len] = '\0';

    return lower_case_str;
}

char *calculate_age(const char *birth_date) {
    int year, month, day;
    parse_date(birth_date, &year, &month, &day);

    int calculated_age = TD_YEAR - year;
    int calculated_month = TD_MONTH - month;
    int calculated_day = TD_DAY - day;
    if (calculated_month < 0 || (calculated_month == 0 && calculated_day < 0)) {
        calculated_age--;
    }

    return g_strdup_printf("%d", calculated_age);
}

int duration_to_seconds(const char *duration) {
    int hours, minutes, seconds;
    parse_time(duration, &hours, &minutes, &seconds);
    return hours * 3600 + minutes * 60 + seconds;
}

char *seconds_to_duration(int seconds) {
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int seconds_left = seconds % 60;
    return g_strdup_printf("%02d:%02d:%02d", hours, minutes, seconds_left);
}

char *get_year_from_date(const char *date) {
    int year, month, day;
    parse_date(date, &year, &month, &day);
    return g_strdup_printf("%04d", year);
}

char *get_hour_from_time(const char *time) {
    int hours, minutes, seconds;
    parse_time(time, &hours, &minutes, &seconds);
    return g_strdup_printf("%02d", hours);
}

char *adjust_date(const char *date) {
    // Parse date
    int year, month, day;
    parse_date(date, &year, &month, &day);

    // Convert to tm struct
    struct tm tm_date = {0};
    tm_date.tm_year = year - 1900; // tm_year is years since 1900
    tm_date.tm_mon = month - 1;   // tm_mon is 0-based
    tm_date.tm_mday = day;

    // Adjust to Sunday
    mktime(&tm_date); // Adjust the `tm_wday` field
    int days_to_sunday = tm_date.tm_wday; // tm_wday: 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    tm_date.tm_mday -= days_to_sunday;   // Move back to Sunday
    mktime(&tm_date); // Adjust again after adjustment

    // Convert back to string
    char *ajusted_date = g_strdup_printf(
        "%04d/%02d/%02d", 
        tm_date.tm_year + 1900, 
        tm_date.tm_mon + 1, 
        tm_date.tm_mday
    );

    return ajusted_date;
}

// Helper function to determine if a year is a leap year
int is_leap_year(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;
    }
    return 0;
}

// Helper function to get the number of days in a given month
int days_in_month(int year, int month) {
    int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days_in_months[month - 1];
}

char *get_next_week(const char *date) {
    char **date_parts = g_strsplit(date, "/", -1);
    int year = atoi(date_parts[0]);
    int month = atoi(date_parts[1]);
    int day = atoi(date_parts[2]);
    g_strfreev(date_parts);

    // Add 7 days to the current day
    day += 7;

    // Adjust month and year if the day exceeds the current month's days
    while (day > days_in_month(year, month)) {
        day -= days_in_month(year, month);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    // Allocate memory for the resulting date string
    char *next_date = g_strdup_printf("%04d/%02d/%02d", year, month, day);

    return next_date;
}
