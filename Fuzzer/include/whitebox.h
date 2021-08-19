#ifndef MAKE_GCOV
#define MAKE_GCOV 

typedef struct coverset {
    int * coverage_set ;
    int num_of_total_coverage ; 
    char * union_coverage_set ;
} coverset_t; 

int coverage_compile(char * program, char * executable_prog); 
int execute_prog(char * executable_prog, char * arg);
int create_gcov(char * path) ; 
char* remove_the_extension(char * program, int prog_length); 
void make_gcov_file(char * program, int prog_length, char * arg); 
char * remove_slash(char * source_file, int length);
int num_of_lines(char * program); 
int read_gcov_coverage(char * program, coverset_t * coverset, int trial); 
void remove_the_gcda_file(char * c_file); 
#endif