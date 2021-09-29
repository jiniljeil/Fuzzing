#include "include/fuzzer.h"
#include <string.h>

int main(void){
    test_config_t config ; 
	config_init(&config) ;

    char * source_files[1] = {"lib/cJSON.c"}; 
    config.num_of_source_files = 1; 

    for(int i = 0 ; i < config.num_of_source_files; i++) {
        config.source_file[i] = source_files[i] ;
    }

    config.input_method = CL_ARGUMENTS ;
    config.num_of_cl_arguments = 1; 

    // strcpy(config.seed_dir,"cJSON_seed_dir"); 
    config.binary_path = "lib/cJSON_program"; 
    config.mutation_trial = 3; 

    config.trial = 10000; 
    fuzzer_main(&config);
}