
#include "database.h"
#include "repository_data.h"
#include "repository_history.h"
#include "data_container.h"
#include "utils.h"
#include "data_operations.h"

void increase_artist_discography_size(DataContainer container, const char *artist_id, const char *music_id) {
    Database database = get_data(container);
    StringPool string_pool = get_string_pool(database);
    DataRepository data_repository = get_data_repository(database);
    ArtistRepository artist_repository = get_artist_repository(database);
    MusicRepository music_repository = get_music_repository(database);

    char *duration = get_music_duration_by_id(music_repository, music_id);
    int time = duration_to_seconds(duration);
    g_free(duration);

    char *country = get_artist_country_by_id(artist_repository, artist_id);
    add_country_by_artist_id(string_pool, data_repository, artist_id, country);
   
    g_free(country);

    increase_discography_size_by_artist_id(string_pool, data_repository, artist_id, time);
}

void calculate_artists_discography_size(Database database) {
    MusicRepository music_repository = get_music_repository(database);
    DataRepository data_repository = get_data_repository(database);
    DataContainer container = init_data_container(0, 0, database, NULL, NULL);

    foreach_artist_music_ids(music_repository, (IterDataFunc)increase_artist_discography_size, container);

    destroy_data_container(container);

    make_sorted_artist_list_from_discography_size_hashtable(data_repository, (GCompareDataFunc)compare_keys_by_value);
}

void preprocess_musics(Database database) {
    calculate_artists_discography_size(database);
}
