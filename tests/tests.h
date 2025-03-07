#ifndef TESTS_H
#define TESTS_H

#include "reusable_barrier.h"

typedef struct {
    ReusableBarrier * barrier;
    Table * table;
} GlobalParams;

typedef struct {
	int threadId;
    GlobalParams * globalParams;
} ThreadParams;

/* 
 * Each thread calling this function will add 10 rows to the table.
 * The rows added by each will have it threadID as char_value and pthread_self() as long_value.
 */
void * thread_computation_add_row (void * params);

/*
 * Tests that rows are added correctly to the table.
 */
bool test_add_row(Table *table, int threadsNumber, ReusableBarrier *barrier);

// TODO: Add more tests for update_row and delete_row.

#endif // TESTS_H