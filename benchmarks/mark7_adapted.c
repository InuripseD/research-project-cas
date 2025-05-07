#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


#include "benchmark_adapted.h"
#include "benchmark_generic.h"

void * thread_computation_mark7(void * params){
	
	// ThreadParamsBenchmark* args = (ThreadParamsBenchmark *) params;

    // GlobalParamsBenchmark* predicat = args -> global_params;

	// PassedFunctionMark7_thread* pass_func = predicat->passed_func;

	// unsigned long long int (*function)(void*) = pass_func->function;

    // // Wait for all threads to be ready.

	// is_last_thread(predicat->barrier, predicat->timer, true);
	// wait_barrier(predicat->barrier);
    
    // unsigned long long int retry = 0;
    // // Update the row multiple times.
	// for(int i = 0; i < predicat->information_3; i++){
    // 	retry += (*function)(args);
	// }
	
	// is_last_thread(predicat->barrier, predicat->timer, false);
	// wait_barrier(predicat->barrier);

    // atomic_fetch_add(predicat->information_2, retry);
	// // printf("Retry %llu\n", retry);

	pthread_exit(EXIT_SUCCESS);
}

// unsigned long long int thread_mark7(char *msg, PassedFunctionMark7_thread* passed_function_mark7) {

// 	// n can also be 8 based on the reference paper of this project.
// 	int n = 10; 

// 	// Number of iterations to make sure we run it enough times for the measurement to be accurate.
// 	long count = 1L; 
// 	long total_count = 0L;
// 	long total_count_thread = 0L;

// 	// For now dummy is useless, would like to set it to "CAS number of retries".
// 	double dummy = 0.0;

// 	 // It is already in nanoseconds so we use long.
// 	long running_time = 0;

// 	// For the mean and standard deviation.
// 	double st = 0.0, sst = 0.0; 

// 	// Setting for all the threads to share the same information.
//     int thread_number = passed_function_mark7->int_value;

// 	ReusableBarrier* barrier = create_barrier(thread_number);

// 	GlobalParamsBenchmark* global_params = malloc(sizeof(GlobalParamsBenchmark));

// 	Table table = create_table(0);
// 	add_row(&table, 'Y', 999);

// 	global_params->table = &table;

// 	global_params->barrier = barrier;
// 	global_params->information_1 = 0; // Row added that has to be updated.
// 	global_params->information_2 = malloc(sizeof(atomic_ullong)); // Number of retries.
// 	atomic_init(global_params->information_2, 0); // Initialize the number of retries to 0.
// 	global_params->passed_func = passed_function_mark7; // The function that threads have to exec.

// 	do { 
// 		count *= 2L;
// 		global_params->information_3 = count;
// 		st = sst = 0.0;
// 		for(int j = 0; j < n; j++) {

// 			// Creating the threads.
// 			pthread_t threads[thread_number];

// 			// Creating the threads parameters.
// 			ThreadParamsBenchmark thread_params[thread_number];

// 			// Creating a empty timer for every run.
// 			Timer* timer = malloc(sizeof(Timer));
// 			global_params->timer = timer;
// 			// Launching the threads.
// 			for (int i = 0; i < thread_number; i++){
// 				thread_params[i].thread_id = i;
// 				thread_params[i].global_params = global_params;

// 				if (pthread_create(&threads[i], NULL, thread_computation_mark7, &thread_params[i]) != 0){
// 					perror("error thread creation");
// 					exit(1);
// 				}	
// 			}

// 			// Joining the threads.
// 			for (int i = 0; i < thread_number; i++){
// 				pthread_join(threads[i], NULL);
// 			}
// 			running_time = check(global_params->timer); // End timer here.
// 			double time = (double)running_time / ((double)count * (double)thread_number);
// 			st += time; 
// 			sst += time * time;
// 			total_count += count;
// 			total_count_thread += count * thread_number;
// 			free(global_params->timer);
// 		}
// 	} while (running_time < 250000000 && count < INT_MAX/2);
// 	destroy_barrier(barrier);
// 	destroy_table(&table);
// 	double mean = st / n; 
// 	// Require -lm flag to compile despite including math.h
// 	double sdev = sqrt((sst - mean * mean * n) / (n - 1));
// 	printf("%-40s %12.1lf ns %9.2lf %12ld\n", msg, mean, sdev, count);
// 	printf("Amount of retries : %llu for %ld total operations. Which give %lf retries per operation on average.\n", atomic_load(global_params->information_2), total_count_thread, atomic_load(global_params->information_2) / (double)total_count_thread);
// 	return atomic_load(global_params->information_2);
// }

// unsigned long long int thread_mark7_inc(char *msg, PassedFunctionMark7_thread* passed_function_mark7) {

// 	// n can also be 8 based on the reference paper of this project.
// 	int n = 10; 

// 	// Number of iterations to make sure we run it enough times for the measurement to be accurate.
// 	long count = 1L; 
// 	long total_count = 0L;
// 	long total_count_thread = 0L;

// 	// For now dummy is useless, would like to set it to "CAS number of retries".
// 	double dummy = 0.0;

// 	 // It is already in nanoseconds so we use long.
// 	long running_time = 0;

// 	// For the mean and standard deviation.
// 	double st = 0.0, sst = 0.0; 

// 	// Setting for all the threads to share the same information.
//     int thread_number = passed_function_mark7->int_value;

// 	ReusableBarrier* barrier = create_barrier(thread_number);

// 	GlobalParamsBenchmark* global_params = malloc(sizeof(GlobalParamsBenchmark));

// 	global_params->information_4 = 0ULL;

// 	global_params->information_5 = malloc(sizeof(atomic_ullong)); // Number of inc
// 	atomic_init(global_params->information_5, 0);

// 	global_params->lock = malloc(sizeof(pthread_mutex_t));
// 	pthread_mutex_init(global_params->lock, NULL);

// 	global_params->barrier = barrier;
// 	global_params->information_2 = malloc(sizeof(atomic_ullong)); // Number of inc
// 	atomic_init(global_params->information_2, 0);
// 	global_params->passed_func = passed_function_mark7; // The function that threads have to exec.

// 	do { 
// 		count *= 2L;
// 		global_params->information_3 = count;
// 		st = sst = 0.0;
// 		for(int j = 0; j < n; j++) {

// 			// Creating the threads.
// 			pthread_t threads[thread_number];

// 			// Creating the threads parameters.
// 			ThreadParamsBenchmark thread_params[thread_number];

// 			// Creating a empty timer for every run.
// 			Timer* timer = malloc(sizeof(Timer));
// 			global_params->timer = timer;
// 			// Launching the threads.
// 			for (int i = 0; i < thread_number; i++){
// 				thread_params[i].thread_id = i;
// 				thread_params[i].global_params = global_params;

// 				if (pthread_create(&threads[i], NULL, thread_computation_mark7, &thread_params[i]) != 0){
// 					perror("error thread creation");
// 					exit(1);
// 				}	
// 			}

// 			// Joining the threads.
// 			for (int i = 0; i < thread_number; i++){
// 				pthread_join(threads[i], NULL);
// 			}
// 			running_time = check(global_params->timer); // End timer here.
// 			double time = (double)running_time / ((double)count * (double)thread_number);
// 			st += time; 
// 			sst += time * time;
// 			total_count += count;
// 			total_count_thread += count * thread_number;
// 			free(global_params->timer);
// 		}
// 	} while (running_time < 250000000 && count < INT_MAX/2);
// 	destroy_barrier(barrier);
// 	double mean = st / n; 
// 	// Require -lm flag to compile despite including math.h
// 	double sdev = sqrt((sst - mean * mean * n) / (n - 1));
// 	printf("%-40s %12.1lf ns %9.2lf %12ld\n", msg, mean, sdev, count);
// 	return atomic_load(global_params->information_2);
// }

