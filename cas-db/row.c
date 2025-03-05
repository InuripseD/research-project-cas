#include <string.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "row.h"

// https://en.cppreference.com/w/c/atomic/atomic_store Could use "_explicit" on atomic funcitons to more specific memory access orders.
// "memory_order_relaxed" is a memory order access type. See next link for more access types.
// https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html

/*
 * When creating a new row the id is already decided for this row. 
 * So it already is a unique row by default.
 * This way we can use atomic_store here for initialisation.
 * 
 * C atomic library take addresses as arguments to mofiify the value at this address.
 * So it was easier to use pointers for atomic valuers.abort
 * However it make declaration and initialisation a bit more complex.
 */
Row* create_row(int id, char char_value, long long_value){
    // Allocate memory for the row.
    Row* row = malloc(sizeof(Row));
    if(!row){
        perror("Row memory not allocated");
        return NULL;
    }

    // Allocate memory for each atomic field of the row.
    row->id = malloc(sizeof(atomic_int));
    row->char_value = malloc(sizeof(atomic_char));
    row->long_value = malloc(sizeof(atomic_long));
    row->is_deleted = malloc(sizeof(atomic_bool));

    if(!row->id || !row->char_value || !row->long_value || !row->is_deleted){
        perror("Row memory not allocated");
        return NULL;
    }

    // Finally give valuers tot the fields of the row.
    atomic_store(row->id, id);
    atomic_store(row->char_value, char_value);
    atomic_store(row->long_value, long_value);
    atomic_store(row->is_deleted, false);
    return row; // Return the address of the row.
}

// TODO: Check if it works properly (Not each charactere is atomic but the entier string is).
// int update_str_value(Row* row, const char *new_str_value){
//     // return atomic_compare_exchange_strong(&(row->str_value), new_str_value, memory_order_relaxed);
//     return 0;
// }


/*
 * This simply performs a compare and swap on the char value of the row.
 * It returns true if the new value is set, otherwise it return false and
 * the old_char_value is updated with the current value of the char_value of the row.
 */
bool update_char_value(Row* row, char *old_char_value, char new_char_value){
    return atomic_compare_exchange_weak(row->char_value, old_char_value, new_char_value);
}

bool update_long_value(Row* row, long *old_long_value, long new_long_value){
    return atomic_compare_exchange_weak(row->long_value, old_long_value, new_long_value);
}

/* It is still intersting to return if it works or not as it uses weak compare exchange.
 * So it can fail even when is_delete==delete. https://en.cppreference.com/w/c/atomic/atomic_compare_exchange
 */
bool delete_row(Row* row, bool *delete){
    return atomic_compare_exchange_weak(row->is_deleted, delete, true);
}

void print_row(Row* row){
    printf("%-5d %-20c %-20ld %-5d\n", atomic_load(row->id), atomic_load(row->char_value), atomic_load(row->long_value), atomic_load(row->is_deleted));
}