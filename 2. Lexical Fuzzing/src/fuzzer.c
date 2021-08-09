#include "../include/fuzzer.h"

char* fuzz() {
    return ""; 
}

RESULT * fuzzer_run(runner runner) {
    return runner(fuzz());
}

RESULT ** fuzzer_runs(print_runner runner, int trials) { 
    RESULT ** result_list = (RESULT**)malloc(sizeof(RESULT*) * trials); 

    for(int i = 0 ; i < trials; i++) {
        result_list[i] = fuzzer_run(runner); 
    }

    return result_list;            
}   

