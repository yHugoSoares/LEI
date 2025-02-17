#include <stdio.h>

#include <glib.h>

#include "database.h"
#include "repository_data.h"
#include "repository_music.h"
#include "repository_user.h"
#include "utils.h"
#include "user.h"

void apply_to_music(DataContainer container, char *user_id, char *music_id) {

    Database database = get_data(container);
    StringPool string_pool = get_string_pool(database);
    DataRepository data_repository = get_data_repository(database);
    UserRepository user_repository = get_user_repository(database);
    MusicRepository music_repository = get_music_repository(database);

    char *age = get_user_age_by_id(user_repository, user_id);
    char *genre = get_music_genre_by_id(music_repository, music_id);
    
    increment_genre_popularity_by_age(string_pool, data_repository, age, genre);

    g_free(age);
    g_free(genre);
}

void calculate_genres_popularity(Database database) {

    DataContainer container = init_data_container(0, 0, database, NULL, NULL);
    UserRepository user_repository = get_user_repository(database);

    foreach_user_liked_musics(user_repository, (IterDataFunc)apply_to_music, container);

    destroy_data_container(container);
}

void preprocess_users(Database database) {
    calculate_genres_popularity(database);
}