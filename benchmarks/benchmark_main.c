#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include "benchmark_classic.h"
#include "../cas-db/table.h"
#include "timer.h"

int main(){

    // // -----  GOOD TEST DO NOT REMOVE. -----//
    for(int nb_thread = 1; nb_thread <= 64; nb_thread*=2){
         PassedFunctionMark7* passed_func_classic = malloc(sizeof(PassedFunctionMark7));
         passed_func_classic->function = thread_row_char_update;
         passed_func_classic->int_value = nb_thread;
         printf("Nb_thread %d -> \n", nb_thread);
         unsigned long long int retries = mark7("Mark7 simple: Modify char with CAS", passed_func_classic);
         printf("Retries %llu\n", retries);
    }
    // // ------------------------------------ //

    // -----  GOOD TEST DO NOT REMOVE. -----//
    //for(int nb_thread = 1; nb_thread <= 64; nb_thread*=2){
    //    PassedFunctionMark7_thread* pass_func_adapt = malloc(sizeof(PassedFunctionMark7_thread));
    //    pass_func_adapt->function = computation_modify_row_char;
    //    pass_func_adapt->int_value = nb_thread;
    //    printf("Nb_thread %d -> \n", nb_thread);
    //    thread_mark7("Mark7 adapted: Modify char with CAS", pass_func_adapt);
    //}
    // ------------------------------------ //

    // printf("%d, %ld, %lld, %lf\n", INT_MAX, ULONG_MAX, LLONG_MAX, DBL_MAX);

	return 0;
	
}
