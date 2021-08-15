#ifndef FUZZER 
#define FUZZER 

#include "config.h"
#include "create_input.h"
#include "file.h"

typedef struct result { 
    int returncode; 
    char * test_result; 
} result_t ; 

void fuzzer_init (test_config_t * config_p); 
void config_init(test_config_t * config_p); 
void config_copy(test_config_t * config_p);
void fuzzer_main () ;
void check_num_of_argument(test_config_t * config_p);
int run(char * input, int length, files_info_t * files_info, int num);
void print_result(files_info_t * files_info, result_t * result, int num) ;
void test_oracle_run(result_t * result, int returncode, int trial); 
void config_free() ;
void timout_handler(const int signal); 
int get_input(char * input, int len, int trial) ;
int get_output(char * output, int len, int trial) ;
int get_error(char * error, int len, int trial) ;

#endif