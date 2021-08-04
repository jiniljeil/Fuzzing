#include <stdio.h>
#include <time.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <string.h> 
#include <string.h> 
#define BASIC_LENGTH 100
#define BASIC_START 32
#define BASIC_RANGE 32
#define BUFF_MAX 1024
#define DEBUG

struct file_info {
    char * path ;
    char * dir_name ; 
};

typedef struct file_info FILE_INFO; 
// generate random string by fuzzer 
char * fuzzer(int max_length, int char_start, int char_range); 
// input the random string in the temporary file.
FILE_INFO* creating_input_files(char* random_string_by_fuzzer) ;
// remove the temporary directory and file 
void remove_files(FILE_INFO * f_info);