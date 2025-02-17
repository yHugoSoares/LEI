// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "string_pool.h"
#include "album.h"

typedef struct album_repository {
    GHashTable *album_by_id;  
    GHashTable *albums_by_artist_id;    
} *AlbumRepository;

AlbumRepository init_album_repository() {
    AlbumRepository album_repository = g_new(struct album_repository, 1);
    album_repository->album_by_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_album);
    album_repository->albums_by_artist_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    return album_repository;
}

void free_album_repository(AlbumRepository album_repository) {
    g_hash_table_destroy(album_repository->album_by_id);

    GList *values = g_hash_table_get_values(album_repository->albums_by_artist_id);
    g_list_free_full(values, (GDestroyNotify)g_list_free);
    g_hash_table_destroy(album_repository->albums_by_artist_id);

    g_free(album_repository);
}

void add_album_by_id(GHashTable *album_by_id, Album album) {
    const char *album_id = get_album_id(album);
    g_hash_table_insert(album_by_id, (gpointer)album_id, album);
}

void add_album_by_artist_id(GHashTable *albums_by_artist_id, const char *artist_id, Album album) {
    GList *albums = g_hash_table_lookup(albums_by_artist_id, artist_id);
    albums = g_list_prepend(albums, album);
    g_hash_table_insert(albums_by_artist_id, (gpointer)artist_id, albums);
}

void add_album_by_artist_ids(GHashTable *albums_by_artist_id, Album album) {
    const char **artist_ids = get_album_artist_ids(album);
    for (int i = 0; artist_ids[i] != NULL; i++) {
        add_album_by_artist_id(albums_by_artist_id, artist_ids[i], album);
    }
}

void load_album(StringPool string_pool, AlbumRepository album_repository, Album album) {
    add_album_by_id(album_repository->album_by_id, album);
    add_album_by_artist_ids(album_repository->albums_by_artist_id, album);
}

int check_album_exists(AlbumRepository album_repository, const char *album_id) {
    return g_hash_table_lookup(album_repository->album_by_id, album_id) != NULL;
}

char *get_artist_num_of_individual_albums_by_id(AlbumRepository album_repository, const char *artist_id) {
    GList *albums = g_hash_table_lookup(album_repository->albums_by_artist_id, artist_id);
    return g_strdup_printf("%d", g_list_length(albums));
}
