#include "include/fuzzer.h"

int main(void){
    test_config_t config ; 
	config_init(&config) ;

    config.is_source = true; 
    config.source_file = "lib/troff_bug_detect.c"; 
    // config.binary_path = "./troff_bug_detect"; 
    config.f_char_start = 0 ; 
    config.f_char_range = 255; 

    config.trial = 10;
    config.f_min_len = 10; 
    config.f_max_len = 5000; 

    fuzzer_main(&config);
}