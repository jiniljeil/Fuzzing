#ifndef FUZZER 
#define FUZZER 

#include "config.h"
#include "file.h"
#define true 1 
#define false 0

typedef struct result { 
    int returncode; 
    char * test_result; 
    double exec_time ; 
} result_t ; 

// 각 인풋에 대한 라인 커버 갯수 (카운트의 배열)
// 전체 덮어씌인 커버 갯수 
// UNION 라인 커버 (배열)

void fuzzer_init (test_config_t * config_p); 
void config_init(test_config_t * config_p); 
void config_copy(test_config_t * config_p);
void fuzzer_main (test_config_t * config) ;
void check_num_of_argument(test_config_t * config_p);
int run(char * input, int length, files_info_t * files_info, int num);
void print_result(files_info_t * files_info, result_t * result, int num) ;
void test_oracle_run(result_t * result, int returncode, int trial); 
void config_free() ;
void timeout_handler(const int signal); 
int get_input(char * input, int len, int trial) ;
int get_output(char * output, int len, int trial) ;
int get_error(char * error, int len, int trial) ;
void fuzzer_summary(result_t * results) ;
#endif