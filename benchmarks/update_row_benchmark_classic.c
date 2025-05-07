#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "benchmark_generic.h"
#include "../cas-db/table.h"

// double increase_a_max_unsigned_long_long_int(FunctionArguments* func_params){
//     int nb_thread = func_params->int_value;
//     pthread_t threads[nb_thread];

//     GenericGlobalParams* global_params = malloc(sizeof(GenericGlobalParams));
//     global_params->information_2 = malloc(sizeof(atomic_ullong));
//     atomic_init(global_params->information_2, 0ULL);

//     for(int i = 0; i < nb_thread; i++){

//         if (pthread_create(&threads[i], NULL, incr, global_params) != 0){
//             perror("error thread creation");
//             exit(1);
//         }	
//     }

//     // Joining the threads.
//     for (int i = 0; i < nb_thread; i++){
//         pthread_join(threads[i], NULL);
//     }

//     return (double)atomic_load(global_params->information_2);
// }

// void * incr(void * args){

//     GenericGlobalParams* params = (GenericGlobalParams*) args;

//     for (unsigned long long int i = 0; i < ULLONG_MAX; i++){
//         atomic_fetch_add(params->information_2, 1);
//     }

//     pthread_exit(EXIT_SUCCESS);
// }

// double thread_row_char_update(FunctionArguments* func_params){

//     int count = func_params->int_value;

//     ReusableBarrier* barrier = create_barrier(count);

//     Table table = create_table(0);
//     add_row(&table, 'Y', 999);

//     // Creating the threads.
//     pthread_t threads[count];

//     // Creating the global parameters for the threads.
//     GenericGlobalParams* global_params = malloc(sizeof(GenericGlobalParams));

//     global_params->table = &table;
//     global_params->barrier = barrier;
//     global_params->information_1 = 0;
//     global_params->information_2 = malloc(sizeof(atomic_ullong));
//     atomic_init(global_params->information_2, 0ULL);

//     // Creating the threads parameters.
//     GenericThreadParams thread_params[count];

//     // Launching the threads.
//     for (int i = 0; i < count; i++){
//         thread_params[i].thread_id = i;
//         thread_params[i].global_params = global_params;

//         if (pthread_create(&threads[i], NULL, thread_computation_modify_row_char, &thread_params[i]) != 0){
//             perror("error thread creation");
//             exit(1);
//         }	
//     }

//     // Joining the threads.
//     for (int i = 0; i < count; i++){
//         pthread_join(threads[i], NULL);
//     }

//     destroy_table(&table);
//     destroy_barrier(barrier);

//     return (double)atomic_load(global_params->information_2);
// }

// void * thread_computation_modify_row_char(void * params){
	
// 	GenericThreadParams* args = (GenericThreadParams*) params;

//     GenericGlobalParams* predicat = args -> global_params;

//     Table* table = predicat->table;

//     // Wait for all threads to be ready.
//     wait_barrier(predicat->barrier);
    
//     unsigned long long int retry = 0ULL;
//     // Update the row multiple times.
//     retry += update_row_char(table, predicat->information_1, ('0'+ (args->thread_id % 10)));

//     atomic_fetch_add(predicat->information_2, retry);

// 	pthread_exit(EXIT_SUCCESS);
// }