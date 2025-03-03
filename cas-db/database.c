#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "database.h"

Database create_database() {
    Database database;
    database.table_count = 0;
    return database;
}
