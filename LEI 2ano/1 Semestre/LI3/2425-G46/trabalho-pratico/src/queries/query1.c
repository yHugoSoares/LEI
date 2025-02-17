#include "database.h"
#include "repository_user.h"
#include "repository_artist.h"
#include "repository_music.h"
#include "repository_data.h"
#include "utils.h"
#include "output.h"
#include "data_operations.h"

void query1_user(Database database, char *user_id, Output output, char *spacer) {    
    
    UserRepository user_repository = get_user_repository(database);

    if (!check_user_exists(user_repository, user_id)) {
        add_line_to_output(output, NULL, NULL);
        return;
    }

    char *email = get_user_email_by_id(user_repository, user_id);
    char *first_name = get_user_first_name_by_id(user_repository, user_id);
    char *last_name = get_user_last_name_by_id(user_repository, user_id);
    char *age = get_user_age_by_id(user_repository, user_id);
    char *country = get_user_country_by_id(user_repository, user_id);
    char *line[] = {email, first_name, last_name, age, country, NULL};

    add_line_to_output(output, line, spacer);
    
    g_free_all(email, first_name, last_name, age, country, NULL);
}

void query1_artist(Database database, char *artist_id, Output output, char *spacer) {

    ArtistRepository artist_repository = get_artist_repository(database);

    if (!check_artist_exists(artist_repository, artist_id)) {
        add_line_to_output(output, NULL, NULL);
        return;
    }

    AlbumRepository album_repository = get_album_repository(database);

    char *name = get_artist_name_by_id(artist_repository, artist_id);
    char *type = get_artist_type_by_id(artist_repository, artist_id);
    char *country = get_artist_country_by_id(artist_repository, artist_id);
    char *num_individual_albums = get_artist_num_of_individual_albums_by_id(album_repository, artist_id);
    char *total_recipe = get_artist_total_recipe(database, artist_id);
    char *line[] = {name, type, country, num_individual_albums, total_recipe, NULL};

    add_line_to_output(output, line, spacer);

    g_free_all(name, type, country, num_individual_albums, total_recipe, NULL);
}

void query1(Database database, char *args, Output output, char *spacer) {

    char *id = args;

    switch (id[0]) {
    case 'U':
        query1_user(database, id, output, spacer);
        break;
    case 'A':
        query1_artist(database, id, output, spacer);
        break;
    default:
        add_line_to_output(output, NULL, NULL);
        return;
    }
}

