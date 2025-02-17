#include "defs.h"
#include "database.h"
#include "repository_data.h"
#include "repository_artist.h"
#include "data_container.h"
#include "utils.h"
#include "recomendador.h"

char *get_key_by_highest_value(GHashTable *hashtable, int tie_breaker_type) {

    char *highest_value_key = NULL;
    int highest_value = -1;
    
    GHashTableIter i;
    gpointer k, v;

    g_hash_table_iter_init(&i, hashtable);
    while (g_hash_table_iter_next(&i, &k, &v)) {
        char *key = k;
        int *value = v;
        if (*value > highest_value) {
            highest_value = *value;
            highest_value_key = key;
        } else if (*value == highest_value && tie_breaker_type == 0 && strcmp(key, highest_value_key) < 0) {
            highest_value = *value;
            highest_value_key = key;
        } else if (*value == highest_value && tie_breaker_type == 1 && strcmp(key, highest_value_key) > 0) {
            highest_value = *value;
            highest_value_key = key;
        }
    }

    return g_strdup(highest_value_key);
}


int compare_keys_by_value(void *a, void *b, void *user_data) {
    GHashTable *hashtable = (GHashTable *)user_data;
    char *key1 = (char *)a;
    char *key2 = (char *)b;
    int *value1 = g_hash_table_lookup(hashtable, key1);
    int *valu2 = g_hash_table_lookup(hashtable, key2);
    int diff = *valu2 - *value1;
    if (diff != 0) {
        return diff;
    } else {
        return g_strcmp0(key1, key2);
    }
}

void increase_value_by_key(DataContainer container, const char *key, int increase) {
    Database database = get_data(container);
    StringPool string_pool = get_string_pool(database);
    GHashTable *hashtable = get_hashtable(container);

    int *value = g_hash_table_lookup(hashtable, key);

    if (value == NULL) {
        int *new_value = g_malloc(sizeof(int));
        *new_value = increase;
        g_hash_table_insert(hashtable, (gpointer)add_string(string_pool, key), new_value);
    } else {
        *value += increase;
    }
}

void increment_value_by_key(DataContainer container, const char *key) {
    Database database = get_data(container);
    StringPool string_pool = get_string_pool(database);
    GHashTable *hashtable = get_hashtable(container);

    int *value = g_hash_table_lookup(hashtable, key);
    if (value == NULL) {
        int *new_value = g_malloc(sizeof(int));
        *new_value = 1;
        g_hash_table_insert(hashtable, (gpointer)add_string(string_pool, key), new_value);
    } else {
        *value += 1;
    }
}

GHashTable *get_genres_popularity_within_age_interval(Database database, int min_age, int max_age) {

    StringPool string_pool = get_string_pool(database);
    DataRepository data_repository = get_data_repository(database);
    GHashTable *genres_popularity_within_age_interval = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);

    for(int i = min_age; i <= max_age; i++) {
        char *age = g_strdup_printf("%d", i);
        add_genres_popularity_for_age(string_pool, data_repository, genres_popularity_within_age_interval, age);
        g_free(age);
    }

    return genres_popularity_within_age_interval;
}

void wrapper(DataContainer container, char *date, char *artist_id) {
    increment_value_by_key(container, artist_id);
}

char **get_top10_artist_and_occurences(Database database, const char *begin_date, const char *end_date) {
    char **result;

    GHashTable *top10_artists_in_the_week_interval = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
    DataContainer container = init_data_container(0, 0, database, NULL, top10_artists_in_the_week_interval);

    DataRepository data_repository = get_data_repository(database);
    char *current_date, *temp_date = g_strdup(begin_date);
    while (g_strcmp0(temp_date, end_date) <= 0) {
        current_date = temp_date;
        foreach_artist_id_from_date(data_repository, current_date, (IterDataFunc)wrapper, container);
        temp_date = get_next_week(current_date);
        g_free(current_date);
    }
    g_free(temp_date);
    destroy_data_container(container);

    if (g_hash_table_size(top10_artists_in_the_week_interval) == 0) {
        g_hash_table_destroy(top10_artists_in_the_week_interval);
        return NULL;
    }

    GList *artist_ids = g_hash_table_get_keys(top10_artists_in_the_week_interval);
    GList *sorted_artist_ids = g_list_sort_with_data(artist_ids, (GCompareDataFunc)compare_keys_by_value, top10_artists_in_the_week_interval);

    char *artist_id = sorted_artist_ids->data;
    int *occurrences = g_hash_table_lookup(top10_artists_in_the_week_interval, artist_id);

    result = g_malloc(3 * sizeof(char **));
    result[0] = g_strdup(artist_id);
    result[1] = g_strdup_printf("%d", *occurrences);
    result[2] = NULL;

    g_list_free(sorted_artist_ids);
    g_hash_table_destroy(top10_artists_in_the_week_interval);

    return result;
}

void calculate_coletive_recipe(DataContainer container, char *constituent_id, char *artist_id) {
    double coletive_recipe = get_d(container);
    Database database = get_data(container);
    ArtistRepository artist_repository = get_artist_repository(database);
    DataRepository data_repository = get_data_repository(database);

    char *recipe_per_stream_coletive = get_artist_recipe_per_stream_by_id(artist_repository, artist_id);
    int num_of_streams_coletive = get_artist_num_of_streams_by_id(data_repository, artist_id);
    int num_of_constituents = get_artist_num_of_constituents_by_id(artist_repository, artist_id);

    coletive_recipe += (num_of_streams_coletive * atof(recipe_per_stream_coletive)) / num_of_constituents;
    set_d(container, coletive_recipe);

    g_free(recipe_per_stream_coletive);
}

char *get_artist_total_recipe(Database database, const char *artist_id) {
    double individual_recipe = 0;
    double coletive_recipe = 0;

    ArtistRepository artist_repository = get_artist_repository(database);
    DataRepository data_repository = get_data_repository(database);

    char *recipe_per_stream_individual = get_artist_recipe_per_stream_by_id(artist_repository, artist_id);
    int num_of_streams_individual = get_artist_num_of_streams_by_id(data_repository, artist_id);
    
    individual_recipe = num_of_streams_individual * atof(recipe_per_stream_individual);
    g_free(recipe_per_stream_individual);

    DataContainer container = init_data_container(0, 0, database, NULL, NULL);
    foreach_artist_id_from_constituent_id(artist_repository, artist_id, (IterDataFunc)calculate_coletive_recipe, container);
    coletive_recipe = get_d(container);
    destroy_data_container(container);

    return g_strdup_printf("%.2f", individual_recipe + coletive_recipe);
}
