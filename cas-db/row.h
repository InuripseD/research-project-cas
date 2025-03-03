#ifndef ROW_H
#define ROW_H

#include <stdatomic.h>
#include <stdbool.h>

/*
 * A row is static compare to a real database (can't choose its fields). 
 * There are only an id, a char and a long.
 */

// TODO: Challenge try to adapt every type to be atomic, start with double and string.

typedef struct {
    atomic_int *id;
    atomic_char *char_value;
    // A bit weird for strings, I don't think it will work. // TODO: Adapt to atomic properly.
    // atomic_char str_value[64];
    atomic_long *long_value;
    atomic_bool *is_deleted; // The way to handle deleted rows.
} Row;


/*
 * Allocate new memory for a new row and returns its address.
 */
Row* create_row(int id, char char_value, long long_value);

/*
 * Take a reference to a row and update its char value.
 * Also needs the old value for the compare exchange. 
 * Side effect on given row !
 */
bool update_char_value(Row* row, char *old_char_value, char new_char_value);

/*
 * Take a reference to a row and update its long value.
 * Also needs the old value for the compare exchange. 
 * Side effect on given row !
 */
bool update_long_value(Row* row, long *old_long_value, long new_long_value);

/*
 * Still take reference as the row will not be deleted but flagged as deleted.
 * Side effect on given row !
 * 
 * Probably do not need compare and swap has it is a one way change from false to true.
 * May need volatile however if atomic is removed for storage visisbility.
 */
bool delete_row(Row* row, bool *delete);

/*
 * Print the row. 
 */
void print_row(Row* row);

#endif // ROW_H