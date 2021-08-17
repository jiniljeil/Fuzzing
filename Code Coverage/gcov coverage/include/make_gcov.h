#ifndef MAKE_GCOV
#define MAKE_GCOV 
int coverage_compile(char * program, char * executable_prog); 
int execute_prog(char * executable_prog);
int create_gcov(char * path) ; 
char* remove_the_extension(char * program, int prog_length); 
void make_gcov_file(char * program, int prog_length); 
#endif