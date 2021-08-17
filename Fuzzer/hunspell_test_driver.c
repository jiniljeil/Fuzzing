#include "include/fuzzer.h"
#include <stdio.h> 
#include <stdlib.h> 

int 
test_oracle(int returncode, int trial) 
{
    char error[1024]; 
    
    if(returncode != 0) { 
        get_error(error, 1024, trial) ; 
	perror(error) ; 	
	return returncode ; 
    }

    return 0 ;
}

int main(void){ 

    test_config_t config ;
    config_init(&config) ; 
	
    config.binary_path = "/usr/local/bin/hunspell";  
    config.oracle = test_oracle ;

    fuzzer_main(&config) ;
}
