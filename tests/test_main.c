#include <stdio.h>

#include "../cas-db/table.h"
#include "reusable_barrier.h"
#include "tests.h"

int main(){

	int threads_number = 8;

    ReusableBarrier* barrier = create_barrier(threads_number);

    // Test add row.
    Table table = create_table(0);
    if (test_add_row(&table, threads_number, barrier)) {
        printf("Test add row passed!\n");
    } else {
        printf("Test add row failed!\n");
    }
    destroy_table(&table);

    // Test modify row. WILL FAIL AS ISOLATION IS NOT IMPLEMENTED.
    Table table2 = create_table(1);
    if (test_modify_row(&table2, threads_number, barrier)) {
        printf("Test modify row passed!\n");
    } else {
        printf("Test modify row failed!\n");
    }
    destroy_table(&table2);

    


    destroy_barrier(barrier);

	return 0;
	
}