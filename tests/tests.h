#ifndef TESTS_H
#define TESTS_H

#include <stdbool.h>

#include "reusable_barrier.h"
#include "../cas-db/table.h"

/**
 * @brief Structure to pass global parameters to the threads.
 * 
 * @details The attributes contained in a `GlobalParams` are:
 * - **barrier**: A pointer to the barrier to synchronize the threads for better quality tests.
 * - **table**: A pointer to the table to modify.
 * - **information_1**: Additionnal information that threads may need depending of the test.
 * - **information_2**: Additionnal information that threads may need depending of the test.
 */
typedef struct {
    ReusableBarrier* barrier;
    Table* table;
    int information_1; // Additionnal information.
    void* information_2; // Additionnal information 2 in case multiple is needed.
} GlobalParams;

/**
 * @brief Structure to pass personnal parameters to the threads.
 * 
 * @details The attributes contained in a `ThreadParams` are:
 * - **thread_id**: The id of the thread.
 * - **globalParams**: A pointer to the global parameters.
 */
typedef struct {
	int thread_id;
    GlobalParams* global_params;
} ThreadParams;

/** 
 * @brief Function is meant to be called by each thread to add rows to the table.
 * 
 * @details This function is called by each thread to add rows to the table.
 *          First the threads will wait until all threads are ready to start adding rows.
 *          Then rows added by each thread will have the thread_id as char_value and pthread_self() as long_value.
 */
void * thread_computation_add_row (void * params);

/** 
 * @brief Function to test the add_row function.
 * 
 * @details This function will create threads to add rows to the table.
 *          The function will then check that all rows have been added with unique ids.
 *          TODO: Add more verifications about addition.
 * 
 * @return true if the test passed, false otherwise.
 */
bool test_add_row(Table* table, int threads_number, ReusableBarrier* barrier);

/** 
 * @brief Function is meant to be called by each thread to modify rows in the table.
 * 
 * @details This function is called by each thread to modify rows in the table.
 *          First the threads will wait until all threads are ready to start modifying rows.
 *          Then each thread will update ames rows multiple times.
 */
void * thread_computation_modify_row (void * params);

/** 
 * @brief Function to test the update_row function.
 * 
 * @details This function will create threads to modify rows in the table.
 *          The function will then check that all rows have been modified correctly.
 *          Checking that each row has char_value == long_value.
 */
bool test_modify_row(Table* table, int threads_number, ReusableBarrier* barrier);

// TODO: Add more tests for delete_row.

#endif // TESTS_H