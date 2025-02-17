// Standard library headers
#include <stdio.h>
#include <stdlib.h>    
#include <time.h> 

// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "load.h"
#include "string_pool.h"
#include "repository_artist.h"
#include "repository_music.h"
#include "repository_user.h"
#include "repository_album.h"
#include "repository_history.h"
#include "repository_data.h"
#include "fields_validation.h"
#include "preprocess.h"

typedef struct database {
    StringPool string_pool;
    ArtistRepository artist_repository;
    MusicRepository music_repository;
    UserRepository user_repository;
    AlbumRepository album_repository;
    HistoryRepository history_repository;
    DataRepository data_repository;
} DatabaseStruct, *Database;

Database init_database() {

    Database database = g_new(DatabaseStruct, 1);

    database->string_pool = init_string_pool();
    database->artist_repository = init_artist_repository();
    database->music_repository = init_music_repository();
    database->user_repository = init_user_repository();
    database->album_repository = init_album_repository();
    database->history_repository = init_history_repository();
    database->data_repository = init_data_repository();

    return database;
}

void free_database(Database database) {

    free_string_pool(database->string_pool);
    free_artist_repository(database->artist_repository);
    free_music_repository(database->music_repository);
    free_user_repository(database->user_repository);
    free_album_repository(database->album_repository);
    free_history_repository(database->history_repository);
    free_data_repository(database->data_repository);
    g_free(database);
}

StringPool get_string_pool(Database database) {
    return database->string_pool;
}

ArtistRepository get_artist_repository(Database database) {
    return database->artist_repository;
}

MusicRepository get_music_repository(Database database) {
    return database->music_repository;
}

UserRepository get_user_repository(Database database) {
    return database->user_repository;
}

AlbumRepository get_album_repository(Database database) {
    return database->album_repository;
}

HistoryRepository get_history_repository(Database database) {
    return database->history_repository;
}

DataRepository get_data_repository(Database database) {
    return database->data_repository;
}

Database load_database(const char *dataset_folder_path) {

    Database database = init_database();

    load(dataset_folder_path, "artists.csv", "resultados/artists_errors.csv",
         database, database->string_pool, database->artist_repository,
         (ValidateFunc)validate_artist_fields, (CreateFunc)create_artist, (LoadFunc)load_artist);

    load(dataset_folder_path, "albums.csv", "resultados/albums_errors.csv",
         database, database->string_pool, database->album_repository,
         (ValidateFunc)validate_album_fields, (CreateFunc)create_album, (LoadFunc)load_album);

    load(dataset_folder_path, "musics.csv", "resultados/musics_errors.csv",
         database, database->string_pool, database->music_repository,
         (ValidateFunc)validate_music_fields, (CreateFunc)create_music, (LoadFunc)load_music);

    load(dataset_folder_path, "users.csv", "resultados/users_errors.csv",
         database, database->string_pool, database->user_repository,
         (ValidateFunc)validate_user_fields, (CreateFunc)create_user, (LoadFunc)load_user);

    load(dataset_folder_path, "history.csv", "resultados/history_errors.csv",
         database, database->string_pool, database->history_repository,
         (ValidateFunc)validate_history_fields, (CreateFunc)create_history, (LoadFunc)load_history);

    preprocess(database);

    return database;
}

// Run small dataset:
// time ./programa-principal files/fase2/small/dataset/com_erros files/fase2/small/inputs-small.txt

// Run big dataset:
// time ./programa-principal files/fase2/big/com_erros files/fase2/big/inputs-big.txt

// Run interativo:
// ./programa-interativo

// Run tests:
// ./programa-testes dataset dataset/input.txt resultados-esperados