#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../cas-db/table.h"
#include "tests.h"

void * thread_computation_add_row (void * params){
	
	ThreadParams *args = (ThreadParams *) params;

    GlobalParams *predicat = args -> globalParams;

	pthread_t self = pthread_self();

    Table *table = predicat->table;

    wait_barrier(predicat->barrier);
    
    for (int i = 0; i < 10; i++){
        add_row(table, '0'+ args->threadId, self);
    }

	pthread_exit(EXIT_SUCCESS);
}


bool test_add_row(Table *table, int threadsNumber, ReusableBarrier *barrier){

    // Creating the threads.
	pthread_t threads[threadsNumber];

    // Creating the global parameters for the threads.
    GlobalParams *globalParams = malloc(sizeof(GlobalParams));

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
 
    print_table(table);
    
    // Testing the table. 
    
    // TODO: Complete with more verifications.

    // Check that all ids are different.
    for (int i = 0; i < threadsNumber*10; i++){
        for (int j = i+1; j < threadsNumber*10; j++){
            if (atomic_load((table->rows[i])->id) == atomic_load((table->rows[j])->id)){
                printf("Error: id %d is not unique\n", atomic_load((table->rows[i])->id));
            }
        }
    }

    // Free memory
    free(globalParams);

	return 0;
	
}