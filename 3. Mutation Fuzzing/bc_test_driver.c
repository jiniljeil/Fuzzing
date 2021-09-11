#include "include/fuzzer.h"
#include <string.h>

int main(void) {
    test_config_t config; 
    config_init(&config) ;

    config.source_file = "lib/bc-1.07.1/bc/main.c"; 
    config.is_source = true ; 
    config.is_makefile = true; 
    config.binary_path = "lib/bc-1.07.1/bc/bc"; 

    config.input_method = CL_ARGUMENTS ;
    config.num_of_cl_arguments = 1; 

    strcpy(config.seed_dir,"seed_dir"); 
    config.mutation_trial = 3; 

    config.f_min_len = 10; 
    config.f_max_len = 10; 

    config.trial = 10; 
    fuzzer_main(&config);
    return 0; 
}