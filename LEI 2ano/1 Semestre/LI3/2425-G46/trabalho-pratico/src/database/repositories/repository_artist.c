// Third-party library headers
#include <glib.h>

// Project headers
#include "defs.h"
#include "utils.h"
#include "data_container.h"
#include "string_pool.h"
#include "artist.h"

typedef struct artist_repository {
    GHashTable *artist_by_id;
    GHashTable *artists_by_constituent_id;
} *ArtistRepository;

ArtistRepository init_artist_repository() {
    ArtistRepository artist_repository = g_new(struct artist_repository, 1);
    artist_repository->artist_by_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_artist);
    artist_repository->artists_by_constituent_id = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    return artist_repository;
}

void free_artist_repository(ArtistRepository artist_repository) {
    g_hash_table_destroy(artist_repository->artist_by_id);

    GList *values = g_hash_table_get_values(artist_repository->artists_by_constituent_id);
    g_list_free_full(values, (GDestroyNotify)g_list_free);
    g_hash_table_destroy(artist_repository->artists_by_constituent_id);

    g_free(artist_repository);
}

void add_artist_by_id(GHashTable *artist_by_id, Artist artist) {
    const char *artist_id = get_artist_id(artist);
    g_hash_table_insert(artist_by_id, (gpointer)artist_id, artist);
}

void add_artist_by_constituent_id(GHashTable *artists_by_constituent_id, const char *constituent_id, Artist artist) {
    GList *artists = g_hash_table_lookup(artists_by_constituent_id, constituent_id);
    artists = g_list_prepend(artists, artist);
    g_hash_table_insert(artists_by_constituent_id, (gpointer)constituent_id, artists);
}

void add_artist_by_constituent_ids(GHashTable *artists_by_constituent_id, Artist artist) {
    const char **constituent_ids = get_artist_constituent_ids(artist);
    for(int i = 0; constituent_ids[i] != NULL; i++) {
        add_artist_by_constituent_id(artists_by_constituent_id, constituent_ids[i], artist);
    }
}

void load_artist(StringPool string_pool, ArtistRepository artist_repository, Artist artist) {
    add_artist_by_id(artist_repository->artist_by_id, artist);
    add_artist_by_constituent_ids(artist_repository->artists_by_constituent_id, artist);
}

int check_artist_exists(ArtistRepository artist_repository, const char *artist_id) {
    return g_hash_table_lookup(artist_repository->artist_by_id, artist_id) != NULL;
}

char *get_artist_name_by_id(ArtistRepository artist_repository, const char *artist_id) {
    Artist artist = g_hash_table_lookup(artist_repository->artist_by_id, artist_id);
    const char *name = get_artist_name(artist);
    return g_strdup(name);
}

char *get_artist_country_by_id(ArtistRepository artist_repository, const char *artist_id) {
    Artist artist = g_hash_table_lookup(artist_repository->artist_by_id, artist_id);
    const char *country = get_artist_country(artist);
    return g_strdup(country);
}

char *get_artist_type_by_id(ArtistRepository artist_repository, const char *artist_id) {
    Artist artist = g_hash_table_lookup(artist_repository->artist_by_id, artist_id);
    const char *type = get_artist_type(artist);
    return g_strdup(type);
}

char *get_artist_recipe_per_stream_by_id(ArtistRepository artist_repository, const char *artist_id) {
    Artist artist = g_hash_table_lookup(artist_repository->artist_by_id, artist_id);
    const char *recipe_per_stream = get_artist_recipe_per_stream(artist);
    return g_strdup(recipe_per_stream);
}

int get_artist_num_of_constituents_by_id(ArtistRepository artist_repository, const char *artist_id) {
    Artist artist = g_hash_table_lookup(artist_repository->artist_by_id, artist_id);
    const char **constituent_ids = get_artist_constituent_ids(artist);
    return get_array_length(constituent_ids);
}

void foreach_artist_id_from_constituent_id(ArtistRepository artist_repository, const char *constituent_id, IterDataFunc func, DataContainer container) {
    GList *artists = g_hash_table_lookup(artist_repository->artists_by_constituent_id, constituent_id);
    char *artist_id = NULL;
    for (GList *artist = artists; artist != NULL; artist = artist->next) {
        artist_id = g_strdup(get_artist_id(artist->data));
        func(container, constituent_id, artist_id);
        g_free(artist_id);
    }
}
