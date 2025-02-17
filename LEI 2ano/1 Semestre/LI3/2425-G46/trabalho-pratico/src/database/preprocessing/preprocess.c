
#include <stdio.h>
#include <time.h>

#include <glib.h>

#include "database.h"
#include "histories_preprocess.h"
#include "musics_preprocess.h"
#include "users_preprocess.h"

void preprocess(Database database) {

    preprocess_histories(database);

    preprocess_musics(database);

    preprocess_users(database);
}
