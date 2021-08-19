#ifndef MAKE_GCOV
#define MAKE_GCOV 
int coverage_compile(char * program, char * executable_prog); 
int execute_prog(char * executable_prog, char * arg);
int create_gcov(char * path) ; 
char* remove_the_extension(char * program, int prog_length); 
void make_gcov_file(char * program, int prog_length, char * arg); 
void read_gcov_coverage(char * program, char * arg); 
#endif