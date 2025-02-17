#include <string.h>
#include <stdio.h>

#include <glib.h>

char *remove_char(const char *str, char c) {

    if (str == NULL)
        return NULL;

    char str_cleaned[strlen(str)+1];

    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != c) {
            str_cleaned[j++] = str[i];
        }
        i++;
    }
    str_cleaned[j] = '\0';

    return g_strdup(str_cleaned);
}

void parse_date(const char *date, int *year, int *month, int *day) {
    sscanf(date, "%4d/%2d/%2d", year, month, day);
}

void parse_time(const char *time, int *hours, int *minutes, int *seconds) {
    sscanf(time, "%2d:%2d:%2d", hours, minutes, seconds);
}

char **parse_list(const char *list) {

    char list_without_brackets[strlen(list)];

    int i = 0, j = 0;
    while (list[i]) {
        if (list[i] != '[' && list[i] != ']' && list[i] != '\'') {
            list_without_brackets[j++] = list[i];
        }
        i++;
    }
    list_without_brackets[j] = '\0';

    char **tokens = g_strsplit(list_without_brackets, ", ", -1);

    return tokens;
}

void free_list(char **list) {
    g_strfreev(list);
}

char **parse_line(const char *line) {

    char line_cleaned[strlen(line)+1];

    int i = 0, j = 0;
    while (line[i]) {
        if (line[i] != '\"' && line[i] != '\n') {
            line_cleaned[j++] = line[i];
        }
        i++;
    }
    line_cleaned[j] = '\0';
    
    char **fields = g_strsplit(line_cleaned, ";", -1);

    return fields;
}

void free_fields(char **fields) {
    g_strfreev(fields);
}
