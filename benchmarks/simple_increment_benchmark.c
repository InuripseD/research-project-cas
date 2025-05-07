#include <stdlib.h>
#include <stdio.h>

#include "benchmark_generic.h"

double increment_lock(FunctionArguments* params){

    pthread_mutex_lock(params->lock);

    params->int_value++;

    pthread_mutex_unlock(params->lock);

    return 0.0;
}

double increment_cas(FunctionArguments* params){

    int old_val = atomic_load(params->atomic_int_value);

    while(!atomic_compare_exchange_weak(params->atomic_int_value, &old_val, old_val+1)){

    } // 10.6 ns

    return 0.0;
}

double increment_fetch_add(FunctionArguments* params){

    atomic_fetch_add(params->atomic_int_value, 1); // 6.4 ns

    return 0.0;
}

double create_thread(FunctionArguments* params){

    pthread_t thread;

    return 0.0;
}

double start_thread(FunctionArguments* params){

    pthread_t thread;

    if (pthread_create(&thread, NULL, nothing, params) != 0){
        perror("error thread creation");
        exit(1);
    }

    // pthread_join(thread, NULL);

    return 0.0;
}

void * nothing(void * params){
    return NULL;
}

double swap_row(FunctionArguments* params){
    Table t = create_table(0);
    add_row(&t, atomic_load(params->table_1->rows[params->int_value]->char_value), atomic_load(params->table_1->rows[params->int_value]->long_value));
    destroy_table(&t);
    return 0.0;
}