#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "benchmark_classic.h"
#include "../cas-db/table.h"

double increase_a_max_unsigned_long_long_int(int dc){
    unsigned long long int a = 0ULL;
    for (unsigned long long int i = 0; i < ULLONG_MAX/8; i++){
        a++;
    }
    return (double)a;
}

double thread_row_char_update(int count){

    ReusableBarrier* barrier = create_barrier(count);

    Table table = create_table(0);
    add_row(&table, 'Y', 999);

    // Creating the threads.
    pthread_t threads[count];

    // Creating the global parameters for the threads.
    GlobalParamsBenchmark* global_params = malloc(sizeof(GlobalParamsBenchmark));

    global_params->table = &table;
    global_params->barrier = barrier;
    global_params->information_1 = 0;
    global_params->information_2 = malloc(sizeof(atomic_ullong));
    atomic_init(global_params->information_2, 0ULL);

    // Creating the threads parameters.
    ThreadParamsBenchmark thread_params[count];

    // Launching the threads.
    for (int i = 0; i < count; i++){
        thread_params[i].thread_id = i;
        thread_params[i].global_params = global_params;

        if (pthread_create(&threads[i], NULL, thread_computation_modify_row_char, &thread_params[i]) != 0){
            perror("error thread creation");
            exit(1);
        }	
    }

    // Joining the threads.
    for (int i = 0; i < count; i++){
        pthread_join(threads[i], NULL);
    }

    destroy_table(&table);
    destroy_barrier(barrier);

    return (double)atomic_load(global_params->information_2);
}

void * thread_computation_modify_row_char(void * params){
	
	ThreadParamsBenchmark* args = (ThreadParamsBenchmark *) params;

    GlobalParamsBenchmark* predicat = args -> global_params;

    Table* table = predicat->table;

    // Wait for all threads to be ready.
    wait_barrier(predicat->barrier);
    
    unsigned long long int retry = 0ULL;
    // Update the row multiple times.
    retry += update_row_char(table, predicat->information_1, ('0'+ (args->thread_id % 10)));

    atomic_fetch_add(&predicat->information_2, retry);

	pthread_exit(EXIT_SUCCESS);
}