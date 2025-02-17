// Standard library headers
#include <stdlib.h>    
#include <string.h>   
#include <ctype.h>     

// Project headers
#include "defs.h"
#include "parser.h"
#include "utils.h"


int validate_date(const char *date) {

    if (strlen(date) != 10) return 0; 

    if (date[4] != '/' || date[7] != '/') return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return 0;
    }

    int year, month, day;
    parse_date(date, &year, &month, &day);

    if (year < 1 || year > 2024) return 0;

    if (month < 1 || month > 12) return 0;

    if (day < 1 || day > 31) return 0;

    if (year > TD_YEAR ||
       (year == TD_YEAR && month > TD_MONTH) ||
       (year == TD_YEAR && month == TD_MONTH && day > TD_DAY)) return 0;

    return 1;
}


int validate_duration(const char *duration) {

    if (strlen(duration) != 8) return 0;

    if (duration[2] != ':' || duration[5] != ':') return 0;

    for (int i = 0; i < 8; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(duration[i])) return 0;
    }

    int hours, minutes, seconds;
    parse_time(duration, &hours, &minutes, &seconds);

    if (hours < 0 || hours > 99) return 0;

    if (minutes < 0 || minutes > 59) return 0;

    if (seconds < 0 || seconds > 59) return 0;

    return 1;
}


int validate_email(const char *email) {
    int at_index = -1;
    int dot_index = -1;
    int length = strlen(email);

    for (int i = 0; i < length; i++) {

        if (i == 0 || i == length - 1)
            if (email[i] == '@' || email[i] == '.') return 0;

        if (email[i] == '@') {
            if (at_index != -1 || i == 0 || i == length - 1) return 0;
            at_index = i;
        } else if (email[i] == '.') {
            if (dot_index != -1 || i == 0 || i == length - 1) return 0;
            dot_index = i;
        } else if (!isalnum(email[i]) || (isalpha(email[i]) && !islower(email[i]))) return 0;
    }

    if (at_index == -1 || dot_index == -1 || dot_index < at_index || (length - dot_index - 1 < 2 || length - dot_index - 1 > 3)) return 0;

    return 1;
}


int validate_subscription(const char *subscription) {

    char *lower_case_subscription = to_lower_case(subscription);
    char *types[] = {"normal", "premium", NULL};

    for (int i = 0; types[i] != NULL; i++) {
        if (strcmp(subscription, types[i]) == 0) {
            g_free(lower_case_subscription);
            return 1;
        }
    }

    g_free(lower_case_subscription);

    return 0;
}

int validate_platform(const char *platform) {

    char *lower_case_platform = to_lower_case(platform);
    char *platforms[] = {"mobile", "desktop", NULL};

    for (int i = 0; platforms[i] != NULL; i++) {
        if (strcmp(platform, platforms[i]) == 0) {
            g_free(lower_case_platform);
            return 1;
        }
    }

    g_free(lower_case_platform);

    return 0;
}

int validate_list(const char *list) {

    if (list[0] != '[' || list[strlen(list) - 1] != ']') return 0;

    return 1;
}
