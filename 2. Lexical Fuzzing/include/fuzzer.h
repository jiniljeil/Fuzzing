#include "runner.h"
typedef RESULT (* runner) (char*);
typedef RESULT (* print_runner) (char*);

char* fuzz() ;
RESULT * fuzzer_run(runner runner);
RESULT ** fuzzer_runs(print_runner runner, int trials) ;