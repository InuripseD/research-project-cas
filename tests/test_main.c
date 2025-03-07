#include "../cas-db/table.h"
#include "reusable_barrier.h"
#include "tests.h"

int main(){

	int threadsNumber = 8;

    Table table = create_table();

    ReusableBarrier *barrier = create_barrier(threadsNumber);

    test_add_row(&table, threadsNumber, barrier);

    destroy_barrier(barrier);

    //

	return 0;
	
}