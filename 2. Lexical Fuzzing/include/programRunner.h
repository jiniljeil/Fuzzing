#include "runner.h"
#define READ 0
#define WRITE 1
typedef struct subprocess {
    char* output ; 
    int exit_code; 
} subprocess ;

void program_runner_initialize(char* prog); 
subprocess * run_process(char* input); 
char** programRunner_run(char* input); 