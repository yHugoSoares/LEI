// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "utils.h"
#include "string_pool.h"
#include "data_container.h"

typedef struct user {
    const char *id; // U0000001
    const char *email;
    const char *first_name;
    const char *last_name;
    const char *birth_date;
    const char *country;
    const char *subscription_type;
    const char **liked_music_ids;
} UserStruct, *User;

User create_user(StringPool string_pool, char **fields) {
    User user = malloc(sizeof(struct user));
    user->id = add_string(string_pool, fields[0]);
    user->email = add_string(string_pool, fields[1]);
    user->first_name = add_string(string_pool, fields[2]);
    user->last_name = add_string(string_pool, fields[3]);
    user->birth_date = add_string(string_pool, fields[4]);
    user->country = add_string(string_pool, fields[5]);
    user->subscription_type = Empty;
    user->liked_music_ids = add_list(string_pool, fields[7]);
    return user;
}

void free_user(User user) {
    free(user->liked_music_ids);
    g_free(user);
}

const char *get_user_id(User user) {
    return user->id;
}

const char *get_user_email(User user) {
    return user->email;
}

const char *get_user_first_name(User user) {
    return user->first_name;
}

const char *get_user_last_name(User user) {
    return user->last_name;
}

const char *get_user_birth_date(User user) {
    return user->birth_date;
}

const char *get_user_country(User user) {
    return user->country;
}

const char **get_user_liked_music_ids(User user) {
    return user->liked_music_ids;
}

void foreach_liked_musics_from_user(User user, IterDataFunc func, DataContainer container) {
    char *user_id = g_strdup(user->id);
    char *music_id = NULL;
    for (int i = 0; user->liked_music_ids[i] != NULL; i++) {
        music_id = g_strdup(user->liked_music_ids[i]);
        func(container, user_id, music_id);
        g_free(music_id);
    }
    g_free(user_id);
}


/* GList *get_user_liked_musics(User user) {
    GList *list = NULL;
    for (int i = 0; user->liked_music_ids[i] != NULL; i++) {
        list = g_list_prepend(list, g_strdup(user->liked_music_ids[i]));
    }
    return list;
} */
