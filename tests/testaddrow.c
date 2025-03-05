#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h>

#include "../cas-db/table.h"

struct globalParams {
    Table* table;
    int ready_count; // For barrier synchronization
    int threadsNumber; 
    pthread_mutex_t * mutex; // For barrier synchronization
    pthread_cond_t  * cond; // For barrier synchronization
};

struct threadsParams {
	int threadId;
    struct globalParams * globalParams;    
};


void * threadComputationAddRow (void * params){
	
	struct threadsParams * args = (struct threadsParams *) params;

    struct globalParams * predicat = args -> globalParams;

	pthread_t self = pthread_self();

    Table* table = args->globalParams->table;

    // ALL OF THIS IS ONLY FOR BARRIERE SYNCHRONIZATION
    pthread_mutex_lock(predicat->mutex);
    predicat->ready_count++;
    printf("Thread %d waiting\n", args->threadId);
    while (predicat->ready_count < predicat->threadsNumber) { // Can be an "if" in C.
        pthread_cond_wait(predicat->cond, predicat->mutex);
    }

    pthread_cond_broadcast(predicat->cond);

    pthread_mutex_unlock(predicat->mutex);
    // TILL HERE

    printf("Thread %d starting\n", args->threadId);
    
    for (int i = 0; i < 10; i++){
        add_row(table, '0'+ args->threadId, self);
    }

	pthread_exit(EXIT_SUCCESS);
}


int main(){

	int threadsNumber = 8;

    Table table = create_table();

	pthread_t threads[threadsNumber];
    struct threadsParams params[threadsNumber];
    struct globalParams *globalParams = malloc(sizeof(struct globalParams));

    pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	pthread_cond_t cond;
	pthread_cond_init(&cond, NULL);

    globalParams->table = &table;   
    globalParams->ready_count = 0;
    globalParams->threadsNumber = threadsNumber;
    globalParams->mutex = &mutex;
    globalParams->cond = &cond;

	for (int i = 0; i < threadsNumber; i++){

		params[i].threadId = i;
        params[i].globalParams = globalParams;

		if (pthread_create(&threads[i], NULL, threadComputationAddRow, &params[i]) != 0){
			perror("error thread creation");
			exit(1);
		}

        printf("Thread %d created\n", i);
	
	}

    // join threads
    for (int i = 0; i < threadsNumber; i++){
		pthread_join(threads[i], NULL);
	}

    print_table(&table);
    
    // Check that all ids are different
    for (int i = 0; i < 80; i++){
        for (int j = i+1; j < 80; j++){
            if (atomic_load((table.rows[i])->id) == atomic_load((table.rows[j])->id)){
                printf("Error: id %d is not unique\n", atomic_load((table.rows[i])->id));
            }
        }
    }

    // Free memory
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    free(globalParams);

	return 0;
	
}