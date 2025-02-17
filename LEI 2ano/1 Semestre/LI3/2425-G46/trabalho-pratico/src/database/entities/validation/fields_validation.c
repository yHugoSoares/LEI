#include "fields_validation.h"
#include "database.h"
#include "syntatic_validation.h"
#include "logic_validation.h"
#include <stdio.h>

int validate_artist_fields(const char **fields, Database database) { // working

    const char *constituent_ids = fields[4];
    const char *type = fields[6];

    if (!validate_list(constituent_ids) ||
        !validate_constituents(constituent_ids, type)) return 0;

    return 1;
}

int validate_music_fields(const char **fields, Database database) { // not working

    const char *artist_ids = fields[2];
    const char *album_id = fields[3];
    const char *duration = fields[4];

    if (!validate_list(artist_ids) ||
        !validate_duration(duration) ||
        !validate_album(album_id, get_album_repository(database)) ||
        !validate_artists(artist_ids, get_artist_repository(database))) return 0;

    return 1;
}

int validate_user_fields(const char **fields, Database database) { // not working

    const char *email = fields[1];
    const char *birth_date = fields[4];
    const char *subscription_type = fields[6];
    const char *liked_music_ids = fields[7];

    if (!validate_email(email) ||
        !validate_date(birth_date) ||
        !validate_subscription(subscription_type) ||
        !validate_list(liked_music_ids) ||
        !validate_musics(liked_music_ids, get_music_repository(database))) return 0;

    return 1;
}

int validate_album_fields(const char **fields, Database database) { // working (unsure because there are no errors in the album dataset)

    const char *artist_ids = fields[2];
    const char *producers = fields[4];

    if (!validate_list(artist_ids) ||
        !validate_list(producers)) return 0;

    return 1;
}

int validate_history_fields(const char **fields, Database database) { // working

    const char *duration = fields[4];

    if (!validate_duration(duration)) return 0;

    return 1;
}
