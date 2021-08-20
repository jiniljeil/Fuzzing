#include "include/fuzzer.h"

int main(void){
    test_config_t config ; 
	config_init(&config) ;

    config.source_file = "lib/cgi_decode.c"; 
    config.is_source = true ; 

    config.input_method = CL_ARGUMENTS ;
    config.num_of_cl_arguments = 1; 


    config.trial = 1;
    config.f_min_len = 10; 
    config.f_max_len = 10; 
    
    fuzzer_main(&config);

    
}