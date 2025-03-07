#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>

typedef struct {
    int count;
    int capacity;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} ReusableBarrier;

ReusableBarrier* create_barrier(int capacity);

void wait_barrier(ReusableBarrier* barrier);

void destroy_barrier(ReusableBarrier* barrier);

#endif // BARRIER_H 