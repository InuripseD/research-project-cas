#include <stdlib.h>
#include <stdatomic.h>
#include <stdio.h>

#include "table.h"

Table create_table(short isolation_mode) {
    Table table;
    table.row_count = malloc(sizeof(atomic_size_t));
    atomic_init(table.row_count, 0);
    table.isolation_mode = isolation_mode;
    return table;
}

int new_id(Table* table) {
    return atomic_fetch_add(table->row_count, 1); // Get previous value and increment.
}

int get_row_count(Table* table) {
    return atomic_load(table->row_count);
}

Row* find_row(Table* table, int id) {
    for (int i = 0; i < get_row_count(table); i++) {
        if (atomic_load((table->rows[i])->id) == id) {
            return table->rows[i];
        }
    }
    perror("Row not found\n");
    return NULL;
}

int add_row(Table* table, char char_value, long long_value) {
    // The id of the row will be unique because we use atomic fetch and incrementation.
    int id = new_id(table);

    Row* row = create_row(id, char_value, long_value, table->isolation_mode);

    if (row == NULL) {
        perror("Row not created");
        return -1;
    }

    table->rows[id] = row;

    return id;
}

int update_row(Table* table, int id, char new_char_value, long new_long_value) {

    Row* row = find_row(table, id);
    if (row == NULL) {
        perror("Can't update row.");
        return -1;
    }

    if (!row->is_deleted) {
        return 0;
    }

    int cas_try = 0;

    cas_try += update_char_value(row, new_char_value);
    cas_try += update_long_value(row, new_long_value);

    return cas_try;
}

int update_row_char(Table* table, int id, char new_char_value) {
    Row* row = find_row(table, id);
    if (row == NULL) {
        perror("Can't update row.");
        return -1;
    }

    if (!row->is_deleted) {
        return 0;
    }

    return update_char_value(row, new_char_value);
}

int update_row_long(Table* table, int id, long new_long_value) {
    Row* row = find_row(table, id);
    if (row == NULL) {
        perror("Can't update row.");
        return -1;
    }

    if (!row->is_deleted) {
        return 0;
    }
    return update_long_value(row, new_long_value);
}

int remove_row(Table* table, int id) {
    Row *row = find_row(table, id); 
    if (row == NULL) { 
        perror("Row not found");
        return -1;
    }
    
    int i = 0;

    i += delete_row(row);
    
    return i;
}

void destroy_table(Table* table) {
    for (int i = 0; i < atomic_load(table->row_count); i++) {
        destroy_row(table->rows[i]);
    }
    free(table->row_count);
}

void print_table(Table* table) {
    printf("%-5s %-20s %-20s %-5s\n", "ID", "CHAR_VALUE", "LONG_VALUE", "DELETED");
    for (int i = 0; i < atomic_load(table->row_count); i++) {
        print_row(table->rows[i]);
    }
}