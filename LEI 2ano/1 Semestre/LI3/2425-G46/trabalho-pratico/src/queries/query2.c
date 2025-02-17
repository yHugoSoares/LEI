#include <stdio.h>

#include "database.h"
#include "repository_artist.h"
#include "repository_data.h"
#include "parser.h"
#include "utils.h"
#include "data_operations.h"
#include "output.h"
#include "data_container.h"

void query2(Database database, char *args, Output output, char *spacer) {

    char **tokens = g_strsplit(args, " ", 2);

    int n = atoi(tokens[0]);
    char *country = remove_char(tokens[1], '\"');

    g_strfreev(tokens);

    if (n <= 0) {
        g_free(country);
        add_line_to_output(output, NULL, NULL);
        return;
    }

    DataRepository data_repository = get_data_repository(database);
    ArtistRepository artist_repository = get_artist_repository(database);

    char **n_largest_artist_ids = get_n_largest_artists_by_discography_size(data_repository, n, country);
    g_free(country);

    for (int i = 0; n_largest_artist_ids[i] != NULL && i < n; i++) {
        char *artist_id = n_largest_artist_ids[i];
        char *name = get_artist_name_by_id(artist_repository, artist_id);
        char *country = get_artist_country_by_id(artist_repository, artist_id);
        char *type = get_artist_type_by_id(artist_repository, artist_id);
        char *discography_duration = get_artist_discography_duration_by_id(data_repository, artist_id);
        char *line[] = {name, type, discography_duration, country, NULL};

        add_line_to_output(output, line, spacer);

        g_free_all(name, country, type, discography_duration, NULL);
    }
    g_strfreev(n_largest_artist_ids);
}