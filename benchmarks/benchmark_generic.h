#ifndef BENCHMARK_G_H
#define BENCHMARK_G_H

#include <stdatomic.h>

#include "../tests/reusable_barrier.h"
#include "timer.h"
#include "../cas-db/table.h"

/**
 * @brief This is a structure that contains parameters for a benchmarked function.abort
 */
typedef struct {
    int i; // Useless most of the time. At least for my tests. 
    int int_value;
    pthread_mutex_t* lock;
    atomic_int* atomic_int_value;
    int nb_thread;
    pthread_t* thread;
    Table* table_1;
    Table* table_2;
    // Add as many as necessary. Don't even need to be used.
} FunctionArguments;

/** 
 * @brief Structure to pass function and int value to mark7.
 * 
 * @attention Compare to Java you can't pass a function and a value to it directly.
 *          If you try the function will get executed instead of being passed for later execution.
 * 
 * @details The attributes contained in a `PassedFunctionMark7` are:
 * - **function**: The function to call.
 * - **int_value**: The int value to pass to the function.
 */
typedef struct{
    double (*function)(FunctionArguments*); 
    FunctionArguments* func_args;
} PassedFunctionMark7;   

typedef struct {
    ReusableBarrier* barrier;
    Timer* timer;
    PassedFunctionMark7 * passed_func;
    int count;
} GenericGlobalParams;

/**
 * @brief Structure to pass personnal parameters to the threads.
 * 
 * @details The attributes contained in a `ThreadParams` are:
 * - **thread_id**: The id of the thread.
 * - **globalParams**: A pointer to the global parameters.
 */
typedef struct {
	int thread_id;
    GenericGlobalParams* global_params;
} GenericThreadParams;

/** 
 * @brief C translation of the Java benchmarking function mark7 by Peter Sestoft.
 * 
 * @attention This function better reflect Peter Sestoft's work mark7 function.
 * 
 * @article{sestoft2013microbenchmarks,
 *   title={Microbenchmarks in Java and C\#},
 *   author={Sestoft, Peter},
 *   journal={Lecture Notes, September},
 *   year={2013}
 * }
 */
double mark7(char *msg, PassedFunctionMark7* passed_function);

double generic_thread_mark7(char *msg, PassedFunctionMark7* passed_function_mark7);

double increment_lock(FunctionArguments* params);

double increment_cas(FunctionArguments* params);

double increment_fetch_add(FunctionArguments* params);

/** 
 * Those are the functions to benchmark a CAS operation the PCPP way.
 */
double thread_row_char_update(FunctionArguments* count);
void * thread_computation_modify_row_char(void * params);

/** 
 * I created this function to know the time it takes to overfload an unsigned long long int. 
 */
double increase_a_max_unsigned_long_long_int(FunctionArguments* dc);

/**
 * It completes increase_a_max_unsigned_long_long_int for analyssi purpose.  
 */
void* incr(void * args);

double create_thread(FunctionArguments* params);

double start_thread(FunctionArguments* params);

void * nothing(void * params);

double swap_row(FunctionArguments* params);


#endif // BENCHMARK_G_H