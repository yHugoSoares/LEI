// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "string_pool.h"
#include "utils.h"
#include "data_container.h"
#include "history.h"

typedef struct history_repository {
    GHashTable *history_by_id;
    GHashTable *histories_by_user_id;
    GHashTable *histories_by_adjusted_date;
} *HistoryRepository;

HistoryRepository init_history_repository() {
    HistoryRepository history_repository = g_new(struct history_repository, 1);
    history_repository->history_by_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_history);
    history_repository->histories_by_user_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    history_repository->histories_by_adjusted_date = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    return history_repository;
}

void free_history_repository(HistoryRepository history_repository) {
    g_hash_table_destroy(history_repository->history_by_id);

    GList *values = g_hash_table_get_values(history_repository->histories_by_user_id);
    g_list_free_full(values, (GDestroyNotify)g_list_free);
    g_hash_table_destroy(history_repository->histories_by_user_id);

    values = g_hash_table_get_values(history_repository->histories_by_adjusted_date);
    g_list_free_full(values, (GDestroyNotify)g_list_free);
    g_hash_table_destroy(history_repository->histories_by_adjusted_date);

    g_free(history_repository);
}

void add_history_by_id(GHashTable *history_by_id, History history) {
    const char *history_id = get_history_id(history);
    g_hash_table_insert(history_by_id, (gpointer)history_id, history);
}

void add_history_by_user_id(GHashTable *histories_by_user_id, History history) {
    const char *user_id = get_history_user_id(history);
    GList *histories = g_hash_table_lookup(histories_by_user_id, user_id);
    histories = g_list_prepend(histories, history);
    g_hash_table_insert(histories_by_user_id, (gpointer)user_id, histories);
}

void add_history_by_adjusted_date(StringPool string_pool, GHashTable *histories_by_adjusted_date, History history) {
    const char *date = get_history_date(history);
    char *adjusted_date = adjust_date(date);
    GList *histories = g_hash_table_lookup(histories_by_adjusted_date, adjusted_date);
    histories = g_list_prepend(histories, history);
    g_hash_table_insert(histories_by_adjusted_date, (gpointer)add_string(string_pool, adjusted_date), histories);
    g_free(adjusted_date);
}

void load_history(StringPool string_pool, HistoryRepository history_repository, History history) {
    add_history_by_id(history_repository->history_by_id, history);
    add_history_by_user_id(history_repository->histories_by_user_id, history);
    add_history_by_adjusted_date(string_pool, history_repository->histories_by_adjusted_date, history);
}

int check_history_exists(HistoryRepository history_repository, const char *history_id) { 
    return g_hash_table_lookup(history_repository->history_by_id, history_id) != NULL;
}

char *get_history_music_id_by_id(HistoryRepository history_repository, const char *history_id) {
    History history = g_hash_table_lookup(history_repository->history_by_id, history_id);
    const char *music_id = get_history_music_id(history);
    return g_strdup(music_id);
}

char *get_history_date_by_id(HistoryRepository history_repository, const char *history_id) {
    History history = g_hash_table_lookup(history_repository->history_by_id, history_id);
    const char *date = get_history_date(history);
    return g_strdup(date);
}

char *get_history_duration_by_id(HistoryRepository history_repository, const char *history_id) {
    History history = g_hash_table_lookup(history_repository->history_by_id, history_id);
    const char *duration = get_history_duration(history);
    return g_strdup(duration);
}

char *get_history_year_by_id(HistoryRepository history_repository, const char *history_id) {
    History history = g_hash_table_lookup(history_repository->history_by_id, history_id);
    const char *date = get_history_date(history);
    return get_year_from_date(date);
}

char *get_history_hour_by_id(HistoryRepository history_repository, const char *history_id) {
    History history = g_hash_table_lookup(history_repository->history_by_id, history_id);
    const char *time = get_history_time(history);
    return get_hour_from_time(time);
}

int get_history_elapsed_time_by_id(HistoryRepository history_repository, const char *history_id) {
    History history = g_hash_table_lookup(history_repository->history_by_id, history_id);
    const char *duration = get_history_duration(history);
    return duration_to_seconds(duration);
}

void foreach_history_adjusted_date(HistoryRepository history_repository, IterDataFunc func, DataContainer data) {
    GHashTableIter iter;
    g_hash_table_iter_init(&iter, history_repository->histories_by_adjusted_date);
    gpointer key, value;
    char *date = NULL;
    while(g_hash_table_iter_next(&iter, &key, &value)) {
        date = g_strdup(key);
        func(data, date, NULL);
        free(date);
    }
}

void foreach_history_id_from_date(HistoryRepository history_repository, const char *date, IterDataFunc func, DataContainer data) {
    GList *histories = g_hash_table_lookup(history_repository->histories_by_adjusted_date, date);
    char *history_id = NULL;
    for (GList *history = histories; history != NULL; history = history->next) {
        history_id = g_strdup(get_history_id(history->data));
        func(data, date, history_id);
        g_free(history_id);
    }
}

void foreach_history_id_from_user_id(HistoryRepository history_repository, const char *user_id, IterDataFunc func, DataContainer data) {
    GList *histories = g_hash_table_lookup(history_repository->histories_by_user_id, user_id);
    char *history_id = NULL;
    for (GList *history = histories; history != NULL; history = history->next) {
        history_id = g_strdup(get_history_id(history->data));
        func(data, user_id, history_id);
        g_free(history_id);
    }
}
