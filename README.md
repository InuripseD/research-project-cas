# research-project-cas
This repository contains code used to benchmark compare and swap on minimalist databases.


# How to read
To understant this repository I recommend to start reading [row.h](./cas-db/row.h) and [table.h](./cas-db/table.h). It is explained how is the minimalist "database" defined. (For now there isn't a database but only a table.) <br>

In [row.c](./cas-db/row.c) and [table.c](./cas-db/table.c), you can see the actual implementation with the use of the [stdatomic library](https://en.cppreference.com/w/c/header/stdatomic) features. <br>

Then a quick look at the tests can be interesting but they are not many for now. The only point to mention is the use of [pthread library](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html) and not C standar library as I am more used to Posix ones.

Lastly for now (as the server is not done yet), the benchmark section with a C translation/adaptation of the [mark7](./benchmarks/mark7.c) benchmarking function by Peter Sestoft[[1]](#1). And [Timer](./benchmarks/timer.h) stuct using [timespec](https://en.cppreference.com/w/c/chrono/timespec) with [clock_gettime()](https://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_gettime.html) instead of [timespec_get()](https://en.cppreference.com/w/c/chrono/timespec_get) as it might allow more flexibility in recording the time for futur experiments.


# How to run
You will need gcc compiler C11 at least.
This is working on my machine with Ubuntu 24.04.2 LTS. <br>
Simply run ```make``` from the root folder. <br>
Then to run each mains run: <br>
```./bin/cas_db_main``` <br>
```./bin/tests``` <br>
```./bin/benchmarks``` <br>

## References
<a id="1">[1]</a> 
Sestoft, Peter,
Microbenchmarks in Java and C\#,
Lecture Notes, September 2013.