#include "create_input.h"
#include <stdlib.h> 

char * 
create_input(test_config_t * config) 
{
    int string_length = rand() % (config->f_max_len - config->f_min_len + 1) + config->f_min_len; 
    char * random_string = (char *)malloc(sizeof(char) * (string_length + 1)) ;

    for(int i = 0 ; i < string_length; i++) {
        random_string[i] = (char) (config->f_char_start + rand() % (config->f_char_range + 1)) ;
    }

    random_string[string_length] = '\0' ;
    return random_string ;
}