// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "string_pool.h"

typedef struct music {
    const char *id; // S0000001
    const char *title; // not used
    const char **artist_ids;
    const char *album_id;
    const char *duration;
    const char *genre;
    const char *year; // not used
    const char *lyrics; // not used
} *Music;

Music create_music(StringPool string_pool, char **fields) {
    Music music = malloc(sizeof(struct music));
    music->id = add_string(string_pool, fields[0]);
    music->title = Empty;
    music->artist_ids = add_list(string_pool, fields[2]);
    music->album_id = add_string(string_pool, fields[3]);
    music->duration = add_string(string_pool, fields[4]);
    music->genre = add_string(string_pool, fields[5]);
    music->year = Empty;
    music->lyrics = Empty;
    return music;
}

void free_music(Music music) {
    free(music->artist_ids);
    g_free(music);
}

const char *get_music_id(Music music) {
    return music->id;
}

const char *get_music_album_id(Music music) {
    return music->album_id;
}

const char *get_music_duration(Music music) {
    return music->duration;
}

const char *get_music_genre(Music music) {
    return music->genre;
}

const char **get_music_artist_ids(Music music) {
    return music->artist_ids;
}

/* GList *get_music_artist_ids(Music music) {
    GList *list = NULL;
    for (int i = 0; music->artist_ids[i] != NULL; i++) {
        list = g_list_prepend(list, g_strdup(music->artist_ids[i]));
    }
    return list;
}
 */

/* void foreach_music_artist_id(Music music, GHashInsertFunc insert_func, StringPool string_pool, GHashTable *hashtable) {
    for (int i = 0; music->artist_ids[i] != NULL; i++) {
        char *artist_id = g_strdup(music->artist_ids[i]);
        insert_func(string_pool, hashtable, artist_id, music);
    }
}
 */