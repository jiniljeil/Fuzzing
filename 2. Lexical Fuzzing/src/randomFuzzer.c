#include "../include/randomFuzzer.h"

void random_fuzzer_initialize(RANDOM_SETTING * setting, int min_length, int max_length, int char_start, int char_range) {
    setting->min_length = min_length; 
    setting->max_length = max_length; 
    setting->char_start = char_start; 
    setting->char_range = char_range; 
}

char* random_fuzz(RANDOM_SETTING * setting) {
    int string_length = rand() % (setting->max_length - setting->min_length + 1) + setting->min_length; 
    char * random_string = (char *)malloc(sizeof(char) * (string_length + 1)) ;

    for(int i = 0 ; i < string_length; i++) {
        random_string[i] = (char) (setting->char_start + rand() % (setting->char_range + 1)) ;
    }
    random_string[string_length] = '\0' ;
    return random_string ;
}

RESULT * fuzzer_run(RANDOM_SETTING * setting, runner runner) {
    return runner(random_fuzz(setting));
}

RESULT ** fuzzer_runs(RANDOM_SETTING * setting, print_runner runner, int trials) { 
    RESULT ** result_list = (RESULT**)malloc(sizeof(RESULT*) * trials); 

    for(int i = 0 ; i < trials; i++) {
        result_list[i] = fuzzer_run(setting, runner); 
    }

    return result_list;            
}   