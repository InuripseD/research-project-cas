#ifndef BENCHMARK_A_H
#define BENCHMARK_A_H

#include <stdatomic.h>

#include "../tests/reusable_barrier.h"
#include "../cas-db/table.h"
#include "timer.h"

typedef struct{
    unsigned long long int (*function)(void *); 
    int int_value; // number of threads.
} PassedFunctionMark7_thread;   

typedef struct {
    ReusableBarrier* barrier;
    Table* table;
    Timer* timer;
    PassedFunctionMark7_thread* passed_func;
    int information_1; // Additionnal information.
    atomic_ullong* information_2; // Additionnal information 2 in case multiple is needed.
    long information_3; // Additionnal information 3.
} GlobalParamsBenchmark;

unsigned long long int computation_modify_row_char(void * params);

void * thread_computation_mark7(void * params);

unsigned long long int thread_mark7(char *msg, PassedFunctionMark7_thread* passed_function_mark7);


#endif // BENCHMARK_A_H