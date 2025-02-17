#include <glib.h>
#include <stdio.h>

#include "defs.h"
#include "parser.h"

// Struct to represent the string pool
typedef struct string_pool {
    int size;
    GHashTable *table;
} StringPoolStruct, *StringPool;

// Create a new string pool
StringPool init_string_pool() {
    StringPool pool = g_new(StringPoolStruct, 1);
    pool->size = 0;
    pool->table = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    return pool;
}

// Get the size of the string pool
int get_string_pool_size(StringPool string_pool) {
    return string_pool->size;
}

// Add and retrieve a string from the pool
const char *add_string(StringPool string_pool, const char *str) {
    // Check if the string already exists in the pool
    char *existingString = g_hash_table_lookup(string_pool->table, str);
    if (existingString) {
        return existingString;
    }
    // Add the string to the pool
    char *newString = g_strdup(str);
    g_hash_table_insert(string_pool->table, newString, newString);
    string_pool->size++;
    return newString;
}

// Get a linked list of strings from the pool
const char **add_list(StringPool string_pool, const char *str) {
    // Parse the list and determine its length
    char **tokens = parse_list(str);
    int len = g_strv_length(tokens);

    // Create list and add tokens to the pool
    const char **list = g_malloc((len + 1) * sizeof(char *));
    int i;
    for (i = 0; i < len; i++) {
        list[i] = add_string(string_pool, tokens[i]);
    }
    list[i] = NULL;
    // Free the tokens
    free_list(tokens);

    return list;
}

// Free the string pool
void free_string_pool(StringPool string_pool) {
    g_hash_table_destroy(string_pool->table);
    g_free(string_pool);
}