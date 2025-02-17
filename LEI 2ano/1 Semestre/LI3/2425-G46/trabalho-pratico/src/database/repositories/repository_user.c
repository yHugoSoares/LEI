// Third-party library headers
#include <glib.h>     

// Project headers
#include "defs.h"
#include "string_pool.h"
#include "user.h"
#include "data_container.h"
#include "utils.h"

typedef struct user_repository {
    GHashTable *user_by_id; 
    int num_of_users;
} UserRepositoryStruct, *UserRepository;

UserRepository init_user_repository() {
    UserRepository user_repository = g_new(UserRepositoryStruct, 1);
    user_repository->user_by_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_user);
    user_repository->num_of_users = 0;
    return user_repository;
}

void free_user_repository(UserRepository user_repository) {
    g_hash_table_destroy(user_repository->user_by_id);

    g_free(user_repository);
}

void add_user_by_id(GHashTable *user_by_id, User user) {
    const char *user_id = get_user_id(user);
    g_hash_table_insert(user_by_id, (gpointer)user_id, user);
}

void load_user(StringPool string_pool, UserRepository user_repository, User user) {
    add_user_by_id(user_repository->user_by_id, user);
    user_repository->num_of_users++;
}

int check_user_exists(UserRepository user_repository, char *user_id) {
    return g_hash_table_lookup(user_repository->user_by_id, user_id) != NULL;
}

char *get_user_email_by_id(UserRepository user_repository, char *user_id) {
    User user = g_hash_table_lookup(user_repository->user_by_id, user_id);
    const char *email = get_user_email(user);
    return g_strdup(email);
}

char *get_user_first_name_by_id(UserRepository user_repository, char *user_id) {
    User user = g_hash_table_lookup(user_repository->user_by_id, user_id);
    const char *first_name = get_user_first_name(user);
    return g_strdup(first_name);
}

char *get_user_last_name_by_id(UserRepository user_repository, char *user_id) {
    User user = g_hash_table_lookup(user_repository->user_by_id, user_id);
    const char *last_name = get_user_last_name(user);
    return g_strdup(last_name);
}

char *get_user_country_by_id(UserRepository user_repository, char *user_id) {
    User user = g_hash_table_lookup(user_repository->user_by_id, user_id);
    const char *country = get_user_country(user);
    return g_strdup(country);
}

char *get_user_age_by_id(UserRepository user_repository, char *user_id) {
    User user = g_hash_table_lookup(user_repository->user_by_id, user_id);
    const char *birth_date = get_user_birth_date(user);
    return calculate_age(birth_date);
}

char **get_user_ids(UserRepository user_repository) { // TO BE REPLACED FOR HASHTABLE ITER
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, user_repository->user_by_id);
    int index = 0;
    char **user_ids = g_malloc((user_repository->num_of_users + 1) * sizeof(char *));
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        user_ids[index++] = g_strdup(key);
    }
    user_ids[index] = NULL;
    return user_ids;
}

int get_num_of_users(UserRepository user_repository) {
    return user_repository->num_of_users;
}

void foreach_user_liked_musics(UserRepository user_repository, IterDataFunc func, DataContainer container) {
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, user_repository->user_by_id);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        User user = value;
        foreach_liked_musics_from_user(user, func, container);
    }
}
