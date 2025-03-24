#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "row.h"

/** @brief Functions to create, update, delete, and destroy rows.
 *
 * Except for the `create_row` function, all functions perform atomic operations 
 * on the fields of a `Row`. 
 * 
 * @attention The operations aren't performed in a transactional way by default.
 *           The `isolation` field is used to manage row isolation. Setting it to 0
 *          allows mixed operations on the row. All these functions should be used 
 *         by the Table encapsulated by `row_lock_if` and `row_unlock_if` to ensure isolation.
 * 
 * @see row.h
 */

Row* create_row(int id, char char_value, long long_value, short isolation){
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
    row->isolation = malloc(sizeof(atomic_int));

    if(!row->id || !row->char_value || !row->long_value || !row->is_deleted || !row->isolation){
        perror("Fields memory not allocated");
        return NULL;
    }

    // Finally give values to the fields of the row.
    atomic_init(row->id, id);
    atomic_init(row->char_value, char_value);
    atomic_init(row->long_value, long_value);
    atomic_init(row->is_deleted, false);
    atomic_init(row->isolation, isolation);

    return row; // Return the address of the row.
}

unsigned long long int update_char_value(Row* row, char new_char_value){
    if (row == NULL || row->char_value == NULL) {
        perror("Row can't be modified because doesn't exists.");
        return -1;
    }
    unsigned long long int i = 0ULL;
    char old = atomic_load(row->char_value);
    while(!atomic_compare_exchange_weak(row->char_value, &old, new_char_value)){
        i++; // TODO : Interferes with running time. See if another solution is possible.
    }
    return i;
}

int update_long_value(Row* row, long new_long_value){
    if (row == NULL || row->long_value == NULL) {
        perror("Row can't be modified because doesn't exists.");
        return -1;
    }
    int i = 0;
    long old = atomic_load(row->long_value);
    while(!atomic_compare_exchange_weak(row->long_value, &old, new_long_value)){
        i++;
    }
    return i;
}

int delete_row(Row* row){
    if (row == NULL || row->char_value == NULL) {
        perror("Row can't be deleted because doesn't exists.");
        return -1;
    }
    int i = 0;
    bool old = atomic_load(row->is_deleted);
    while(!atomic_compare_exchange_weak(row->is_deleted, &old, true)){
        i++;
    }
    return i;
}

void destroy_row(Row* row){
    free(row->id);
    free(row->char_value);
    free(row->long_value);
    free(row->is_deleted);
    free(row->isolation);
    free(row);
}

void print_row(Row* row){
    printf("%-5d %-20c %-20ld %-5d\n", atomic_load(row->id), atomic_load(row->char_value), atomic_load(row->long_value), atomic_load(row->is_deleted));
}

void row_lock_if(Row* row){
    short iso = atomic_load(row->isolation);
    if (iso == 0){
        return;
    }
    iso = 1;
    while (!atomic_compare_exchange_weak(row->isolation, &iso, 2)) {
        iso = 1;
    }   
}

void row_unlock_if(Row* row){
    short iso = atomic_load(row->isolation);
    if (iso == 0){
        return;
    }
    iso = 2;
    while (!atomic_compare_exchange_weak(row->isolation, &iso, 1)) {
        iso = 2; // Should not be needed has it supposed to already be 2.
    }
}