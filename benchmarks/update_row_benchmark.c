#include "benchmark.h"
#include "../cas-db/table.h"

// Calculates the time it takes to update the char of a row in a table while multiple threads are working on it.
double updating_row_char(int count){

    Table table = create_table(0);

    add_row(&table, 'A', 19);

    int retyr = 0;

    retyr += update_row_char(&table, 0, 'B');

    destroy_table(&table);

    return retyr;

}
