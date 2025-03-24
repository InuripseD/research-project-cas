#include "benchmark_adapted.h"
#include "benchmark_classic.h"

unsigned long long int computation_modify_row_char(void * params){
	
	ThreadParamsBenchmark* args = (ThreadParamsBenchmark *) params;

    unsigned long long int retry = 0;

    retry += update_row_char(args->global_params->table, args->global_params->information_1, ('0'+ (args->thread_id % 10)));

    return retry;
}