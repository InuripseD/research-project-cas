#ifndef BENCHMARK_C_H
#define BENCHMARK_C_H

#include "../tests/tests.h"
#include "benchmark_adapted.h"

/**
 * @brief Structure to pass personnal parameters to the threads.
 * 
 * @details The attributes contained in a `ThreadParams` are:
 * - **thread_id**: The id of the thread.
 * - **globalParams**: A pointer to the global parameters.
 */
typedef struct {
	int thread_id;
    GlobalParamsBenchmark* global_params;
} ThreadParamsBenchmark;

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
    double (*function)(int); 
    int int_value;
} PassedFunctionMark7;   

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

double thread_row_char_update(int count);

void * thread_computation_modify_row_char(void * params);

double increase_a_max_unsigned_long_long_int(int dc);

#endif // BENCHMARK_C_H