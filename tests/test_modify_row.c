#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "../cas-db/table.h"
#include "tests.h"

#define MODIFICATION_PER_THREAD 10
#define ROWS_NUMBER 100

void * thread_computation_modify_row (void * params){
	
	ThreadParams* args = (ThreadParams *) params;

    GlobalParams* predicat = args -> globalParams;

    Table* table = predicat->table;

    // Wait for all threads to be ready.
    wait_barrier(predicat->barrier);
    
    // Update the row multiple times.
    for (int i = 0; i < MODIFICATION_PER_THREAD; i++){
        update_row(table, predicat->information_1, '0'+ args->threadId, args->threadId);
    }

	pthread_exit(EXIT_SUCCESS);
}


bool test_modify_row(Table* table, int threadsNumber, ReusableBarrier* barrier){

    // Creating the threads.
	pthread_t threads[threadsNumber];

    // Creating the global parameters for the threads.
    GlobalParams* globalParams = malloc(sizeof(GlobalParams));

    globalParams->table = table;
    globalParams->barrier = barrier;

    // Creating the threads parameters.
    ThreadParams threadParams[threadsNumber];

    for (int k = 0; k < ROWS_NUMBER; k++){
        add_row(table, 'N', -1);
        globalParams->information_1 = k;
        // Launching the threads.
        for (int i = 0; i < threadsNumber; i++){
            threadParams[i].threadId = i;
            threadParams[i].globalParams = globalParams;

            if (pthread_create(&threads[i], NULL, thread_computation_modify_row, &threadParams[i]) != 0){
                perror("error thread creation");
                exit(1);
            }	
        }

        // Joining the threads.
        for (int i = 0; i < threadsNumber; i++){
            pthread_join(threads[i], NULL);
        }
    }
    
    // Testing the table. 

    // Check that all char_value == long_value.
    for (int i = 0; i < ROWS_NUMBER; i++){
        char char_value = atomic_load((table->rows[i])->char_value);
        long long_value = atomic_load((table->rows[i])->long_value);
        if (char_value != ('0'+long_value)){
            printf("Error: Update not atomic, row: %d, char: %c, long: %ld\n", atomic_load((table->rows[i])->id), char_value, long_value);
            return false;
        }     
    }

    // Free memory
    free(globalParams);

	return true;
	
}