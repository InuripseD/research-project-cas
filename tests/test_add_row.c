#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../cas-db/table.h"
#include "tests.h"

#define ROWS_PER_THREAD 100 // Number of rows to add in the table per thread.

void * thread_computation_add_row (void * params){
	
    // Getting the parameters.
	ThreadParamsTest* args = (ThreadParamsTest *) params;

    GlobalParamsTest* predicat = args -> global_params;

	pthread_t self = pthread_self();

    Table* table = predicat->table;

    // Waiting for all threads to be at the same point.
    wait_barrier(predicat->barrier);
    
    // Adding rows to the table. 
    for (int i = 0; i < ROWS_PER_THREAD; i++){
        add_row(table, '0'+ args->thread_id, self);
    }

	pthread_exit(EXIT_SUCCESS);
}


bool test_add_row(Table* table, int threads_number, ReusableBarrier* barrier){

    // Creating the threads.
	pthread_t threads[threads_number];

    // Creating the global parameters for the threads.
    GlobalParamsTest* global_params = malloc(sizeof(GlobalParamsTest));

    global_params->table = table;
    global_params->barrier = barrier;

    // Creating the threads parameters.
    ThreadParamsTest thread_params[threads_number];

    // Launching the threads.
	for (int i = 0; i < threads_number; i++){
		thread_params[i].thread_id = i;
        thread_params[i].global_params = global_params;

		if (pthread_create(&threads[i], NULL, thread_computation_add_row, &thread_params[i]) != 0){
			perror("error thread creation");
			exit(1);
        }	
	}

    // Joining the threads.
    for (int i = 0; i < threads_number; i++){
		pthread_join(threads[i], NULL);
	}
    
    // Testing the table. 
    
    // TODO: Complete with more verifications.

    // Check that the number of rows is correct.
    if (get_row_count(table) != threads_number*ROWS_PER_THREAD){
        printf("Error: the number of rows is not correct\n");
        return false;
    }

    // Check that all ids are different.
    for (int i = 0; i < threads_number*ROWS_PER_THREAD; i++){
        for (int j = i+1; j < threads_number*ROWS_PER_THREAD; j++){
            if (atomic_load((table->rows[i])->id) == atomic_load((table->rows[j])->id)){
                printf("Error: id %d is not unique\n", atomic_load((table->rows[i])->id));
                return false;
            }
        }
    }

    // Free memory
    free(global_params);

	return true;
}