#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "timer.h"

void play(Timer *t) { 
	// Get squiggles under CLOCK_REALTIME but works fine. TODO: Fix intelisense.
	if(clock_gettime(CLOCK_REALTIME, &t->start)){ 
		perror("Erro: clock_gettime");
		exit(1);
	}
}

void pause_timer(Timer *t) { 
	if(clock_gettime(CLOCK_REALTIME, &t->elapsed)){
		perror("Error: clock_gettime");
		exit(1);
	}
}

long check(Timer *t) {
	return ((t->elapsed.tv_sec - t->start.tv_sec) * 1e9) + (t->elapsed.tv_nsec - t->start.tv_nsec);
}