#ifndef BENCHMARK_H
#define BENCHMARK_H

/** 
 * @brief Function called by mark7 to calculate the time for a CAS operation on a char of a row of a table.
 * 
 * Only works for one thread for now.
 */
double updating_row_char(int count);

/** 
 * @brief C translation of the Java benchmarking function mark7 by Peter Sestoft.
 * 
 * @article{sestoft2013microbenchmarks,
 *   title={Microbenchmarks in Java and C\#},
 *   author={Sestoft, Peter},
 *   journal={Lecture Notes, September},
 *   year={2013}
 * }
 */ 
double mark7(char *msg, double (*function)(int));


#endif // BENCHMARK_H