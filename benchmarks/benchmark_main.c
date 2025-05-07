#include <stdio.h>
#include <stdlib.h>

#include "benchmark_generic.h"

int main(){

    // FunctionArguments* func_args_thread = malloc(sizeof(FunctionArguments));
    // PassedFunctionMark7* passed_func_thread = malloc(sizeof(PassedFunctionMark7));
    // passed_func_thread->function = create_thread;
    // passed_func_thread->func_args = func_args_thread;
    // mark7("Time needed to create a thread: ", passed_func_thread);
    // free(func_args_thread);
    // free(passed_func_thread);

    // FunctionArguments* func_args_thread_s = malloc(sizeof(FunctionArguments));
    // PassedFunctionMark7* passed_func_thread_s = malloc(sizeof(PassedFunctionMark7));
    // passed_func_thread_s->function = start_thread;
    // passed_func_thread_s->func_args = func_args_thread_s;
    // mark7("Time needed to start a thread: ", passed_func_thread_s);
    // free(func_args_thread_s);
    // free(passed_func_thread_s);

    printf("//------------------------Swap a row from tables----------------------//\n");
    for(int nb_thread = 1; nb_thread <= 64; nb_thread *= 2){
        FunctionArguments* func_args_cas_thread = malloc(sizeof(FunctionArguments));
        func_args_cas_thread->atomic_int_value = malloc(sizeof(atomic_int));
        func_args_cas_thread->int_value = 0;
        func_args_cas_thread->nb_thread = nb_thread; // Number of threads to run the bechmark on.
        Table table_1 = create_table(0);
        add_row(&table_1, 'A', 55.5);
        func_args_cas_thread->table_1 = &table_1;

        PassedFunctionMark7* pass_func_cas_thread = malloc(sizeof(PassedFunctionMark7));
        pass_func_cas_thread->function = swap_row;
        pass_func_cas_thread->func_args= func_args_cas_thread;

        printf("With %2d thread: ", nb_thread);
        generic_thread_mark7("Time needed for one row swapping using CAS:", pass_func_cas_thread);  
        free(func_args_cas_thread->atomic_int_value);
        free(func_args_cas_thread);
        free(pass_func_cas_thread); 
    }
    printf("//-------------------------------------------------------------------------------------------//\n\n");

    // Increase with Lock
    printf("//------------------------Increase a value with Lock-------------------------//\n");
    FunctionArguments* func_args_lock = malloc(sizeof(FunctionArguments));
    func_args_lock->int_value = 0; // Value to increase.
    func_args_lock->lock = malloc(sizeof(pthread_mutex_t)); // Lock necessary for this benchmark.
    pthread_mutex_init(func_args_lock->lock, NULL);

    PassedFunctionMark7* passed_func_lock = malloc(sizeof(PassedFunctionMark7));
    passed_func_lock->function = increment_lock;
    passed_func_lock->func_args = func_args_lock;

    mark7("Time needed for one increase with Lock: ", passed_func_lock);
    pthread_mutex_destroy(func_args_lock->lock);
    free(func_args_lock);
    free(passed_func_lock);
    printf("//---------------------------------------------------------------------------//\n\n");

    // Increase with CAS
    printf("//--------------------------Increase a value with CAS------------------------//\n");
    FunctionArguments* func_args_cas = malloc(sizeof(FunctionArguments));
    func_args_cas->atomic_int_value = malloc(sizeof(atomic_int)); // Value to increase.
    atomic_init(func_args_cas->atomic_int_value, 0);

    PassedFunctionMark7* passed_func_cas = malloc(sizeof(PassedFunctionMark7));
    passed_func_cas->function = increment_cas; // Can swap between atomic_compare_exchange and atomic_fetch_and_add.
    passed_func_cas->func_args = func_args_cas;

    mark7("Time needed for one increase with CAS: ", passed_func_cas);
    free(func_args_cas->atomic_int_value);
    free(func_args_cas);
    free(passed_func_cas);
    printf("//---------------------------------------------------------------------------//\n\n");

    printf("//------------------------Increase a value with add_and_fetch-------------------------//\n");
    FunctionArguments* func_args_aaf = malloc(sizeof(FunctionArguments));
    func_args_aaf->atomic_int_value = malloc(sizeof(atomic_int)); // Value to increase.
    atomic_init(func_args_aaf->atomic_int_value, 0);

    PassedFunctionMark7* passed_func_aaf = malloc(sizeof(PassedFunctionMark7));
    passed_func_aaf->function = increment_fetch_add; // Can swap between atomic_compare_exchange and atomic_fetch_and_add.
    passed_func_aaf->func_args = func_args_aaf;

    mark7("Time needed for one increase with add_and_fetch: ", passed_func_aaf);
    free(func_args_aaf->atomic_int_value);
    free(func_args_aaf);
    free(passed_func_aaf);
    printf("//---------------------------------------------------------------------------//\n\n");

    // Increase with Lock with increase number of threads
    printf("//------------------------Increase a value with many threads using Lock----------------------//\n");
    for(int nb_thread = 1; nb_thread <= 64; nb_thread *= 2){
        FunctionArguments* func_args_lock_thread = malloc(sizeof(FunctionArguments));
        func_args_lock_thread->int_value = 0; // Value to increase.
        func_args_lock_thread->nb_thread = nb_thread; // Number of threads to run the bechmark on.
        func_args_lock_thread->lock = malloc(sizeof(pthread_mutex_t)); // Necessary lock.
        pthread_mutex_init(func_args_lock_thread->lock, NULL);

        PassedFunctionMark7* pass_func_lock_thread = malloc(sizeof(PassedFunctionMark7));
        pass_func_lock_thread->function = increment_lock;
        pass_func_lock_thread->func_args= func_args_lock_thread;

        printf("With %2d thread: ", nb_thread);
        generic_thread_mark7("Time needed for one increase using lock:", pass_func_lock_thread);  
        pthread_mutex_destroy(func_args_lock_thread->lock);
        free(func_args_lock_thread);
        free(pass_func_lock_thread); 
    }
    printf("//-------------------------------------------------------------------------------------------//\n\n");

    // Increase with CAS with increase number of threads
    printf("//------------------------Increase a value with many threads using CAS----------------------//\n");
    for(int nb_thread = 1; nb_thread <= 64; nb_thread *= 2){
        FunctionArguments* func_args_cas_thread = malloc(sizeof(FunctionArguments));
        func_args_cas_thread->atomic_int_value = malloc(sizeof(atomic_int));
        atomic_init(func_args_cas_thread->atomic_int_value, 0);
        func_args_cas_thread->nb_thread = nb_thread; // Number of threads to run the bechmark on.
        PassedFunctionMark7* pass_func_cas_thread = malloc(sizeof(PassedFunctionMark7));
        pass_func_cas_thread->function = increment_cas;
        pass_func_cas_thread->func_args= func_args_cas_thread;

        printf("With %2d thread: ", nb_thread);
        generic_thread_mark7("Time needed for one increase using lock:", pass_func_cas_thread);  
        free(func_args_cas_thread->atomic_int_value);
        free(func_args_cas_thread);
        free(pass_func_cas_thread); 
    }
    printf("//-------------------------------------------------------------------------------------------//\n\n");

    // Increase with fetch_and_add with increase number of threads
    printf("//------------------------Increase a value with many threads using add_and_fetch----------------------//\n");
    for(int nb_thread = 1; nb_thread <= 64; nb_thread *= 2){
        FunctionArguments* func_args_faa_thread = malloc(sizeof(FunctionArguments));
        func_args_faa_thread->atomic_int_value = malloc(sizeof(atomic_int));
        atomic_init(func_args_faa_thread->atomic_int_value, 0);
        func_args_faa_thread->nb_thread = nb_thread; // Number of threads to run the bechmark on.
        PassedFunctionMark7* pass_func_faa_thread = malloc(sizeof(PassedFunctionMark7));
        pass_func_faa_thread->function = increment_fetch_add;
        pass_func_faa_thread->func_args= func_args_faa_thread;

        printf("With %2d thread: ", nb_thread);
        generic_thread_mark7("Time needed for one increase using fetch_and_add:", pass_func_faa_thread);  
        free(func_args_faa_thread->atomic_int_value);
        free(func_args_faa_thread);
        free(pass_func_faa_thread); 
    }
    printf("//-------------------------------------------------------------------------------------------//\n\n");

    // for(int nb_thread = 1; nb_thread <= 64; nb_thread*=2){
    //     PassedFunctionMark7_thread* pass_func_adapt1 = malloc(sizeof(PassedFunctionMark7_thread));
    //     pass_func_adapt1->function = increment_long_lock;
    //     pass_func_adapt1->int_value = nb_thread;
    //     printf("Nb_thread %d -> ", nb_thread);
    //     thread_mark7_inc("Mark7 adapted: increment_long_lock", pass_func_adapt1);

    //     PassedFunctionMark7_thread* pass_func_adapt2 = malloc(sizeof(PassedFunctionMark7_thread));
    //     pass_func_adapt2->function = increment_long_atomic;
    //     pass_func_adapt2->int_value = nb_thread;
    //     printf("Nb_thread %d -> ", nb_thread);
    //     thread_mark7_inc("Mark7 adapted: increment_long_atomic", pass_func_adapt2);

        // PassedFunctionMark7* passed_func_classic = malloc(sizeof(PassedFunctionMark7));
        // passed_func_classic->function = thread_row_char_update;
        // passed_func_classic->int_value = nb_thread;
        // printf("Nb_thread %d -> ", nb_thread);
        // double retries = mark7("Mark7 simple: Modify char with CAS", passed_func_classic);
        // printf("Retries %lf\n", retries);

    // }

    // -----  GOOD TEST DO NOT REMOVE. -----//
    // for(int nb_thread = 1; nb_thread <= 64; nb_thread*=2){
    //     PassedFunctionMark7* passed_func_classic = malloc(sizeof(PassedFunctionMark7));
    //     passed_func_classic->function = thread_row_char_update;
    //     passed_func_classic->int_value = nb_thread;
    //     printf("Nb_thread %d -> ", nb_thread);
    //     double retries = mark7("Mark7 simple: Modify char with CAS", passed_func_classic);
    //     printf("Retries %lf\n", retries);
    // }
    // ------------------------------------ //

    // -----  GOOD TEST DO NOT REMOVE. -----//
    // for(int nb_thread = 1; nb_thread <= 64; nb_thread*=2){
    //     PassedFunctionMark7_thread* pass_func_adapt = malloc(sizeof(PassedFunctionMark7_thread));
    //     pass_func_adapt->function = computation_modify_row_char;
    //     pass_func_adapt->int_value = nb_thread;
    //     printf("Nb_thread %d -> ", nb_thread);
    //     thread_mark7("Mark7 adapted: Modify char with CAS", pass_func_adapt);
    // }
    // ------------------------------------ //

    // printf("%d, %ld, %lld, %lf\n", INT_MAX, ULONG_MAX, LLONG_MAX, DBL_MAX);

	return 0;
	
}
