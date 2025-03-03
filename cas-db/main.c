#include <stdio.h>

#include "database.h"
#include "table.h"

int main() {
    Table table = create_table();
    add_row(&table, 'A', 55.5);
    add_row(&table, 'B', 600);
    add_row(&table, 'B', 6001);
    add_row(&table, 'o', 6005);
    add_row(&table, 'c', 6050);
    add_row(&table, '8', 6800);
    add_row(&table, 'p', 6800);

    printf("Initial Table:\n");
    print_table(&table);

    remove_row(&table, 3);
    remove_row(&table, 5);

    update_row(&table, 2, 'C', 6002);

    printf("\nAfter Modifs:\n");
    print_table(&table);

    return 0;
}