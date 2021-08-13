#include "fuzzer.h"

int main(void){
    test_config_t config ; 
	config_init(&config) ;

    config.binary_path = "/bin/cat"; 

    fuzzer_init(&config) ; 

  	fuzzer_main();
}