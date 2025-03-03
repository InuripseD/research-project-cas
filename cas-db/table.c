#include <stdlib.h>
#include <stdatomic.h>
#include <stdio.h>
#include <assert.h>

#include "table.h"

Table create_table() {
    Table table;
    table.row_count = malloc(sizeof(atomic_size_t));
    atomic_store(table.row_count, 0);
    return table;
}

/*
 * First call for instance will return 0 while incrementing the value to 1.
 * Second call will return 1 while incrementing the value to 2.
 * 
 * Handle atomicity of the incrementation of the ids.
 */
int new_id(Table* table) {
    return atomic_fetch_add(table->row_count, 1); // Get previous value and increment.
}

/*
 * Usefull as it is often needed to call the last id being used.
 */
int get_id(Table* table) {
    return atomic_load(table->row_count);
}

/*
 * Has two threads may try to create a row in same time, it is not assure the rows are in croissant id order.
 * So this function is needed when we need to update a row by its id.
 */
Row* find_row(Table* table, int id) {
    for (int i = 0; i < get_id(table); i++) {
        if (atomic_load((table->rows[i])->id) == id) {
            return table->rows[i];
        }
    }
    return NULL;
}

/*
 * The id of the row will be unique as we use atomic fetch and incrementation.
 */
int add_row(Table* table, char char_value, long long_value) {
    int id = new_id(table);

    Row *row = create_row(id, char_value, long_value);
    table->rows[id] = row;

    return 0;
}

int update_row(Table* table, int id, char new_char_value, long new_long_value) {
    Row *row = find_row(table, id);
    if (row == NULL) {
        return -1;
    }

    int i = 0;

    // In case we con't update the char we pass '\0'. 
    if (new_char_value != '\0') {

        // FROM HERE 
        char old = atomic_load(row->char_value);
        while(!update_char_value(row, &old, new_char_value)){
            i++;
        }
        // TILL HERE
        // This is an atomic modification of the char value of the row. We try CAS (aka here compare exchange) until it works.
        // Might need a function as it might be used in other places later.
        
    }

    // Same here with -1.
    if (new_long_value != -1) { // TODO: Easy solution here but not the best.
        long old = atomic_load(row->long_value);
        while(!update_long_value(row, &old, new_long_value)){
            i++;
        }
    }

    return i;
}

/*
 * Here for now, nothing ensusre that rows are sorted by id.
 * So we have to check every row to find the one to update.
 */
int remove_row(Table* table, int id) {
    Row *row = find_row(table, id);
    if (row == NULL) {
        perror("Row not found");
        return -1;
    }
    int i = 0;
    bool delete = false;
    while(!delete_row(row, &delete)){
        i++;
    }
    return i;
}

void print_table(Table* table) {
    printf("%-5s %-20s %-10s %-5s\n", "ID", "STR_VALUE", "LONG_VALUE", "DELETED");
    for (int i = 0; i < atomic_load(table->row_count); i++) {
        print_row(table->rows[i]);
    }
}