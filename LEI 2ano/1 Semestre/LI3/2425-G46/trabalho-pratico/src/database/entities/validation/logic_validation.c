// Third-party library headers
#include <glib.h>       

// Project headers
#include "repository_music.h"
#include "repository_artist.h"
#include "repository_album.h"
#include "parser.h"


int validate_constituents(const char* list, const char* type) {

    if (strcmp(type, "individual") == 0) {
        int len = strlen(list);
        return (len == 2 && list[0] == '[' && list[len - 1] == ']');
    }

    return 1;
}

int validate_artists(const char *list, ArtistRepository artist_repository) {

    char **artist_ids = parse_list(list);

    for (int i = 0; artist_ids[i] != NULL; i++) {

        char *artist_id = artist_ids[i];

        if (!check_artist_exists(artist_repository, artist_id)) {
            free_list(artist_ids);
            return 0;
        }
    }

    free_list(artist_ids);

    return 1;
}

int validate_musics(const char *list, MusicRepository music_repository) {

    char **music_ids = parse_list(list);

    for (int i = 0; music_ids[i] != NULL; i++) {
        char *music_id = music_ids[i];


        if (!check_music_exists(music_repository, music_id)) {
            free_list(music_ids);
            return 0;
        }
    }
    
    free_list(music_ids);

    return 1;
}

int validate_album(const char *album_id, AlbumRepository album_repository) {

    if (!check_album_exists(album_repository, album_id)) return 0;

    return 1;
}