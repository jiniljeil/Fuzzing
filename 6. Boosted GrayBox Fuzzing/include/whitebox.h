#ifndef MAKE_GCOV
#define MAKE_GCOV 

typedef struct coverset {
    int * coverage_set ;
    int num_of_max_coverage ; 
    int num_of_total_coverage ; 
    int num_of_total_branch_coverage; 
    char union_coverage_set[10000] ;
    char union_branch_coverage_set[10000]; 

    char hash_table[65537] ; 
} coverset_t; 

unsigned short sdbm_hashing(char *str); 
int coverage_compile(char * program, char * executable_prog); 
int execute_prog(char * executable_prog, char * arg);
int create_gcov(char * path) ; 
char* remove_the_extension(char * program, int prog_length); 
void make_gcov_file(char * program, int prog_length, char * arg); 
char * remove_slash(char * source_file, int length);
int num_of_total_lines(char * program); 
int num_of_uncovered_lines(char * program); 
int num_of_uncovered_branch_lines(char * program); 
int read_gcov_coverage(char * gcov_filename, coverset_t * coverset, int trial, unsigned short * path_id);
void remove_the_gcda_file(char * c_file); 
#endif