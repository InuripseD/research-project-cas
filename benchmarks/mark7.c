#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "timer.h"

double mark7(char *msg, double (*function)(int)) {

	// n can also be 8 based on the reference paper of this project.
	int n = 10; 

	// Number of iterations to make sure we run it enough times for the measurement to be accurate.
	int count = 1; 
	int total_count = 0;

	// For now dummy is useless, would like to set it to "CAS number of retries".
	double dummy = 0.0;

	 // It is already in nanoseconds so we use long.
	long running_time = 0;

	// For the mean and standard deviation.
	double st = 0.0, sst = 0.0; 

	do { 
		count *= 2;
		st = sst = 0.0;
		for(int j = 0; j < n; j++) {
			Timer timer;
			play(&timer); // Start timer here.
			for (int i=0; i<count; i++) {
				dummy += (*function)(count);
			}
			running_time = check(&timer); // End timer here.
			double time = (double)running_time / (double)count;
			st += time; 
			sst += time * time;
			total_count += count;
		}
	} while (running_time < 250000000 && count < INT_MAX/2);
	double mean = st / n; 
	double sdev = sqrt((sst - mean * mean * n) / (n - 1));
	printf("%-25s %9.1lf ns %9.2lf %10d\n", msg, mean, sdev, count);
	return dummy / total_count;
}