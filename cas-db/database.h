#ifndef DATABASE_H
#define DATABASE_H

#include "table.h"

#define DATABASE_SIZE 1 

/*
 * This is not necessary for now as we only have one table.
 */

typedef struct {
    Table *tables[DATABASE_SIZE];
    size_t table_count;
} Database;


Database create_database();

int add_table(Database* database, Table table);

#endif // DATABASE_H