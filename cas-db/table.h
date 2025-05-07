#ifndef TABLE_H
#define TABLE_H

#include <stdatomic.h>

#include "row.h"

/** 
 * @brief Defined table size.
 * 
 * The table size is defined to 1000 rows. 
 * This is a fixed size table as a dynamic table would require more concurrency control. 
 */
#define TABLE_SIZE 10000

/**
 * @brief Represents a database table with rows.
 * 
 * This struct follows an OOP-like approach to handling the table. 
 * - The `Table` struct itself holds the rows.
 * - Functions use a `Table*` to manipulate it and its rows as `func(Table* table, ...)`,  
 *   similar to calling `table.function(...)` in Java.
 * 
 * @details The attributes contained in a `Table` are:
 * - **rows**: An array of pointers to `Row` structs.
 * - **row_count**: The number of rows in the table.
 * - **isolation_mode**: The isolation mode of the table. (0 for no isolation, 1 for isolation).
 */
typedef struct {
    Row* rows[TABLE_SIZE]; // Array of addresses of rows.
    atomic_size_t* row_count;
    short isolation_mode; // Is not really used yet, focus on row isolation will be done later.
} Table;


/**
 * @brief Creates a new table with the given isolation mode.
 * 
 * No need to allocates memory as the size is static for simplicity reasons,
 * and initializes its `row_count` to 0 and `isolation_mode` to the given value.
 * The function returns the newly created `Table`.
 * 
 * @param isolation_mode The isolation mode for the table.
 * 
 * @return The newly allocated `Table`.
 */
Table create_table(short isolation_mode);

/** 
 * @brief Atomicaly generates a new unique id for a row.
 * 
 * The first call will return 0 while incrementing the value to 1.
 * The second call will return 1 while incrementing the value to 2.
 * etc.
 * 
 * @param table The table to generate the id for.
 * 
 * @return The new unique id.
 *  
 * @note This function is thread safe.
 */
int new_id(Table* table);

/**
 * @brief Get the number of rows in the table.
 * 
 * @param table The table to get the number of rows from.
 * 
 * @return The number of rows in the table.
 * 
 * @note This function is thread safe.
 */
int get_row_count(Table* table);

/**
 * @brief Find a row in the table by its id.
 * 
 * @details Has two threads may try to create a row in same time, it is not assure 
 *          the rows are stored in croissant id order.
 *          So this function is needed when we need to access a row by its id. 
 * 
 * @param table The table to search in.
 * @param id The id of the row to find.
 * 
 * @return The row with the given id, or `NULL` if not found.
 */
Row* find_row(Table* table, int id);

/**
 * @brief Add a new row to the table with the given values.
 * 
 * The function creates a new row with the given values and adds it to the table.
 * An id is atomically generated for the row, and the row is stored in the table at the index of the id.
 * 
 * @param table The table to add the row to.
 * @param char_value The character value to store in the row.
 * @param long_value The long integer value to store in the row.
 * 
 * @return The id of the row if it was successfully added, or -1 if an error occurred.
 * 
 * @note This function is thread safe.
 */
int add_row(Table* table, char char_value, long long_value);


/**
 * @brief Update a row in the table with the given values.
 * 
 * The function updates the row with the given id in the table with the new values.
 * The row is updated in isolation dependending of the `isolation_mode` (NOT YET IMPLEMENTED),
 * using the `update_char_value` and `update_long_value` functions.
 * 
 * @param table The table to update the row in.
 * @param id The id of the row to update.
 * @param new_char_value The new character value to set.
 * @param new_long_value The new long integer value to set.
 * 
 * @return The number of CAS operation tried before update, or -1 if an error occurred.
 * 
 * TODO : Implement isolation mode if necessary.
 */
int update_row(Table* table, int id, char new_char_value, long new_long_value);

/**
 * @brief Update the character value of a row in the table.
 * 
 * The function atomically updates the character value of the row with the given id in the table.
 * 
 * @param table The table to update the row in.
 * @param id The id of the row to update.
 * @param new_char_value The new character value to set.
 * 
 * @return The number of CAS operation tried before update, or -1 if an error occurred.
 */
int update_row_char(Table* table, int id, char new_char_value);

/**
 * @brief Update the long value of a row in the table.
 * 
 * The function atomically updates the long value of the row with the given id in the table.
 * 
 * @param table The table to update the row in.
 * @param id The id of the row to update.
 * @param new_long_value The new long integer value to set.
 * 
 * @return The number of CAS operation tried before update, or -1 if an error occurred.
 */
int update_row_long(Table* table, int id, long new_long_value);

/**
 * @brief Remove a row from the table by its id.
 * 
 * The function removes the row with the given id from the table.
 * The row is flagged as deleted using the `is_deleted` field.
 * 
 * @param table The table to remove the row from.
 * @param id The id of the row to remove.
 * 
 * @return The number of CAS operation tried before removal, or -1 if an error occurred.
 * 
 * @note This function is thread safe.
 */
int remove_row(Table* table, int id);

/**
 * @brief Destroy the table and free its memory.
 * 
 * The function frees the memory allocated for the table, its rows and fields.
 * 
 * @param table The table to destroy.
 */
void destroy_table(Table* table);

/**
 * @brief Print the table to the console.
 * 
 * It is concidered as the "SELECT * FROM table" SQL query.
 * The function prints the id, char value, long value, and isolation status of each row in the table.
 * 
 * @param table The table to print.
 */
void print_table(Table* table);

#endif // TABLE_H