#include "include/fuzzer.h"
#include <string.h>

int main(void){
    test_config_t config ; 
	config_init(&config) ;

    char * source_files[1] = {"lib/cgi_decode.c"}; 
    config.num_of_source_files = 1; 

    for(int i = 0 ; i < config.num_of_source_files; i++) {
        config.source_file[i] = source_files[i] ;
    }
    
    config.input_method = CL_ARGUMENTS ;
    config.num_of_cl_arguments = 1; 

    strcpy(config.seed_dir,"seed_dir"); 
    config.binary_path = "lib/cgi_decode"; 
    config.mutation_trial = 3; 

    config.f_min_len = 10; 
    config.f_max_len = 10; 

    config.trial = 10; 
    fuzzer_main(&config);
}