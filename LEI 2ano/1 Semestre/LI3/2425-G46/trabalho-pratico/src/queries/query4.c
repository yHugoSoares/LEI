#include <stdio.h>

#include "database.h"
#include "repository_artist.h"
#include "repository_data.h"
#include "parser.h"
#include "utils.h"
#include "data_operations.h"
#include "output.h"


void query4(Database database, char *args, Output output, char *spacer) {

    char **tokens = g_strsplit(args, " ", 2);
    char *begin_date = NULL;
    char *end_date = NULL;

    if (tokens[0] != NULL) {
        begin_date = adjust_date(tokens[0]);
        end_date = adjust_date(tokens[1]);
    }
    g_strfreev(tokens);

    DataRepository data_repository = get_data_repository(database);
    ArtistRepository artist_repository = get_artist_repository(database);

    if (begin_date == NULL || end_date == NULL) {
        char *artist_id = get_top10_all_time_artist_id(data_repository);
        char *type = get_artist_type_by_id(artist_repository, artist_id);
        char *occurences = get_most_top10_occurences(data_repository);
        char *line[] = {artist_id, type, occurences, NULL};

        add_line_to_output(output, line, spacer);
        g_free_all(artist_id, type, occurences, NULL);
    } else {
        char **result = get_top10_artist_and_occurences(database, begin_date, end_date);
        
        if (result == NULL) {
            add_line_to_output(output, NULL, NULL);
        } else {
            char *type = get_artist_type_by_id(artist_repository, result[0]);
            char *line[] = {result[0], type, result[1], NULL};
            add_line_to_output(output, line, spacer);
            g_strfreev(result);
            g_free(type);
        }

        g_free_all(begin_date, end_date, NULL);
    }
}


















/* int compare_artists_by_top10_occurrences(void *a, void *b, void *user_data) {
    char *artist1_id = (char *)a;
    char *artist2_id = (char *)b;
    GHashTable *artists_by_top10_occurrences = (GHashTable *)user_data;
    int *occurrences1 = g_hash_table_lookup(artists_by_top10_occurrences, artist1_id);
    int *occurrences2 = g_hash_table_lookup(artists_by_top10_occurrences, artist2_id);
    int diff = *occurrences2 - *occurrences1;

    if (diff != 0)
        return diff;
    else 
        return strcmp(artist1_id, artist2_id);
}


void query4(Database database, char *args, char *output_file_path, char spacer) {
    char **tokens = g_strsplit(args, " ", 2);

    char *begin_date = NULL;
    char *end_date = NULL;

    if (tokens[0] != NULL) {
        begin_date = normalize_date(tokens[0]);
        end_date = normalize_date(tokens[1]);
    }
    g_strfreev(tokens);

    DataRepository data_repository = get_data_repository(database);
    ArtistRepository artist_repository = get_artist_repository(database);

    GHashTable *top10_artists_by_week = get_top10_artists_by_week(data_repository);
    GHashTable *top10_occurrences_by_artist_id = get_top10_occurrences_by_artist_id(data_repository);

    GHashTable *top10_occurences_by_artist_id_in_date_interval = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

    FILE *output_file = fopen(output_file_path, "w");

    if (begin_date == NULL || end_date == NULL) {
        GList *artist_ids = g_hash_table_get_keys(top10_occurrences_by_artist_id);
        GList *sorted_artist_ids = g_list_sort_with_data(artist_ids, (GCompareDataFunc)compare_artists_by_top10_occurrences, top10_occurrences_by_artist_id);
        
        char *artist_id = sorted_artist_ids->data;
        char *type = get_artist_type_from_repository(artist_repository, artist_id);
        int *occurrences = g_hash_table_lookup(top10_occurrences_by_artist_id, artist_id);
        fprintf(output_file, "%s%c%s%c%d\n", artist_id, spacer, type, spacer, *occurrences);
        g_free(type);
        g_list_free(sorted_artist_ids);
    } else {
        char *temp_date = begin_date;
        while (strcmp(temp_date, end_date) <= 0) {
            char *current_date = temp_date;

            GList *top10_artists = g_hash_table_lookup(top10_artists_by_week, current_date);
            for (GList *iter_top10_artists = top10_artists; iter_top10_artists != NULL; iter_top10_artists = iter_top10_artists->next) {
                char *artist_id = iter_top10_artists->data;
                int *occurrences = g_hash_table_lookup(top10_occurences_by_artist_id_in_date_interval, artist_id);
                if (occurrences == NULL) {
                    int *new_occurrences = g_malloc(sizeof(int));
                    *new_occurrences = 1;
                    g_hash_table_insert(top10_occurences_by_artist_id_in_date_interval, g_strdup(artist_id), new_occurrences);
                } else {
                    *occurrences += 1;
                }
            }

            temp_date = next_week(current_date);
            g_free(current_date);
        }

        GList *artist_ids = g_hash_table_get_keys(top10_occurences_by_artist_id_in_date_interval);
        GList *sorted_artist_ids = g_list_sort_with_data(artist_ids, (GCompareDataFunc)compare_artists_by_top10_occurrences, top10_occurences_by_artist_id_in_date_interval);

        if (sorted_artist_ids == NULL) {
            fputs("\n", output_file);
        } else {
            char *artist_id = sorted_artist_ids->data;
            char *type = get_artist_type_from_repository(artist_repository, artist_id);
            int *occurrences = g_hash_table_lookup(top10_occurences_by_artist_id_in_date_interval, artist_id);
            fprintf(output_file, "%s%c%s%c%d\n", artist_id, spacer, type, spacer, *occurrences);
            g_free(type);
            g_list_free(sorted_artist_ids);
        }
    }

    g_hash_table_destroy(top10_occurences_by_artist_id_in_date_interval);

    fclose(output_file);
}
 */










/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

// Project headers
#include "query4.h"
#include "database.h"
#include "utils.h"
#include "artist.h"
#include "repository_artist.h"

struct playback {
    char *artist_id; // ID of the artist
    int time; // Playback time in seconds
};

struct activity {
    char *date; // Date of the activity
    GList *playbacks; // List of Playback
};

// Function to compare artists by their total playback time
gint compare_artists(gconstpointer a, gconstpointer b) {
    const Artist *artist_a = (const Artist *)a;
    const Artist *artist_b = (const Artist *)b;
    return (*artist_b)->total_playback_time - (*artist_a)->total_playback_time;
}

// Function to find the artist with the most top 10 appearances
Artist find_top_artist(GHashTable *artists, GList *activities, const char *start_date, const char *end_date, int *max_count) {
    GHashTable *top10_count = g_hash_table_new(g_str_hash, g_str_equal);

    // Iterate through activities and calculate top 10 for each week
    for (GList *node = activities; node != NULL; node = node->next) {
        Activity activity = (Activity)node->data;
        // Filter by date range if specified
        if ((start_date && strcmp(activity->date, start_date) < 0) ||
            (end_date && strcmp(activity->date, end_date) > 0)) {
            continue;
        }

        // Calculate total playback time for each artist
        GHashTable *weekly_playback = g_hash_table_new(g_str_hash, g_str_equal);
        for (GList *a_node = activity->playbacks; a_node != NULL; a_node = a_node->next) {
            Playback playback = (Playback)a_node->data;
            Artist artist = g_hash_table_lookup(artists, playback->artist_id);
            if (artist) {
                int *total_time = g_hash_table_lookup(weekly_playback, artist->id);
                if (!total_time) {
                    total_time = g_new(int, 1);
                    *total_time = 0;
                    g_hash_table_insert(weekly_playback, artist->id, total_time);
                }
                *total_time += playback->time;
            }
        }

        // Get top 10 artists for the week
        GList *sorted_artists = g_hash_table_get_values(weekly_playback);
        sorted_artists = g_list_sort(sorted_artists, compare_artists);
        GList *top10 = g_list_copy_deep(g_list_first(sorted_artists), (GCopyFunc)g_strdup, NULL);
        top10 = g_list_truncate(top10, 10);

        // Count top 10 appearances
        for (GList *t_node = top10; t_node != NULL; t_node = t_node->next) {
            char *artist_id = (char *)t_node->data;
            int *count = g_hash_table_lookup(top10_count, artist_id);
            if (!count) {
                count = g_new(int, 1);
                *count = 0;
                g_hash_table_insert(top10_count, artist_id, count);
            }
            (*count)++;
        }

        g_list_free_full(top10, g_free);
        g_hash_table_destroy(weekly_playback);
    }

    // Find the artist with the most top 10 appearances
    Artist top_artist = NULL;
    *max_count = 0;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, top10_count);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *artist_id = (char *)key;
        int count = *(int *)value;
        if (count > *max_count || (count == *max_count && (!top_artist || strcmp(artist_id, top_artist->id) < 0))) {
            top_artist = g_hash_table_lookup(artists, artist_id);
            *max_count = count;
        }
    }

    g_hash_table_destroy(top10_count);
    return top_artist;
}

// Function to execute query 4
void query4(Database database, char *args, char *output_file_path, char spacer) {
    char **tokens = g_strsplit(args, " ", 2);
    const char *start_date = tokens[0];
    const char *end_date = tokens[1];

    g_strfreev(tokens);

    GHashTable *artists = get_artist_repository(database)->artists_by_id;
    GList *activities = get_activity_list(database);

    int max_count;
    Artist top_artist = find_top_artist(artists, activities, start_date, end_date, &max_count);

    FILE *output_file = fopen(output_file_path, "w");
    if (top_artist) {
        fprintf(output_file, "%s%c%s%c%d\n", top_artist->name, spacer, top_artist->type, spacer, max_count);
    } else {
        fprintf(output_file, "No top artist found.\n");
    }
    fclose(output_file);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <dataset_folder> <args> <output_file>\n", argv[0]);
        return 1;
    }

    const char *dataset_folder = argv[1];
    char *args = argv[2];
    const char *output_file_path = argv[3];

    Database database = load_database(dataset_folder);
    if (!database) {
        fprintf(stderr, "Failed to load database from %s\n", dataset_folder);
        return 1;
    }

    query4(database, args, output_file_path, ';');

    free_database(database);
    return 0;
} */