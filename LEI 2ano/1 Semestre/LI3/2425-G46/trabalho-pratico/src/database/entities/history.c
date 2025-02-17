// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "parser.h"
#include "utils.h"
#include "string_pool.h"

typedef struct history {
    const char *id; // H000000001
    const char *user_id;
    const char *music_id;
    const char *date;
    const char *time;
    const char *duration;
    const char *platform; // not used
} *History;

History create_history(StringPool string_pool, char **fields) {
    History history = g_malloc(sizeof(struct history));
    history->id = add_string(string_pool, fields[0]);
    history->user_id = add_string(string_pool, fields[1]);
    history->music_id = add_string(string_pool, fields[2]);
    char *date = g_strndup(fields[3], 10);
    char *time = g_strndup(&fields[3][11], 8);
    history->date = add_string(string_pool, date);
    history->time = add_string(string_pool, time);
    g_free_all(date, time, NULL);
    history->duration = add_string(string_pool, fields[4]);
    history->platform = Empty;
    
    return history;
}

void free_history(History history) {
    g_free(history);
}

const char *get_history_id(History history) {
    return history->id;
}

const char *get_history_user_id(History history) {
    return history->user_id;
}

const char *get_history_music_id(History history) {
    return history->music_id;
}

const char *get_history_date(History history) {
    return history->date;
}

const char *get_history_time(History history) {
    return history->time;
}

const char *get_history_duration(History history) {
    return history->duration;
}
