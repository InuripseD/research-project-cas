#ifndef ROW_H
#define ROW_H

#include <stdatomic.h>

/**
 * @brief Represents a table row with fields using atomic operations.
 * 
 * This struct follows an OOP-like approach to handling rows. 
 * - The `Row` struct itself holds the fields of the row.
 * - Functions use a `Row*` to manipulate a row as `func(Row* row, ...)`,  
 *   similar to calling `row.function(...)` in Java.
 * 
 * The fields and their types are "static" compared to a real database 
 * (they are chosen by default and cannot be modified).
 * 
 * @details The fields contained in a `Row` are:
 * - **id**: Unique identifier, handled by the table. @see add_row in table.h
 * - **char_value**: A character field.
 * - **long_value**: A long integer field.
 * - **is_deleted**: A hidden field indicating whether the row is deleted.
 * - **isolation**: Used to manage row isolation (0 or 1 given by the table).
 * 
 * @note Pointers are used for fields to facilitate atomic operations, 
 * since atomic operations require pointers to atomic values.
 */
typedef struct {
    atomic_int* id;         /**< Unique row identifier */
    atomic_char* char_value; /**< Character field */
    atomic_long* long_value; /**< Long integer field */
    atomic_bool* is_deleted; /**< Indicates if the row is deleted */
    atomic_short* isolation;   /**< Isolation status: 0 (Not isolated), 
                                  1 (Isolated), 2 (Row being used) */
} Row;

// TODO: Challenge, try to adapt every type to be atomic (double, string...).


/**
 * @brief Creates a new row with the given values.
 * 
 * Allocates memory for a new `Row` and initializes its fields with the provided values.
 * The function returns a pointer to the newly created `Row`.
 * 
 * The `id` had already been atomically decided at this point, ensuring uniquity of 
 * the row. @details Also, it allows `atomic_init` to be used which is not atomic.
 * 
 * @param id          The unique identifier for the row.
 * @param char_value  A character value to store in the row.
 * @param long_value  A long integer value to store in the row.
 * @param isolation   The isolation status of the row.
 * 
 * @return A pointer to the newly allocated `Row`, or `NULL` if memory allocation fails.
 * 
 * @note When the table is destroyed, the row will also be destroyed to free memory.
 */
Row* create_row(int id, char char_value, long long_value, short isolation);

/**
 * @brief Atomically updates the character value of a row.
 * 
 * Performs an atomic compare-and-exchange operation on the `char_value` field of the given `Row`.
 * The function updates `char_value` only if it matches the expected `old_char_value`.
 * Otherwise, the function updates `old_char_value` with the current value of `char_value`.
 * 
 * @param row            Pointer to the `Row` to update.
 * @param new_char_value The new character value to set.
 * 
 * @return The number of tries to modify the value before success. 0 if first try.
 * 
 * @note This function is thread safe for `char` field only. (Entire row @see Table.h isolation)
 */
int update_char_value(Row* row, char new_char_value);

/**
 * @brief Atomically updates the long value of a row.
 * 
 * @see update_char_value
 */
int update_long_value(Row* row, long new_long_value);

/**
 * @brief Flags a row as deleted.
 * 
 * Marks the given `Row` as deleted by updating its `is_deleted` field.
 * 
 * @param row Pointer to the `Row` to delete.
 * 
 * @return The number of tries to modify the value before success. 0 if first try.
 * 
 * @note Without isolation mode (isolation = 0), modifications can still occur after deletion.
 */
int delete_row(Row* row);

/**
 * @brief Completely deletes a row.
 * 
 * Frees the memory allocated for the given `Row` and its atomic fields.
 * After calling this function, the `row` pointer becomes invalid.
 * 
 * @param row Pointer to the `Row` to destroy.
 * 
 * @note This function should only be called when deleting a table.
 *       Any further access to the `row` after destruction is undefined behavior.
 */
void destroy_row(Row* row);

/**
 * @brief Prints the contents of a row.
 * 
 * Displays the values stored in the given `Row`.  
 * This function is considered the "read" operation for a row.
 * 
 * @param row Pointer to the `Row` to print.
 * 
 * @note Without isolation mode (isolation = 0), data could be inconsistent.
 */
void print_row(Row* row);


// The following functions are used to manage row isolation. Only for multiple fields updates.

/**
 * @brief Locks a row using isolation status. (NOT USED FOR NOW)
 * 
 * If the isolation status of the given `Row` is 0 (Not isolated), this function does nothing.
 * Otherwise, this function is used to prevent other threads from modifying the row.
 * It sets the isolation status of the given `Row` to 2 (Row being used), 
 * if it is 1, or busy wait until it is 1.
 * 
 * @param row Pointer to the `Row` to "lock".
 */
void row_lock_if(Row* row);

/**
 * @brief Unlocks a row using isolation status. (NOT USED FOR NOW)
 * 
 * If the isolation status of the given `Row` is 0 (Not isolated), this function does nothing.
 * Otherwise, this function is used to allow other threads to modify the row.
 * It sets the isolation status of the given `Row` to 1 (Isolated), 
 * if it is 2, or busy wait until it is 2.
 * 
 * @param row Pointer to the `Row` to "unlock".
 */
void row_unlock_if(Row* row);

#endif // ROW_H