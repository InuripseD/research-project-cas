#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "benchmark.h"
#include "../cas-db/table.h"
#include "timer.h"

int main(){

    mark7("Modify char with CAS", updating_row_char);

	return 0;
	
}