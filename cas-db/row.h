#ifndef ROW_H
#define ROW_H

#include <stdatomic.h>
#include <stdbool.h>

/*
 * Functions on rows requires side effects as we basically reflect OOP strategy.
 * Instead of allocating new memory creating a new row when updating or deleting a row,
 * we will directly modify the row passed as argument.
 */

/*
 * The fields of a row are static compare to a real database (They are choosen by default and can't be modifided). 
 * Fields contained are only: an id, a char, a long and an "hidden" field to state if the row is deleted or not.
 * 
 * Here pointer of fields are used because:
 *  - It facilitate the use of atomic operations on the fields as they require pointers of atomic values.
 */
typedef struct {
    atomic_int *id;
    atomic_char *char_value;
    atomic_long *long_value;
    atomic_bool *is_deleted; // The way to handle deleted rows.
} Row;

// atomic_char str_value[64];
// A bit weird for strings, I don't think it will work. // TODO: Adapt to atomic properly.
// TODO: Challenge try to adapt every type to be atomic, start with double and string. If I have free time.

/*
 * Allocate new memory for a new row, initialize it with the given values.
 * And returns its address.
 */
Row* create_row(int id, char char_value, long long_value);

/*
 * Takes a reference to a row and atomically update its char value.
 * Also needs the expected old value for the compare exchange. 
 * Side effect on given row !
 */
bool update_char_value(Row* row, char *old_char_value, char new_char_value);

/*
 * Takes a reference to a row and atomically update its long value.
 * Also needs the expected old value for the compare exchange. 
 * Side effect on given row !
 */
bool update_long_value(Row* row, long *old_long_value, long new_long_value);

/*
 * Takes a reference to a row and flag it as deleted.
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