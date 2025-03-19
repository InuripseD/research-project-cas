#include <stdio.h>

#include "database.h"
#include "table.h"

int main() {

    // Simple tests on the database to quickly check if it works properly.
    
    printf("Creating table...\n");
    Table table = create_table(0);

    printf("Adding rows...\n");
    add_row(&table, 'A', 55.5);
    add_row(&table, 'B', 600);
    add_row(&table, 'B', 6001);
    add_row(&table, 'o', 6005);
    add_row(&table, 'c', 6050);
    add_row(&table, '8', 7.89);
    add_row(&table, 'p', 6800);
    add_row(&table, 'x', 60);
    add_row(&table, 'p', 6800);

    printf("Printing initial Table...\n");
    print_table(&table);

    printf("\nRemoving rows...\n");
    remove_row(&table, 3);
    remove_row(&table, 5);

    printf("Updating rows...\n");
    update_row_char(&table, 1, 'Z');
    update_row_long(&table, 2, 9999);
    update_row(&table, 4, 'z', 9999);

    printf("\nTable after modifs...\n");
    print_table(&table);

    destroy_table(&table);

    return 0;
}