// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "string_pool.h"

typedef struct artist {
    const char *id; // A0000001
    const char *name;
    const char *description; // not used
    const char *recipe_per_stream;
    const char **constituent_ids;
    const char *country;
    const char *type;
} *Artist;

Artist create_artist(StringPool string_pool, char **fields) {
    Artist artist = malloc(sizeof(struct artist));
    artist->id = add_string(string_pool, fields[0]);
    artist->name = add_string(string_pool, fields[1]);
    artist->description = Empty;
    artist->recipe_per_stream = add_string(string_pool, fields[3]);
    artist->constituent_ids = add_list(string_pool, fields[4]);
    artist->country = add_string(string_pool, fields[5]);
    artist->type = add_string(string_pool, fields[6]);
    return artist;
}

void free_artist(Artist artist) {
    free(artist->constituent_ids);
    free(artist);
}

const char *get_artist_id(Artist artist) {
    return artist->id;
}

const char *get_artist_name(Artist artist) {
    return artist->name;
}

const char *get_artist_recipe_per_stream(Artist artist) {
    return artist->recipe_per_stream;
}

const char *get_artist_country(Artist artist) {
    return artist->country;
}

const char *get_artist_type(Artist artist) {
    return artist->type;
}

const char **get_artist_constituent_ids(Artist artist) {
    return artist->constituent_ids;
}

/* GList *get_artist_constituent_ids(Artist artist) {
    GList *list = NULL;
    for (int i = 0; artist->constituent_ids[i] != NULL; i++) {
        list = g_list_prepend(list, g_strdup(artist->constituent_ids[i]));
    }
    return list;
} */

/* void foreach_artist_constituent_id(Artist artist, GHashInsertFunc func, StringPool string_pool, GHashTable *hashtable) {
    for (int i = 0; artist->constituent_ids[i] != NULL; i++) {
        char *constituent_id = g_strdup(artist->constituent_ids[i]);
        func(string_pool, hashtable, constituent_id, artist);
    }
} */
