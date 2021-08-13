#include "config.h"
#include "create_input.h"
#include "oracle.h"
#include "file.h"
void fuzzer_init (test_config_t * config_p); 
void config_init(test_config_t * config_p); 
void config_copy(test_config_t * config_p);
void fuzzer_main () ;
int run(char * input, int length, files_info_t * files_info);