#include <stdio.h>

#include "database.h"
#include "repository_artist.h"
#include "repository_history.h"
#include "repository_data.h"
#include "parser.h"
#include "utils.h"
#include "data_container.h"
#include "data_operations.h"
#include "output.h"

void calculate_history_metrics(DataContainer container, const char *user_id, const char *history_id) {

    Database database = get_data(container);
    HistoryRepository history_repository = get_history_repository(database);
    
    char *history_year = get_history_year_by_id(history_repository, history_id);
    int stats_year = get_i(container);

    if (atoi(history_year) != stats_year) {
        g_free(history_year);
        return;
    } else {
        g_free(history_year);
    }

    MusicRepository music_repository = get_music_repository(database);

    char *music_id = get_history_music_id_by_id(history_repository, history_id);
    GList *artist_ids = get_music_artist_ids_by_id(music_repository, music_id);
    char *genre = get_music_genre_by_id(music_repository, music_id);
    char *album = get_music_album_id_by_id(music_repository, music_id);
    char *date = get_history_date_by_id(history_repository, history_id);
    char *hour = get_history_hour_by_id(history_repository, history_id);
    int elapsed_time = get_history_elapsed_time_by_id(history_repository, history_id);

    double listening_time = get_d(container);
    listening_time += elapsed_time;
    set_d(container, listening_time);

    GHashTable **hashtables = (GHashTable **)get_data_array(container);
    GHashTable *listening_time_by_genre = hashtables[0];
    GHashTable *listening_time_by_album = hashtables[1];
    GHashTable *listening_time_by_hour = hashtables[2];
    GHashTable *listening_time_by_artist_id = hashtables[3];
    GHashTable *listened_musics = hashtables[4];
    GHashTable *num_of_listened_musics_by_date = hashtables[5];
    GHashTable *num_of_listened_musics_by_artist_id = hashtables[6];

    set_hashtable(container, listening_time_by_genre);
    increase_value_by_key(container, genre, elapsed_time);
    set_hashtable(container, listening_time_by_album);
    increase_value_by_key(container, album, elapsed_time);
    set_hashtable(container, listening_time_by_hour);
    increase_value_by_key(container, hour, elapsed_time);

    set_hashtable(container, listening_time_by_artist_id);
    for (GList *artist_id = artist_ids; artist_id != NULL; artist_id = artist_id->next) {
        increase_value_by_key(container, artist_id->data, elapsed_time);
    }

    if (!g_hash_table_contains(listened_musics, music_id)) {
        g_hash_table_insert(listened_musics, music_id, music_id);
        set_hashtable(container, num_of_listened_musics_by_date);
        increment_value_by_key(container, date);
        set_hashtable(container, num_of_listened_musics_by_artist_id);
        for (GList *iter_artist_id = artist_ids; iter_artist_id != NULL; iter_artist_id = iter_artist_id->next) {
            char *artist_id = iter_artist_id->data;
            increment_value_by_key(container, artist_id);
        }
    }

    g_list_free_full(artist_ids, g_free);
    g_free_all(music_id, genre, album, date, hour, NULL);
}


void query6(Database database, char *args, Output output, char *spacer) {

    char **tokens = g_strsplit(args, " ", 3);

    char *user_id = g_strdup(tokens[0]);
    int year = atoi(tokens[1]);
    int n = 0;
    if (tokens[2] != NULL) {
        n = atoi(tokens[2]);
    }
    g_strfreev(tokens);

    GHashTable *listening_time_by_genre = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    GHashTable *listening_time_by_album = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    GHashTable *listening_time_by_hour = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    GHashTable *listening_time_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    GHashTable *listened_musics = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    GHashTable *num_of_listened_musics_by_date = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    GHashTable *num_of_listened_musics_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);


    GHashTable *hashtables[] = {listening_time_by_genre,
                                listening_time_by_album,
                                listening_time_by_hour,
                                listening_time_by_artist_id,
                                listened_musics,
                                num_of_listened_musics_by_date,
                                num_of_listened_musics_by_artist_id};


    DataContainer data_container = init_data_container(year, 0, database, (void **)hashtables, NULL);

    HistoryRepository history_repository = get_history_repository(database);
    foreach_history_id_from_user_id(history_repository, user_id, (IterDataFunc)calculate_history_metrics, data_container);
    g_free(user_id);

    if (get_d(data_container) == 0) {
        add_line_to_output(output, NULL, NULL);
        destroy_data_container(data_container);
        g_hash_table_destroy_all(listening_time_by_genre,
                         listening_time_by_album,
                         listening_time_by_hour,
                         listening_time_by_artist_id,
                         listened_musics,
                         num_of_listened_musics_by_date,
                         num_of_listened_musics_by_artist_id,
                         NULL);
        return;
    }

    char *listening_time = seconds_to_duration(get_d(data_container));
    char *musics_count = g_strdup_printf("%d", g_hash_table_size(listened_musics));
    char *favorite_genre = get_key_by_highest_value(listening_time_by_genre, 0);
    char *favorite_album = get_key_by_highest_value(listening_time_by_album, 0);
    char *peak_activity_hour = get_key_by_highest_value(listening_time_by_hour, 0);
    char *peak_activity_day = get_key_by_highest_value(num_of_listened_musics_by_date, 1);
    char *favorite_artist_id = get_key_by_highest_value(listening_time_by_artist_id, 0);
    char *line[] = {listening_time, musics_count, favorite_artist_id, peak_activity_day, favorite_genre, favorite_album, peak_activity_hour, NULL};

    add_line_to_output(output, line, spacer);

    destroy_data_container(data_container);
    g_free_all(listening_time, musics_count, favorite_genre, favorite_album, peak_activity_hour, peak_activity_day, favorite_artist_id, NULL);

    GList *artist_ids = g_hash_table_get_keys(listening_time_by_artist_id);
    GList *artist_ids_sorted = g_list_sort_with_data(artist_ids, (GCompareDataFunc)compare_keys_by_value, listening_time_by_artist_id);

    int i = 0;
    for (GList *iter = artist_ids_sorted; i < n && iter != NULL; iter = iter->next) {
        char *artist_id = iter->data;
        int *artist_musics_count_int = g_hash_table_lookup(num_of_listened_musics_by_artist_id, artist_id);
        int *artist_listening_time = g_hash_table_lookup(listening_time_by_artist_id, artist_id);
        char *artist_musics_count = g_strdup_printf("%d", *artist_musics_count_int);
        char *duration = seconds_to_duration(*artist_listening_time);

        char *artist_line[] = {artist_id, artist_musics_count, duration, NULL};
        add_line_to_output(output, artist_line, spacer);

        g_free_all(artist_musics_count, duration, NULL);
        i++;
    }

    g_list_free(artist_ids_sorted);
    g_hash_table_destroy_all(listening_time_by_genre,
                             listening_time_by_album,
                             listening_time_by_hour,
                             listening_time_by_artist_id,
                             listened_musics,
                             num_of_listened_musics_by_date,
                             num_of_listened_musics_by_artist_id,
                             NULL);
}

/* 
void increase_music_count(GHashTable *hashtable, char *category){
    int *current_value = g_hash_table_lookup(hashtable, category);
        if (current_value == NULL) {
            int *new_value = g_malloc(sizeof(int));
            *new_value = 1;
            g_hash_table_insert(hashtable, g_strdup(category), new_value);
        } else {
            (*current_value)++;
        }
}

void add_listening_time(GHashTable *hashtable, char *category, int listening_time){
    int *current_value = g_hash_table_lookup(hashtable, category);
        if (current_value == NULL) {
            int *new_value = g_malloc(sizeof(int));
            *new_value = listening_time;
            g_hash_table_insert(hashtable, g_strdup(category), new_value);
        } else {
            *current_value += listening_time;
        }
}

int compare_artist_ids(void *a, void *b, void *user_data) {
    char *artist_id1 = (char *)a;
    char *artist_id2 = (char *)b;
    GHashTable *listening_time_by_artist_id = (GHashTable *)user_data;

    int *listening_time1 = g_hash_table_lookup(listening_time_by_artist_id, artist_id1);
    int *listening_time2 = g_hash_table_lookup(listening_time_by_artist_id, artist_id2);
    int diff = *listening_time2 - *listening_time1;

    if (diff != 0) {
        return diff;
    } else {
        return strcmp(artist_id1, artist_id2);
    }

}


void query6(Database database, char *args, char *output_file_path, char spacer) {

    MusicRepository music_repository = get_music_repository(database);

    char **tokens = g_strsplit(args, " ", 3);

    char *user_id = tokens[0];
    int year = atoi(tokens[1]);
    int n = 0;
    if (tokens[2] != NULL) {
        n = atoi(tokens[2]);
    }

    int total_listening_time = 0;
    int musics_count = 0; // distinct musics
    char *favorite_artist_id = NULL;
    char *peak_activity_day = NULL;
    char *favorite_genre = NULL;
    char *favorite_album = NULL;
    char *peak_activity_hour = NULL;
    
    GHashTable *listened_musics = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    GHashTable *num_of_listened_musics_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    GHashTable *num_of_listened_musics_by_date = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

    GHashTable *listening_time_by_genre = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    GHashTable *listening_time_by_album = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    GHashTable *listening_time_by_hour = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    GHashTable *listening_time_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

    HistoryRepository history_repository = get_history_repository(database);
    GList* user_history = get_user_history_from_repository(history_repository, user_id);
    for(GList *iter_user_history = user_history; iter_user_history != NULL; iter_user_history = iter_user_history->next) {

        History history = iter_user_history->data;
        char *history_year = get_history_year(history);

        if (atoi(history_year) == year) {
            // num_of_listened_musics_by_date
            char *music_id = get_history_music_id(history);
            GList *artist_ids = get_music_artist_ids_from_repository(music_repository, music_id);
            char *genre = get_music_genre_from_repository(music_repository, music_id);
            char *album = get_music_album_from_repository(music_repository, music_id);
            char *date = get_history_date(history);
            char *hour = get_history_hour(history);
            char *duration = get_history_duration(history);

            int listening_time = duration_to_seconds(duration);
            total_listening_time += listening_time;

            add_listening_time(listening_time_by_genre, genre, listening_time);
            add_listening_time(listening_time_by_album, album, listening_time);
            add_listening_time(listening_time_by_hour, hour, listening_time);

            for (GList *iter_artist_id = artist_ids; iter_artist_id != NULL; iter_artist_id = iter_artist_id->next) {
                char *artist_id = iter_artist_id->data;
                add_listening_time(listening_time_by_artist_id, artist_id, listening_time);
            }

            if (!g_hash_table_contains(listened_musics, music_id)) {
                g_hash_table_insert(listened_musics, music_id, music_id);
                musics_count++;
                increase_music_count(num_of_listened_musics_by_date, date);
                for (GList *iter_artist_id = artist_ids; iter_artist_id != NULL; iter_artist_id = iter_artist_id->next) {
                    char *artist_id = iter_artist_id->data;
                    increase_music_count(num_of_listened_musics_by_artist_id, artist_id);
                }
            }

            g_list_free_full(artist_ids, g_free);
            g_free(genre);
            g_free(album);
            g_free(date);
            g_free(hour);
            g_free(duration);
        }

        g_free(history_year);
    }

    if (musics_count == 0) {
        FILE *output_file = fopen(output_file_path, "w");
        fputs("\n", output_file);
        fclose(output_file);
        g_strfreev(tokens);
        g_hash_table_destroy(listening_time_by_genre);
        g_hash_table_destroy(listening_time_by_album);
        g_hash_table_destroy(listening_time_by_hour);
        g_hash_table_destroy(listening_time_by_artist_id);
        g_hash_table_destroy(listened_musics);
        g_hash_table_destroy(num_of_listened_musics_by_artist_id);
        g_hash_table_destroy(num_of_listened_musics_by_date);
        return;
    }

    char *total_listening_duration = seconds_to_duration(total_listening_time);

    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, listening_time_by_genre);
    int favorite_genre_listening_time = -1;
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *genre = key;
        int *listening_time = value;
        if (*listening_time > favorite_genre_listening_time) {
            favorite_genre_listening_time = *listening_time;
            favorite_genre = genre;
        } else if (*listening_time == favorite_genre_listening_time && strcmp(genre, favorite_genre) < 0) {
            favorite_genre_listening_time = *listening_time;
            favorite_genre = genre;
        }
    }

    g_hash_table_iter_init(&iter, listening_time_by_album);
    int favorite_album_listening_time = -1;
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *album = key;
        int *listening_time = value;
        if (*listening_time > favorite_album_listening_time) {
            favorite_album_listening_time = *listening_time;
            favorite_album = album;
        } else if (*listening_time == favorite_album_listening_time && strcmp(album, favorite_album) < 0) {
            favorite_album_listening_time = *listening_time;
            favorite_album = album;
        }
    }

    g_hash_table_iter_init(&iter, num_of_listened_musics_by_date);
    int peak_activity_day_listening_time = -1;
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *date = key;
        int *listening_time = value;
        if (*listening_time > peak_activity_day_listening_time) {
            peak_activity_day_listening_time = *listening_time;
            peak_activity_day = date;
        } else if (*listening_time == peak_activity_day_listening_time && strcmp(date, peak_activity_day) > 0) {
            peak_activity_day_listening_time = *listening_time;
            peak_activity_day = date;
        }
    }

    g_hash_table_iter_init(&iter, listening_time_by_hour);
    int peak_activity_hour_listening_time = -1;
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *hour = key;
        int *listening_time = value;
        if (*listening_time > peak_activity_hour_listening_time) {
            peak_activity_hour_listening_time = *listening_time;
            peak_activity_hour = hour;
        } else if (*listening_time == peak_activity_hour_listening_time && strcmp(hour, peak_activity_hour) < 0) {
            peak_activity_hour_listening_time = *listening_time;
            peak_activity_hour = hour;
        }
    }

    g_hash_table_iter_init(&iter, listening_time_by_artist_id);
    int favorite_artist_id_listening_time = -1;
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *artist_id = key;
        int *listening_time = value;
        if (*listening_time > favorite_artist_id_listening_time) {
            favorite_artist_id_listening_time = *listening_time;
            favorite_artist_id = artist_id;
        } else if (*listening_time == favorite_artist_id_listening_time && strcmp(artist_id, favorite_artist_id) < 0) {
            favorite_artist_id_listening_time = *listening_time;
            favorite_artist_id = artist_id;
        }
    }

    FILE *output_file = fopen(output_file_path, "w");

    fprintf(output_file,"%s%c%d%c%s%c%s%c%s%c%s%c%s\n", total_listening_duration, spacer,
                                                        musics_count, spacer,
                                                        favorite_artist_id, spacer,
                                                        peak_activity_day, spacer,
                                                        favorite_genre, spacer,
                                                        favorite_album, spacer,
                                                        peak_activity_hour);

    fclose(output_file);

    GList *artist_ids = g_hash_table_get_keys(listening_time_by_artist_id);
    GList *artist_ids_sorted = g_list_sort_with_data(artist_ids, (GCompareDataFunc)compare_artist_ids, listening_time_by_artist_id);

    output_file = fopen(output_file_path, "a");

    int i = 0;
    for (GList *iter = artist_ids_sorted; i < n && iter != NULL; iter = iter->next) {
        char *artist_id = iter->data;
        int *musics_count = g_hash_table_lookup(num_of_listened_musics_by_artist_id, artist_id);
        int *listening_time = g_hash_table_lookup(listening_time_by_artist_id, artist_id);
        char *listening_duration = seconds_to_duration(*listening_time);
        fprintf(output_file, "%s%c%d%c%s\n", artist_id, spacer, *musics_count, spacer, listening_duration);
        g_free(listening_duration);
        i++;
    }

    fclose(output_file);

    g_list_free(artist_ids_sorted);

    g_strfreev(tokens);
    g_free(total_listening_duration);
    g_hash_table_destroy(listening_time_by_genre);
    g_hash_table_destroy(listening_time_by_album);
    g_hash_table_destroy(listening_time_by_hour);
    g_hash_table_destroy(listening_time_by_artist_id);
    g_hash_table_destroy(listened_musics);
    g_hash_table_destroy(num_of_listened_musics_by_artist_id);
    g_hash_table_destroy(num_of_listened_musics_by_date);

}


 */