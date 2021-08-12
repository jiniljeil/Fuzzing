#include "fuzzer.h" 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h> 
/*
1. check some conditions
    - binary path validity
    - default values
2. make result directory
*/
test_config_t * config ; 

void
config_init(test_config_t * config_p) 
{
    config_p->f_min_len = MIN_LENGTH ;
    config_p->f_max_len = MAX_LENGTH ;
    config_p->f_char_start = CHAR_START ; 
    config_p->f_char_range = CHAR_RANGE ; 

    config_p->binary_path = NULL ;
    config_p->timeout = 2; 
    config_p->trial = 10;
    config_p->oracle = NULL ; 
    config_p->cmd_args = NULL ; 
}

void
fuzzer_init (test_config_t * config_p)
{
    config = config_p; 

    // check whether the file exists or not.
	if (config != NULL && config->binary_path != NULL && access(config->binary_path, X_OK) != -1 ) {
        if (config->f_min_len < 0) config->f_min_len = MIN_LENGTH; 
        if (config->f_max_len < 0) config->f_max_len = MAX_LENGTH; 

        if (config->f_char_start < 0 || config->f_char_start > 127) config->f_char_start = CHAR_START; 
        if (config->f_char_range < 0 || (config->f_char_start + config->f_char_range) > 127) config->f_char_range = CHAR_RANGE; 

        if (config->f_min_len > config->f_max_len) {
            config->f_max_len = config->f_min_len; 
        }
    }else{
        perror("The path is incorrect!\n"); 
        exit(1); 
    }
}

void 
fuzzer_main ()
{
    for (int i = 0; i < config->trial; i++) {

    	char * input = create_input(config) ; // >> input
    	run(config, input) ; 
    	// oracle(config) ; // file....
    }
}
