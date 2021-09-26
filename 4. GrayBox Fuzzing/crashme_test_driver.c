#include "include/fuzzer.h"
#include <string.h>

int main(void){
    test_config_t config ; 
	config_init(&config) ;

    // char * source_file = "lib/cgi_decode.c"; 
    char * source_files[1] = {"lib/crashme.c"}; 
    config.num_of_source_files = 1; 
    for(int i = 0 ; i < config.num_of_source_files; i++) {
        config.source_file[i] = source_files[i] ;
    }

    config.input_method = STDIN_INPUT ;

    strcpy(config.seed_dir,"crashme_seed_dir"); 
    config.binary_path = "lib/crashme"; 
    config.mutation_trial = 3; 

    config.trial = 10; 
    fuzzer_main(&config);
}