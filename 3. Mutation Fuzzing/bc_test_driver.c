#include "include/fuzzer.h"
#include <string.h>

int main(void) {
    test_config_t config; 
    config_init(&config) ;

    char * source_files[10] = {"lib/bc-1.07.1/bc/bc.c", "lib/bc-1.07.1/bc/execute.c", 
     "lib/bc-1.07.1/bc/load.c","lib/bc-1.07.1/bc/main.c", 
    "lib/bc-1.07.1/bc/scan.c", "lib/bc-1.07.1/bc/storage.c", "lib/bc-1.07.1/bc/util.c",
    "lib/bc-1.07.1/bc/warranty.c"}; 

    strcpy(config.working_dir, "lib/bc-1.07.1/bc/"); 
    config.num_of_source_files = 8; 
    for(int i = 0 ; i < config.num_of_source_files; i++) {
        config.source_file[i] = source_files[i] ;
    }

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