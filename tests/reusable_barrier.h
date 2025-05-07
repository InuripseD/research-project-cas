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

/** 
 * @details This function checks if the current thread is the last one to reach the barrier.
 *          If so, it will start and pause the timer depending on the start_or_end parameter.
 * 
 * @param barrier The barrier to check.
 * @param timer The timer to start or pause.
 * @param start_or_end If true, the timer will be started, otherwise it will be paused.
 * 
 * @return True if the current thread is the last one to reach the barrier, false otherwise.
 */
bool is_last_thread(ReusableBarrier* barrier, Timer *timer, bool start_or_end);

#endif // BARRIER_H 