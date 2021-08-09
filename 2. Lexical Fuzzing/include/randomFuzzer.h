#include "runner.h"
#include <time.h>
#define BASIC_MIN_LENGTH 10 
#define BASIC_MAX_LENGTH 100 
#define BASIC_CHAR_START 32 
#define BASIC_CHAR_RANGE 32 
typedef RESULT * (* runner) (char*);
typedef RESULT * (* print_runner) (char*);

typedef struct setting {
    int min_length ;
    int max_length ;
    int char_start ;
    int char_range ; 
} RANDOM_SETTING; 

void random_fuzzer_initialize(RANDOM_SETTING * set, int min_length, int max_length, int char_start, int char_range) ; 
char* random_fuzz(RANDOM_SETTING * setting) ;
RESULT * random_fuzzer_run(RANDOM_SETTING * setting, runner runner);
RESULT ** random_fuzzer_runs(RANDOM_SETTING * setting, print_runner runner, int trials) ;