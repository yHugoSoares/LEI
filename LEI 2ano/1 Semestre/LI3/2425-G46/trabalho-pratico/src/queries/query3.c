#include <stdio.h>

#include "database.h"
#include "repository_artist.h"
#include "repository_data.h"
#include "parser.h"
#include "utils.h"
#include "data_operations.h"
#include "output.h"

void query3(Database database, char *args, Output output, char *spacer) {
    char **tokens = g_strsplit(args, " ", 2);

    int min_age = atoi(tokens[0]);
    int max_age = atoi(tokens[1]);

    g_strfreev(tokens);

    GHashTable *genres_popularity_within_age_interval = get_genres_popularity_within_age_interval(database, min_age, max_age);

    GList *genres = g_hash_table_get_keys(genres_popularity_within_age_interval);
    GList *sorted_genres = g_list_sort_with_data(genres, (GCompareDataFunc)compare_keys_by_value, genres_popularity_within_age_interval);

    if (sorted_genres == NULL) {
        add_line_to_output(output, NULL, NULL);
    } else for (GList *iter = sorted_genres; iter != NULL; iter = iter->next) {
        char *genre = iter->data;
        int *popularity = g_hash_table_lookup(genres_popularity_within_age_interval, genre);
        char *popularity_str = g_strdup_printf("%d", *popularity);
        
        char *line[] = {genre, popularity_str, NULL};
        add_line_to_output(output, line, spacer);
        g_free(popularity_str);
    }

    g_list_free(sorted_genres);
    g_hash_table_destroy(genres_popularity_within_age_interval);
}
