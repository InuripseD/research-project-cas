#ifndef TIMER_H
#define TIMER_H

#include <time.h>

typedef struct {
    struct timespec start, elapsed;
} Timer;

/** 
 * @return The time elapsed between the start and the call af this function.
 * 
 * @note As both seconds and nanosecods are stored in longs, 
 *       seconds has to be multiplied by 1e9 to be added to nanoseconds.
 */
long check(Timer *t);

/** 
 * @brief Starts the timer.
 */
void play(Timer *t);

#endif // TIMER_H