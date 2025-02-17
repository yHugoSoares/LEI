#include "data_container.h"
#include "database.h"
#include "repository_data.h"
#include "repository_history.h"
#include "data_operations.h"

void increase_history_artists_listening_time_and_num_of_streams(DataContainer container, const char *date, const char *history_id) {
    Database database = get_data(container);
    StringPool string_pool = get_string_pool(database);
    DataRepository data_repository = get_data_repository(database);
    HistoryRepository history_repository = get_history_repository(database);
    MusicRepository music_repository = get_music_repository(database);

    int elapsed_time = get_history_elapsed_time_by_id(history_repository, history_id);
    char *music_id = get_history_music_id_by_id(history_repository, history_id);

    GList *artist_ids = get_music_artist_ids_by_id(music_repository, music_id);
    for (GList *artist_id = artist_ids; artist_id != NULL; artist_id = artist_id->next) {
        increase_value_by_key(container, artist_id->data, elapsed_time);
        increment_num_of_streams_by_artist_id(string_pool, data_repository, artist_id->data);
    }
    g_free(music_id);
    g_list_free_full(artist_ids, (GDestroyNotify)g_free);
}

void calculate_week_top10_artists_and_num_of_streams(DataContainer container, const char *date) {
    GHashTable *listening_time_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    set_hashtable(container, listening_time_by_artist_id);

    Database database = get_data(container);
    HistoryRepository history_repository = get_history_repository(database);
    foreach_history_id_from_date(history_repository, date, (IterDataFunc)increase_history_artists_listening_time_and_num_of_streams, container);

    GList *artist_ids = g_hash_table_get_keys(listening_time_by_artist_id);
    GList *artists_ids_sorted_by_listening_time = g_list_sort_with_data(artist_ids,
                                                                        (GCompareDataFunc)compare_keys_by_value,
                                                                        listening_time_by_artist_id);

    StringPool string_pool = get_string_pool(database);
    DataRepository data_repository= get_data_repository(database);
    int i = 0;
    for (GList *iter = artists_ids_sorted_by_listening_time; i < 10 && iter != NULL; iter = iter->next) {
        char *artist_id = iter->data;
        add_artist_id_by_week(string_pool, data_repository, date, artist_id);
        i++;
    }

    g_list_free(artists_ids_sorted_by_listening_time);
    g_hash_table_destroy(listening_time_by_artist_id);
}

// Query 4 (part 2) and Query 1
void calculate_top10_artists_by_week_and_num_of_streams(Database database) {
    DataContainer container = init_data_container(0, 0, database, NULL, NULL);
    HistoryRepository history_repository = get_history_repository(database);
    foreach_history_adjusted_date(history_repository, (IterDataFunc)calculate_week_top10_artists_and_num_of_streams, container);
    destroy_data_container(container);
}

void increment_artist_id_top10_occurences(DataContainer container, const char *date, const char *artist_id) {
    increment_value_by_key(container, artist_id);
}

// Query 4 (part 1)
void calculate_top10_all_time_artist(Database database) {
    GHashTable *top10_occurences_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    DataContainer container = init_data_container(0, 0, database, NULL, top10_occurences_by_artist_id);

    DataRepository data_repository = get_data_repository(database);
    foreach_date_artist_ids(data_repository, (IterDataFunc)increment_artist_id_top10_occurences, container);
    destroy_data_container(container);

    GList *artist_ids = g_hash_table_get_keys(top10_occurences_by_artist_id);
    GList *sorted_artist_ids = g_list_sort_with_data(artist_ids, (GCompareDataFunc)compare_keys_by_value, top10_occurences_by_artist_id);

    StringPool string_pool = get_string_pool(database);
    char *artist_id = sorted_artist_ids->data;
    set_top10_all_time_artist_id(string_pool, data_repository, artist_id);
    int *most_top10_occurences = g_hash_table_lookup(top10_occurences_by_artist_id, artist_id);
    set_most_top10_occurences(data_repository, *most_top10_occurences);

    g_list_free(sorted_artist_ids);
    g_hash_table_destroy(top10_occurences_by_artist_id);
}

void apply_to_history_id(DataContainer container, const char *user_id, const char *history_id) {

    Database database = get_data(container);
    DataRepository data_repository = get_data_repository(database);
    HistoryRepository history_repository = get_history_repository(database);
    MusicRepository music_repository = get_music_repository(database);

    char *music_id = get_history_music_id_by_id(history_repository, history_id);
    char *genre = get_music_genre_by_id(music_repository, music_id);

    int user_idx = get_i(container);
    int genre_idx = get_genre_index(data_repository, genre);

    increment_user_genre_preference(data_repository, user_idx, genre_idx);

    g_free(music_id);
    g_free(genre);
}

// Query 5
void calculate_users_genres_preferences(Database database) {

    DataRepository data_repository = get_data_repository(database);
    UserRepository user_repository = get_user_repository(database);
    MusicRepository music_repository = get_music_repository(database);

    char **user_ids = get_user_ids(user_repository);
    char **genres = get_genres(music_repository);
    int num_of_users = get_num_of_users(user_repository);
    int num_of_genres = get_num_of_genres(music_repository);

    init_users_genres_preferences(data_repository,
                                  user_ids,
                                  genres,
                                  num_of_users,
                                  num_of_genres);

    DataContainer container = init_data_container(0, 0, database, NULL, NULL);

    for (int i = 0; i < num_of_users; i++) {
        set_i(container, i);
        char *user_id = user_ids[i];
        HistoryRepository history_repository = get_history_repository(database);
        foreach_history_id_from_user_id(history_repository, user_id, (IterDataFunc)apply_to_history_id, container);
    }

    destroy_data_container(container);
}

void preprocess_histories(Database database) {
    calculate_top10_artists_by_week_and_num_of_streams(database);
    calculate_top10_all_time_artist(database);
    calculate_users_genres_preferences(database);
}
