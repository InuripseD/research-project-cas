#include <stdlib.h>

#include "reusable_barrier.h"

ReusableBarrier* create_barrier(int capacity) {
    ReusableBarrier* barrier = malloc(sizeof(ReusableBarrier));
    barrier->count = 0;
    barrier->capacity = capacity;
    pthread_mutex_init(&barrier->mutex, NULL);
    pthread_cond_init(&barrier->cond, NULL);
    return barrier;
}

void wait_barrier(ReusableBarrier* barrier) {
    pthread_mutex_lock(&barrier->mutex);
    barrier->count++;
    if (barrier->count == barrier->capacity) {
        barrier->count = 0;
        pthread_cond_broadcast(&barrier->cond);
    } else {
        pthread_cond_wait(&barrier->cond, &barrier->mutex);
    }
    pthread_mutex_unlock(&barrier->mutex);
}

void destroy_barrier(ReusableBarrier* barrier) {
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);
    free(barrier);
}