#include "create_input.h"
#include <stdlib.h> 

int
create_input(test_config_t * config, char * input) 
{
    int string_length = rand() % (config->f_max_len - config->f_min_len + 1) + config->f_min_len; 

    for(int i = 0 ; i < string_length; i++) {
        input[i] = (char) (config->f_char_start + rand() % (config->f_char_range + 1)) ;
    }

    input[string_length] = '\0' ;
    return string_length ;
}