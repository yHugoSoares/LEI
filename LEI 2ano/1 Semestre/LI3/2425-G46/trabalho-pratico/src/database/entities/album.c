// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "string_pool.h"

typedef struct album {
    const char *id; // AL000001
    const char *title; // not used
    const char **artist_ids;
    const char *year; // not used
    const char **producers; // not used
} *Album;

Album create_album(StringPool string_pool, char **fields) {
    Album album = malloc(sizeof(struct album));
    album->id = add_string(string_pool, fields[0]);
    album->title = Empty;
    album->artist_ids = add_list(string_pool, fields[2]);
    album->year = Empty;
    album->producers = Empty;
    return album;
}

void free_album(Album album) {
    free(album->artist_ids);
    free(album);
}

const char *get_album_id(Album album) {
    return album->id;
}

const char **get_album_artist_ids(Album album) {
    return album->artist_ids;
}


/* GList *get_album_artist_ids(Album album) {
    GList *list = NULL;
    for (int i = 0; album->artist_ids[i] != NULL; i++) {
        list = g_list_prepend(list, g_strdup(album->artist_ids[i]));
    }
    return list;
} */

/* void foreach_album_artist_id(Album album, GHashInsertFunc func, StringPool string_pool, GHashTable *hashtable) {
    for (int i = 0; album->artist_ids[i] != NULL; i++) {
        char *artist_id = g_strdup(album->artist_ids[i]);
        func(string_pool, hashtable, artist_id, album);
    }
} */
