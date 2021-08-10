#include "programRunner.h"
#include <time.h>

#define BASIC_MIN_LENGTH 10 
#define BASIC_MAX_LENGTH 100 
#define BASIC_CHAR_START 32 
#define BASIC_CHAR_RANGE 32 
typedef subprocess * (* program_runner) (char*);
typedef subprocess * (* program_print_runner) (char*);

typedef struct setting {
    int min_length ;
    int max_length ;
    int char_start ;
    int char_range ; 
} RANDOM_SETTING; 

void random_fuzzer_initialize(RANDOM_SETTING * set, int min_length, int max_length, int char_start, int char_range) ; 
char* random_fuzz(RANDOM_SETTING * setting) ;
subprocess * random_fuzzer_run(RANDOM_SETTING * setting, program_runner runner);
subprocess ** random_fuzzer_runs(RANDOM_SETTING * setting, program_print_runner runner, int trials) ;
