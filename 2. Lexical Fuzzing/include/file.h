#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#define BUFF_MAX 1024

struct file_info {
    char ** path ;
    char * dir_name ; 
    int count ;
};

typedef struct file_info FILE_INFO; 

// create the temporary file
FILE_INFO* create_temp_dir();
// input the random string in the temporary file.
FILE_INFO* creating_input_file(FILE_INFO* info, char* random_string_by_fuzzer) ;
// remove the temporary directory and file 
void remove_files(FILE_INFO * f_info);