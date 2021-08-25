#include "include/fuzzer.h"
#include <string.h>
#include <assert.h>
#include <stdio.h> 
#include <stdlib.h> 

#define TEST_SIZE 1024
int 
test_oracle(int returncode, int trial ) 
{
    char input[TEST_SIZE], output[TEST_SIZE], error[TEST_SIZE];  
    int result = 0 ;

    if (returncode != 0) {
        get_error(error, TEST_SIZE, trial);
        perror(error); 
        return returncode; 
    }
    
    int input_size = get_input(input, TEST_SIZE, trial); 
    int output_size = get_output(output, TEST_SIZE, trial); 

    assert(input_size == output_size && "The length of input is different from the length of the output.\n") ; 
    assert(memcmp(input, output, input_size) == 0 && "The input generated by fuzzer is different from the output.\n");

    return result ;
}

int main(void) {
    
    test_config_t config ; 
	config_init(&config) ;

    strcpy(config.seed_dir, "seed_dir"); 
    config.mutation_trial = 3; 

    config.input_method = STDIN_INPUT ; 


    config.binary_path = "/bin/cat"; 
    char * options[3] = {"-e"}; 

    config.cmd_args = options; 
    config.num_of_options = 1; 
    config.oracle = test_oracle; 

    fuzzer_main(&config);
}