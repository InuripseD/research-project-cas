#include "benchmark_adapted.h"
#include "benchmark_generic.h"

// unsigned long long int computation_modify_row_char(void * params){
	
// 	ThreadParamsBenchmark* args = (ThreadParamsBenchmark *) params;

//     unsigned long long int retry = 0;

//     retry += update_row_char(args->global_params->table, args->global_params->information_1, ('0'+ (args->thread_id % 10)));

//     return retry;
// }

// unsigned long long int increment_long_lock(void * params){
	
// 	ThreadParamsBenchmark* args = (ThreadParamsBenchmark *) params;

//     unsigned long long int x;

//     pthread_mutex_lock(args->global_params->lock);

//     x = args->global_params->information_4;

//     pthread_mutex_unlock(args->global_params->lock);

//     return x;
// }

// unsigned long long int increment_long_atomic(void * params){
	
// 	ThreadParamsBenchmark* args = (ThreadParamsBenchmark *) params;

//     return atomic_fetch_add(args->global_params->information_5, 1);
// }
