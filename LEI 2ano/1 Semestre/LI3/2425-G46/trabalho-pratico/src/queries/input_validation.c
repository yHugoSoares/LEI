#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <glib.h>

#include "defs.h"
#include "syntatic_validation.h"

int check_file_exists(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return 0;
    } else {
        fclose(file);
        return 1;
    }
}

int validate_directory(const char *directory) {

    char *files[] = FILES;
    char file_path[BUFFER_SIZE];
    int i = 0;

    while (files[i] != NULL) {
        snprintf(file_path, BUFFER_SIZE, "%s/%s", directory, files[i]);
        
        if (!check_file_exists(file_path)) {
            return 0;
        }
        i++;
    }
    return 1;
}

int validate_query1_input(char *input) {

    int len = strlen(input);

    if (len == 0 || len == 1) {
        return 0;
    }

    if (input[0] != 'A' && input[0] != 'U') {
        return 0;
    }

    for (int i = 1; i < len; i++) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }

    return 1;
}


int validate_query2_input(char *input) {

    int len = strlen(input);

    if (len == 0) {
        return 0;
    }

    char **tokens = g_strsplit(input, " ", 2);
    int token1_len = strlen(tokens[0]);

    for (int i = 0; i < token1_len; i++) {
        if (!isdigit(tokens[0][i])) {
            g_strfreev(tokens);
            return 0;
        }
    }

    if (tokens[1] != NULL) {
        int token2_len = strlen(tokens[1]);
        for (int i = 0; i < token2_len; i++) {
            if (i == 0 || i == token2_len - 1) {
                if (tokens[1][i] != '"') {
                    g_strfreev(tokens);
                    return 0;
                }
            }
        }
    }

    g_strfreev(tokens);

    return 1;
}

int validate_query3_input(char *input) {

    int len = strlen(input);

    if (len == 0) {
        return 0;
    }

    char **tokens = g_strsplit(input, " ", 2);

    if (tokens[0] == NULL || tokens[1] == NULL) {
        g_strfreev(tokens);
        return 0;
    }


    int token1_len = strlen(tokens[0]);
    for (int i = 0; i < token1_len; i++) {
        if (!isdigit(tokens[0][i])) {
            g_strfreev(tokens);
            return 0;
        }
    }

    int token2_len = strlen(tokens[1]);
    for (int i = 0; i < token2_len; i++) {
        if (!isdigit(tokens[1][i])) {
            g_strfreev(tokens);
            return 0;
        }
    }

    g_strfreev(tokens);
    return 1;

}

int validate_query4_input(char *input) {
    
    int len = strlen(input);

    if (len == 0) {
        return 1;
    }

    char **tokens = g_strsplit(input, " ", 2);

    if (tokens[0] == NULL || tokens[1] == NULL) {
        g_strfreev(tokens);
        return 0;
    }

    if (!validate_date(tokens[0]) || !validate_date(tokens[1])) {
        g_strfreev(tokens);
        return 0;
    }

    g_strfreev(tokens);
    return 1;
}

int validate_query5_input(char *input) {

    int len = strlen(input);

    if (len == 0) {
        return 0;
    }

    char **tokens = g_strsplit(input, " ", 2);

    if (tokens[0] == NULL || tokens[1] == NULL) {
        g_strfreev(tokens);
        return 0;
    }

    int token1_len = strlen(tokens[0]);
    for (int i = 0; i < token1_len; i++) {
        if (i == 0) {
            if (tokens[0][i] != 'U') {
                g_strfreev(tokens);
                return 0;
            }
        } else if (!isdigit(tokens[0][i])) {
            g_strfreev(tokens);
            return 0;
        }
    }

    int token2_len = strlen(tokens[1]);
    for (int i = 0; i < token2_len; i++) {
        if (!isdigit(tokens[1][i])) {
            g_strfreev(tokens);
            return 0;
        }
    }

    g_strfreev(tokens);
    return 1;
}


int validate_query6_input(char *input) {

    int len = strlen(input);

    if (len == 0) {
        return 0;
    }

    char **tokens = g_strsplit(input, " ", 3);

    if (tokens[0] == NULL || tokens[1] == NULL) {
        g_strfreev(tokens);
        return 0;
    }

    int token1_len = strlen(tokens[0]);
    for (int i = 0; i < token1_len; i++) {
        if (i == 0) {
            if (tokens[0][i] != 'U') {
                g_strfreev(tokens);
                return 0;
            }
        } else if (!isdigit(tokens[0][i])) {
            g_strfreev(tokens);
            return 0;
        }
    }

    int token2_len = strlen(tokens[1]);

    if (token2_len != 4) {
        g_strfreev(tokens);
        return 0;
    }

    for (int i = 0; i < token2_len; i++) {
        if (!isdigit(tokens[1][i])) {
            g_strfreev(tokens);
            return 0;
        }
    }

    if (tokens[2] == NULL) {
        g_strfreev(tokens);
        return 1;
    }

    int token3_len = strlen(tokens[2]);

    for (int i = 0; i < token3_len; i++) {
        if (!isdigit(tokens[2][i])) {
            g_strfreev(tokens);
            return 0;
        }
    }

    g_strfreev(tokens);
    return 1;
}


int validate_input(int query, char *input) {

    switch (query) {
    case 1:
        return validate_query1_input(input);
        break;
    case 2:
        return validate_query2_input(input);
        break;
    case 3:
        return validate_query3_input(input);
        break;
    case 4:
        return validate_query4_input(input);
        break;
    case 5:
        return validate_query5_input(input);
        break;
    case 6:
        return validate_query6_input(input);
        break;
    default:
        return 0;
    }

    return 0;
}