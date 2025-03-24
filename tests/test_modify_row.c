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
	
	ThreadParamsTest* args = (ThreadParamsTest *) params;

    GlobalParamsTest* predicat = args -> global_params;

    Table* table = predicat->table;

    // Wait for all threads to be ready.
    wait_barrier(predicat->barrier);
    
    // Update the row multiple times.
    for (int i = 0; i < MODIFICATION_PER_THREAD; i++){
        update_row(table, predicat->information_1, '0'+ args->thread_id, args->thread_id);
    }

	pthread_exit(EXIT_SUCCESS);
}


bool test_modify_row(Table* table, int threads_number, ReusableBarrier* barrier){

    // Creating the threads.
	pthread_t threads[threads_number];

    // Creating the global parameters for the threads.
    GlobalParamsTest* global_params = malloc(sizeof(GlobalParamsTest));

    global_params->table = table;
    global_params->barrier = barrier;

    // Creating the threads parameters.
    ThreadParamsTest thread_params[threads_number];

    for (int k = 0; k < ROWS_NUMBER; k++){
        add_row(table, 'N', -1);
        global_params->information_1 = k;
        // Launching the threads.
        for (int i = 0; i < threads_number; i++){
            thread_params[i].thread_id = i;
            thread_params[i].global_params = global_params;

            if (pthread_create(&threads[i], NULL, thread_computation_modify_row, &thread_params[i]) != 0){
                perror("error thread creation");
                exit(1);
            }	
        }

        // Joining the threads.
        for (int i = 0; i < threads_number; i++){
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
    free(global_params);

	return true;
	
}