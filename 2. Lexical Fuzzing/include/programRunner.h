#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#define PASS "PASS"
#define FAIL "FAIL"
#define UNRESOLVED "UNRESOLVED" 
#define READ 0
#define WRITE 1

typedef struct subprocess {
    char* standard_out ; 
    char* standard_err ;
    int exit_code; 
    char * outcome; 
} subprocess ;

void program_runner_initialize(char* prog); 
subprocess * run_process(char* input); 
subprocess * programRunner_run(char* input); 
