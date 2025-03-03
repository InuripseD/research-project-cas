#ifndef TABLE_H
#define TABLE_H

#include <stdatomic.h>

#include "row.h"

// Tried with dinamic size but doesn't seems worth the effort as rows may be stored consistently anyway.
#define TABLE_SIZE 100 

/*
 * It is static compare to a real database (can't choose its fields, there are defined in "Row" structure).
 */
typedef struct {
    Row *rows[TABLE_SIZE]; // Array of addresses of rows.
    atomic_size_t *row_count;
} Table;


/*
 * Returns a new table with row_counts at 0.
 */
Table create_table();

/*
 * Add a row to the table with the given values.
 */
int add_row(Table* table, char char_value, long long_value);

/*
 * Find the row with the given id has they are not sorted.
 */
Row* find_row(Table* table, int id);

/*
 * Update the row with the given id with the given values.
 * 
 * Return the number of try to modify the row value before succes (usefull for data about one thread).
 */
int update_row(Table* table, int id, char char_value, long long_value);

/*
 * Remove the row with the given id.
 *
 * Return the number of try to modify the row value before succes.
 */
int remove_row(Table* table, int id);

/*
 * Print the table.
 */
void print_table(Table* table);

#endif // TABLE_H