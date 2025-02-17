#include <stdio.h>

#include "database.h"
#include "repository_artist.h"
#include "repository_data.h"
#include "parser.h"
#include "utils.h"
#include "recomendador.h"
#include "output.h"
#include "data_operations.h"

void query5(Database database, char *args, Output output, char *spacer) {

    char **tokens = g_strsplit(args, " ", 2);

    char *user_id = g_strdup(tokens[0]);
    int n = atoi(tokens[1]);
    g_strfreev(tokens);

    UserRepository user_repository = get_user_repository(database);
    if(!check_user_exists(user_repository, user_id) || n <= 0) {
        g_free(user_id);
        add_line_to_output(output, NULL, NULL);
        return;
    }

    DataRepository data_repository = get_data_repository(database);
    char **recommended_users = get_recommended_users(data_repository, user_id, n);
    g_free(user_id);
    
    for (int i = 0; i < n; i++) {
        char *line[] = {recommended_users[i], NULL};
        add_line_to_output(output, line, spacer);
    }

    g_free(recommended_users);
}