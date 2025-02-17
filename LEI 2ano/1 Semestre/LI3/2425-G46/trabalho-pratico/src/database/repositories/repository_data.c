// Standard library headers   
#include <stdlib.h>
#include <stdio.h>

// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "utils.h"
#include "data_container.h"
#include "string_pool.h"
#include "recomendador.h"

typedef struct data_repository {
    // Query 1
    GHashTable *num_of_streams_by_artist_id;
    // Query 2
    GHashTable *discography_size_by_artist_id;
    GHashTable *country_by_artist_id;
    GList *artist_ids_sorted_by_discography_size;
    // Query 3
    GHashTable *genres_popularity_by_age;
    // Query 4
    GHashTable *top10_artists_by_week;
    const char *top10_all_time_artist_id;
    int most_top10_occurences;
    // Query 5
    int **users_genres_preferences;
    char **user_ids;
    char **genres;
    int num_of_users;
    int num_of_genres;
    GHashTable *genres_idx;
} *DataRepository;

DataRepository init_data_repository() {
    DataRepository data_repository = g_new(struct data_repository, 1);

    data_repository->num_of_streams_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);

    data_repository->discography_size_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    data_repository->country_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    data_repository->artist_ids_sorted_by_discography_size = NULL;

    data_repository->genres_popularity_by_age = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

    data_repository->top10_artists_by_week = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    data_repository->top10_all_time_artist_id = NULL;
    data_repository->most_top10_occurences = 0;

    data_repository->users_genres_preferences = NULL;
    data_repository->user_ids = NULL;
    data_repository->genres = NULL;
    data_repository->num_of_users = 0;
    data_repository->num_of_genres = 0;
    data_repository->genres_idx = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);

    return data_repository;
}

void free_data_repository(DataRepository data_repository) {
    g_hash_table_destroy(data_repository->num_of_streams_by_artist_id);

    g_hash_table_destroy(data_repository->discography_size_by_artist_id);
    g_hash_table_destroy(data_repository->country_by_artist_id);
    g_list_free(data_repository->artist_ids_sorted_by_discography_size);

    GList *values = g_hash_table_get_values(data_repository->genres_popularity_by_age);
    g_list_free_full(values, (GDestroyNotify)g_hash_table_destroy);
    g_hash_table_destroy(data_repository->genres_popularity_by_age);

    values = g_hash_table_get_values(data_repository->top10_artists_by_week);
    g_list_free_full(values, (GDestroyNotify)g_list_free);
    g_hash_table_destroy(data_repository->top10_artists_by_week);

    for (int i = 0; i < data_repository->num_of_users; i++) {
        g_free(data_repository->users_genres_preferences[i]);
    }
    g_free(data_repository->users_genres_preferences);
    g_strfreev(data_repository->user_ids);
    g_strfreev(data_repository->genres);
    g_hash_table_destroy(data_repository->genres_idx);

    g_free(data_repository);
}

void increment_num_of_streams_by_artist_id(StringPool string_pool, DataRepository data_repository, const char *artist_id) {
    int *num_of_streams = g_hash_table_lookup(data_repository->num_of_streams_by_artist_id, artist_id);

    if (num_of_streams == NULL) {
        num_of_streams = g_malloc(sizeof(int));
        *num_of_streams = 1;
        g_hash_table_insert(data_repository->num_of_streams_by_artist_id, (gpointer)add_string(string_pool, artist_id), num_of_streams);
    } else {
        *num_of_streams += 1;
    }
}

int get_artist_num_of_streams_by_id(DataRepository data_repository, const char *artist_id) {
    int *num_of_streams = g_hash_table_lookup(data_repository->num_of_streams_by_artist_id, artist_id);
    return num_of_streams == NULL ? 0 : *num_of_streams;
}


void increase_discography_size_by_artist_id(StringPool string_pool, DataRepository data_repository, const char *artist_id, int increase) {
    int *discography_size = g_hash_table_lookup(data_repository->discography_size_by_artist_id, artist_id);

    if (discography_size == NULL) {
        discography_size = g_malloc(sizeof(int));
        *discography_size = increase;
        g_hash_table_insert(data_repository->discography_size_by_artist_id, (gpointer)add_string(string_pool, artist_id), discography_size);
    } else {
        *discography_size += increase;
    }
}

void make_sorted_artist_list_from_discography_size_hashtable(DataRepository data_repository, GCompareDataFunc compare_keys_by_value) {
    GList *artist_ids = g_hash_table_get_keys(data_repository->discography_size_by_artist_id);
    GList *sorted_artist_ids = g_list_sort_with_data(artist_ids, compare_keys_by_value, data_repository->discography_size_by_artist_id);
    data_repository->artist_ids_sorted_by_discography_size = sorted_artist_ids;
}

void add_country_by_artist_id(StringPool string_pool, DataRepository data_repository, const char *artist_id, const char *country) {
    g_hash_table_insert(data_repository->country_by_artist_id, (gpointer)add_string(string_pool, artist_id), (gpointer)add_string(string_pool, country));
}

char **get_n_largest_artists_by_discography_size(DataRepository data_repository, int n, char *country) {
    char **n_largest_artists = g_malloc((n + 1) * sizeof(char *));
    int i = 0;
    GList *list_iter = data_repository->artist_ids_sorted_by_discography_size;
    while (i < n && list_iter != NULL) {
        char *artist_id = list_iter->data;
        char *artist_country = g_hash_table_lookup(data_repository->country_by_artist_id, artist_id);
        if (country == NULL || strcmp(artist_country, country) == 0) {
            n_largest_artists[i++] = g_strdup(artist_id);
        }
        list_iter = list_iter->next;
    }
    n_largest_artists[i] = NULL;
    return n_largest_artists;
}

char *get_artist_discography_duration_by_id(DataRepository data_repository, const char *artist_id) {
    int *discography_size = g_hash_table_lookup(data_repository->discography_size_by_artist_id, artist_id);
    return discography_size == NULL ? NULL : seconds_to_duration(*discography_size);
}

void update_artist_ids_sorted_by_discography_size(DataRepository data_repository, GList *list) {
    data_repository->artist_ids_sorted_by_discography_size = list;
}

void increment_genre_popularity_by_age(StringPool string_pool, DataRepository data_repository, char *age, char *genre) {
    GHashTable *genres_popularity = g_hash_table_lookup(data_repository->genres_popularity_by_age, age);

    if (genres_popularity == NULL) {
        genres_popularity = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
        g_hash_table_insert(data_repository->genres_popularity_by_age, (gpointer)add_string(string_pool, age), genres_popularity);
    }
    
    int *popularity = g_hash_table_lookup(genres_popularity, genre);

    if (popularity == NULL) {
        popularity = g_malloc(sizeof(int));
        *popularity = 1;
        g_hash_table_insert(genres_popularity, (gpointer)add_string(string_pool, genre), popularity);
    } else {
        *popularity += 1;
    }
}

void add_genres_popularity_for_age(StringPool string_pool, DataRepository data_repository, GHashTable *genres_popularity_within_age_interval, char *age) {
    
    GHashTable *genres_popularity_for_age = g_hash_table_lookup(data_repository->genres_popularity_by_age, age);

    if (genres_popularity_for_age == NULL) return;

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, genres_popularity_for_age);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *genre = key;
        int *age_popularity = g_hash_table_lookup(genres_popularity_for_age, genre);
        int *current_popularity = g_hash_table_lookup(genres_popularity_within_age_interval, genre);
        if (current_popularity == NULL) {
            int *new_popularity = g_malloc(sizeof(int));
            *new_popularity = *age_popularity;
            g_hash_table_insert(genres_popularity_within_age_interval, (gpointer)add_string(string_pool, genre), new_popularity);
        } else {
            *current_popularity += *age_popularity;
        }
    }
}

void add_artist_id_by_week(StringPool string_pool, DataRepository data_repository, const char *date, const char *artist_id) {
    GList *list = g_hash_table_lookup(data_repository->top10_artists_by_week, date);
    list = g_list_prepend(list, (gpointer)add_string(string_pool, artist_id));
    g_hash_table_insert(data_repository->top10_artists_by_week, (gpointer)add_string(string_pool, date), list);
}

void set_top10_all_time_artist_id(StringPool string_pool, DataRepository data_repository, const char *artist_id) {
    data_repository->top10_all_time_artist_id = add_string(string_pool, artist_id);
}

void set_most_top10_occurences(DataRepository data_repository, int most_top10_occurences) {
    data_repository->most_top10_occurences = most_top10_occurences;
}

void foreach_date_artist_ids(DataRepository data_repository, IterDataFunc func, DataContainer data) {
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, data_repository->top10_artists_by_week);
    char *date = NULL;
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        date = g_strdup(key);
        GList *artist_ids = g_hash_table_lookup(data_repository->top10_artists_by_week, date);
        char *artist_id = NULL;
        for (GList *iter = artist_ids; iter != NULL; iter = iter->next) {
            artist_id = g_strdup(iter->data);
            func(data, date, artist_id);
            g_free(artist_id);
        }
        g_free(date);
    }
}

void foreach_artist_id_from_date(DataRepository data_repository, const char *date, IterDataFunc func, DataContainer data) {
    GList *artist_ids = g_hash_table_lookup(data_repository->top10_artists_by_week, date);
    if (artist_ids == NULL) return;
    char *artist_id = NULL;
    for (GList *iter = artist_ids; iter != NULL; iter = iter->next) {
        artist_id = g_strdup(iter->data);
        func(data, date, artist_id);
        g_free(artist_id);
    }
}

char *get_top10_all_time_artist_id(DataRepository data_repository) {
    return g_strdup(data_repository->top10_all_time_artist_id);
}

char *get_most_top10_occurences(DataRepository data_repository) {
    return g_strdup_printf("%d", data_repository->most_top10_occurences);
}

void init_users_genres_preferences(DataRepository data_repository, char **user_ids, char **genres, int num_of_users, int num_of_genres) {
    data_repository->users_genres_preferences = g_malloc((num_of_users+1) * sizeof(int *));
    for(int i = 0; i < num_of_users; i++) {
        data_repository->users_genres_preferences[i] = g_malloc0(num_of_genres * sizeof(int));
    }
    data_repository->user_ids = user_ids;
    data_repository->genres = genres;
    data_repository->num_of_users = num_of_users;
    data_repository->num_of_genres = num_of_genres;

    for (int i = 0; i < num_of_genres; i++) {
        int *idx = g_malloc(sizeof(int));
        *idx = i;
        g_hash_table_insert(data_repository->genres_idx, (gpointer)genres[i], idx);
    }
}

void increment_user_genre_preference(DataRepository data_repository, int user_idx, int genre_idx) {
    data_repository->users_genres_preferences[user_idx][genre_idx]++;
}

int get_genre_index(DataRepository data_repository, const char *genre) {
    int *idx = g_hash_table_lookup(data_repository->genres_idx, genre);
    return *idx;
}

char **get_recommended_users(DataRepository data_repository, char *user_id, int n) {
    return recomendaUtilizadores(user_id,
                                 data_repository->users_genres_preferences,
                                 data_repository->user_ids,
                                 data_repository->genres,
                                 data_repository->num_of_users,
                                 data_repository->num_of_genres,
                                 n);

}
