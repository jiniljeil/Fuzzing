#include "fuzzer.h"

int main(void){
    test_config_t config ; 
	config_init(&config) ;

    config.binary_path = "/bin/cat"; 
    char * options[3] = {"-e"}; 
    config.cmd_args = options; 
    config.num_of_options = 1; 
    fuzzer_init(&config) ; 

  	fuzzer_main();
}