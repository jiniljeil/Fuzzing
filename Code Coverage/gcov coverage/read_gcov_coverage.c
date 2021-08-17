#include "include/make_gcov.h"
#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <string.h> 
// #define PRINT_GCOV

void read_gcov_coverage(char * program) {
    
    // executeable program name (remove the extension)
    int ext_point = 0, prog_length = strlen(program); 

    make_gcov_file(program, prog_length) ;

#ifdef PRINT_GCOV
    print_gcovfile() ;
#endif
    char * gcov_filename = (char *)malloc(sizeof(char) * (prog_length + 6)); // .gcov
    sprintf(gcov_filename, "%s.gcov", program) ;
    char * token; 

    FILE * fp = fopen(gcov_filename, "rw"); 

    if ( fp == NULL ) {
        perror("File open failed!\n");
        exit(1) ;  
    }else{
        char * buf = (char *)malloc(sizeof(char) * 256); 
        ssize_t s ; 
        size_t size = 256; 
        while((s = getline(&buf, &size, fp)) > 0) {
            buf[s] = 0x0 ; 
            token = strtok(buf, ":") ;
            int executed_count = atoi(token); 
            if ( executed_count > 0) {
                token = strtok(NULL, ":") ; 
                int executed_statment = atoi(token); 
                printf("(\'%s\', %d)\n", program, executed_statment) ;
            }
        }
        free(buf) ;
    }
    fclose(fp); 
    free(gcov_filename);
}

int main(void) {
    read_gcov_coverage("cgi_decode.c") ;
}