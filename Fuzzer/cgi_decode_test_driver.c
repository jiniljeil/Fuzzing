#include "include/fuzzer.h"

int main(void){
    test_config_t config ; 
	config_init(&config) ;

    config.source_file = "lib/cgi_decode.c"; 
    config.is_source = true ; 

    config.trial = 10;
    config.f_min_len = 10; 
    config.f_max_len = 100; 

    fuzzer_main(&config);
}