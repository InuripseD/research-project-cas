#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "benchmark_generic.h"
#include "../tests/reusable_barrier.h"
#include "time.h"

void * thread_computation_generic_mark7(void * params){
	
	GenericThreadParams* args = (GenericThreadParams *) params;

    GenericGlobalParams* predicat = args -> global_params;

	PassedFunctionMark7* pass_func = predicat->passed_func;

	double (*function)(FunctionArguments*) = pass_func->function;

    // Wait for all threads to be ready.

	is_last_thread(predicat->barrier, predicat->timer, true);
	wait_barrier(predicat->barrier);
    
    double res = 0;
    // Update the row multiple times.
	for(int i = 0; i < predicat->count; i++){
    	res += (*function)(pass_func->func_args);
	}
	
	is_last_thread(predicat->barrier, predicat->timer, false);
	wait_barrier(predicat->barrier);

	pthread_exit(EXIT_SUCCESS);
}

double generic_thread_mark7(char *msg, PassedFunctionMark7* passed_function_mark7) {

	// n can also be 8 based on the reference paper of this project.
	int n = 10; 

	// Number of iterations to make sure we run it enough times for the measurement to be accurate.
	long count = 1L; 
	long total_count = 0L;
	long total_count_thread = 0L;

	double dummy = 0.0;

	// It is already in nanoseconds so we use long.
	long running_time = 0L;

	// For the mean and standard deviation.
	double st = 0.0, sst = 0.0; 

	// Setting for all the threads to share the same information.
    int thread_number = passed_function_mark7->func_args->nb_thread;

	ReusableBarrier* barrier = create_barrier(thread_number);

	GenericGlobalParams* global_params = malloc(sizeof(GenericGlobalParams));

	global_params->barrier = barrier;
	global_params->passed_func = passed_function_mark7;

	do { 
		count *= 2L;
		global_params->count = count;
		st = sst = 0.0;
		for(int j = 0; j < n; j++) {

			// Creating the threads.
			pthread_t threads[thread_number];

			// Creating the threads parameters.
			GenericThreadParams thread_params[thread_number];

			// Creating a empty timer for every run.
			Timer* timer = malloc(sizeof(Timer));
			if(!timer){printf("Error Timer\n");exit(1);}
			global_params->timer = timer;
			// Launching the threads.
			for (int i = 0; i < thread_number; i++){
				thread_params[i].thread_id = i;
				thread_params[i].global_params = global_params;

				if (pthread_create(&threads[i], NULL, thread_computation_generic_mark7, &thread_params[i]) != 0){
					perror("error thread creation");
					exit(1);
				}	
			}

			// Joining the threads.
			for (int i = 0; i < thread_number; i++){
				pthread_join(threads[i], NULL);
			}
			running_time = check(global_params->timer); // End timer here.
			double time = (double)running_time / ((double)count * (double)thread_number);
			st += time; 
			sst += time * time;
			total_count += count;
			total_count_thread += count * thread_number;
			free(global_params->timer);
		}
	} while (running_time < 250000000 && count < INT_MAX/2);
	destroy_barrier(barrier);
	double mean = st / n; 
	// Require -lm flag to compile despite including math.h
	double sdev = sqrt((sst - mean * mean * n) / (n - 1));
	printf("%-40s %12.1lf ns %9.2lf %12ld\n", msg, mean, sdev, count);
	return dummy / total_count_thread;
}
