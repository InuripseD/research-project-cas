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
	ThreadParams* args = (ThreadParams *) params;

    GlobalParams* predicat = args -> globalParams;

	pthread_t self = pthread_self();

    Table* table = predicat->table;

    // Waiting for all threads to be at the same point.
    wait_barrier(predicat->barrier);
    
    // Adding rows to the table. 
    for (int i = 0; i < ROWS_PER_THREAD; i++){
        add_row(table, '0'+ args->threadId, self);
    }

	pthread_exit(EXIT_SUCCESS);
}


bool test_add_row(Table* table, int threadsNumber, ReusableBarrier* barrier){

    // Creating the threads.
	pthread_t threads[threadsNumber];

    // Creating the global parameters for the threads.
    GlobalParams* globalParams = malloc(sizeof(GlobalParams));

    globalParams->table = table;
    globalParams->barrier = barrier;

    // Creating the threads parameters.
    ThreadParams threadParams[threadsNumber];

    // Launching the threads.
	for (int i = 0; i < threadsNumber; i++){
		threadParams[i].threadId = i;
        threadParams[i].globalParams = globalParams;

		if (pthread_create(&threads[i], NULL, thread_computation_add_row, &threadParams[i]) != 0){
			perror("error thread creation");
			exit(1);
        }	
	}

    // Joining the threads.
    for (int i = 0; i < threadsNumber; i++){
		pthread_join(threads[i], NULL);
	}
    
    // Testing the table. 
    
    // TODO: Complete with more verifications.

    // Check that the number of rows is correct.
    if (get_row_count(table) != threadsNumber*ROWS_PER_THREAD){
        printf("Error: the number of rows is not correct\n");
        return false;
    }

    // Check that all ids are different.
    for (int i = 0; i < threadsNumber*ROWS_PER_THREAD; i++){
        for (int j = i+1; j < threadsNumber*ROWS_PER_THREAD; j++){
            if (atomic_load((table->rows[i])->id) == atomic_load((table->rows[j])->id)){
                printf("Error: id %d is not unique\n", atomic_load((table->rows[i])->id));
                return false;
            }
        }
    }

    // Free memory
    free(globalParams);

	return true;
}