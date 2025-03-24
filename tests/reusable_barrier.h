#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>
#include <stdbool.h>

#include "../benchmarks/timer.h"


/**
 * Nothing much to say here, this the most simple implementation of a barrier.
 * With a twist that the last thread to reach the barrier will reset it.
 * So it can be reused.
 */
typedef struct {
    int count;
    int capacity;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} ReusableBarrier;

ReusableBarrier* create_barrier(int capacity);

void wait_barrier(ReusableBarrier* barrier);

void destroy_barrier(ReusableBarrier* barrier);

bool is_last_thread(ReusableBarrier* barrier, Timer *timer, bool start_or_end);

#endif // BARRIER_H 