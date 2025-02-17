// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "string_pool.h"
#include "music.h"
#include "data_container.h"

typedef struct music_repository {
    GHashTable *music_by_id;      
    GHashTable *musics_by_artist_id;
    GHashTable *genres;
} MusicRepositoryStruct, *MusicRepository;

MusicRepository init_music_repository() {
    MusicRepository music_repository = g_new(MusicRepositoryStruct, 1);
    music_repository->music_by_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_music);
    music_repository->musics_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    music_repository->genres = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    return music_repository;
}

void free_music_repository(MusicRepository music_repository) {
    g_hash_table_destroy(music_repository->music_by_id);

    GList *value = g_hash_table_get_values(music_repository->musics_by_artist_id);
    g_list_free_full(value, (GDestroyNotify)g_list_free);
    g_hash_table_destroy(music_repository->musics_by_artist_id);

    g_hash_table_destroy(music_repository->genres);
    g_free(music_repository);
}

void add_music_by_id(GHashTable *music_by_id, Music music) {
    const char *music_id = get_music_id(music);
    g_hash_table_insert(music_by_id, (gpointer)music_id, music);
}

void add_music_by_artist_id(GHashTable *musics_by_artist_id, const char *artist_id, Music music) {
    GList *musics = g_hash_table_lookup(musics_by_artist_id, artist_id);
    musics = g_list_prepend(musics, music);
    g_hash_table_insert(musics_by_artist_id, (gpointer)artist_id, musics);
}

void add_music_by_artist_ids(GHashTable *musics_by_artist_id, Music music) {
    const char **artist_ids = get_music_artist_ids(music);
    for (int i = 0; artist_ids[i] != NULL; i++) {
        add_music_by_artist_id(musics_by_artist_id, artist_ids[i], music);
    }
}

void update_genres(GHashTable *genres, Music music) {
    const char *genre = get_music_genre(music);
    if (g_hash_table_lookup(genres, genre) == NULL) {
        g_hash_table_insert(genres, (gpointer)genre, (gpointer)genre);
    }
}

void load_music(StringPool string_pool, MusicRepository music_repository, Music music) {
    add_music_by_id(music_repository->music_by_id, music);
    add_music_by_artist_ids(music_repository->musics_by_artist_id, music);
    update_genres(music_repository->genres, music);
}

int check_music_exists(MusicRepository music_repository, const char *music_id) {
    return g_hash_table_lookup(music_repository->music_by_id, music_id) != NULL;
}

char *get_music_genre_by_id(MusicRepository music_repository, const char *music_id) {
    Music music = g_hash_table_lookup(music_repository->music_by_id, music_id);
    const char *genre = get_music_genre(music);
    return g_strdup(genre);
}

char *get_music_album_id_by_id(MusicRepository music_repository, const char *music_id) {
    Music music = g_hash_table_lookup(music_repository->music_by_id, music_id);
    const char *album_id = get_music_album_id(music);
    return g_strdup(album_id);
}

char *get_music_duration_by_id(MusicRepository music_repository, const char *music_id) {
    Music music = g_hash_table_lookup(music_repository->music_by_id, music_id);
    const char *duration = get_music_duration(music);
    return g_strdup(duration);
}

GList *get_music_artist_ids_by_id(MusicRepository music_repository, const char *music_id) {
    Music music = g_hash_table_lookup(music_repository->music_by_id, music_id);
    const char **artist_ids = get_music_artist_ids(music);
    GList *artist_ids_list = NULL;
    for (int i = 0; artist_ids[i] != NULL; i++) {
        artist_ids_list = g_list_prepend(artist_ids_list, g_strdup(artist_ids[i]));
    }
    return artist_ids_list;
}

char **get_genres(MusicRepository music_repository) {
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, music_repository->genres);
    char **genres = g_malloc((g_hash_table_size(music_repository->genres) + 1) * sizeof(char *));
    int index = 0;
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        genres[index++] = g_strdup(key);
    }
    genres[index] = NULL;
    return genres;
}

int get_num_of_genres(MusicRepository music_repository) {
    return g_hash_table_size(music_repository->genres);
}

void foreach_artist_music_ids(MusicRepository music_repository, IterDataFunc func, DataContainer container) {
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, music_repository->musics_by_artist_id);
    char *artist_id = NULL;
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        artist_id = g_strdup(key);
        GList *musics = g_hash_table_lookup(music_repository->musics_by_artist_id, key);
        char *music_id = NULL;
        for (GList *music = musics; music != NULL; music = music->next) {
            music_id = g_strdup(get_music_id(music->data));
            func(container, artist_id, music_id);
            g_free(music_id);
        }
        g_free(artist_id);
    }
}
