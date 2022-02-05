#include "fuzzer.h"
#include <string.h>

int main(void){
    test_config_t config ; 
	config_init(&config) ;

    char * source_files[1] = {"../lib/cJSON.c"}; 
    config.num_of_source_files = 1; 

    for(int i = 0 ; i < config.num_of_source_files; i++) {
        config.source_file[i] = source_files[i] ;
    }

    config.input_method = STDIN_INPUT ; 

    strcpy(config.seed_dir,"../seed_dir/Jinil_cJSON_seed_dir"); 
    config.binary_path = "../lib/json_parser"; 
    config.mutation_trial = 1; 

    config.trial = 1000; 
    fuzzer_main(&config);
}