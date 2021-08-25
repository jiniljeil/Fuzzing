#include "include/fuzzer.h"
#include <string.h> 
int main(void){
    test_config_t config ; 
	config_init(&config) ;

    config.is_source = true; 
    config.source_file = "lib/troff_bug_detect.c"; 
    // config.binary_path = "./troff_bug_detect"; 

    config.input_method = STDIN_INPUT ;
    config.f_char_start = 0 ; 
    config.f_char_range = 255; 

    strcpy(config.seed_dir,"seed_dir"); 
    config.mutation_trial = 3; 

    config.trial = 10;
    config.f_min_len = 10; 
    config.f_max_len = 100; 

    fuzzer_main(&config);
}