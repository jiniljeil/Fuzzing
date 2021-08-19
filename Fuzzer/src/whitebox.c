#include "../include/whitebox.h"
#include <stdlib.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <string.h> 
#include <stdio.h>
#define REMOVE_EXECFILE

int coverage_compile(char * program, char * executable_prog) {
    int status ;
    int pid = fork(); 

    if ( pid < 0 ) {
        perror("fork failed!\n"); 
        exit(1); 
    }else if( pid == 0 ) {
        char * args[] = {"/usr/bin/gcc","--coverage", "-o", executable_prog, program, 0x0}; 
        execv("/usr/bin/gcc", args); 

        fprintf(stderr, "Execute failed!\n"); 
        exit(1) ;
    }else{
        wait(&status); 
    }
    return status ;
}

int execute_prog(char * executable_prog, char * arg) { 
    int status ; 

    int pid = fork(); 

    if ( pid < 0 ) {
        perror("fork failed!\n"); 
        exit(1); 
    }else if( pid == 0 ) {
        char * args[] = {executable_prog, arg, 0x0} ;
        execv(executable_prog, args) ;

        fprintf(stderr, "Execute failed!\n"); 
        exit(1) ;
    }else {
        wait(&status); 
    }
    return status ;
}

int create_gcov(char * path) {
    int status ; 

    int pid = fork(); 

    if ( pid < 0 ) {
        perror("fork failed!\n"); 
        exit(1); 
    }else if( pid == 0 ) {
        char * args[] = {"/usr/bin/gcov", path, 0x0} ;
        execv("/usr/bin/gcov", args) ;

        fprintf(stderr, "Execute failed!\n"); 
        exit(1) ;
    }else {
        wait(&status); 
    }
    return status ;
}

char* remove_the_extension(char * program, int prog_length){
    int ext_point = 0 ; 
    char * prog_name ; 
    for ( ext_point = prog_length ; ext_point >= 0; ext_point--) {
        if (program[ext_point] == '.') {
            prog_name = (char*)malloc(sizeof(char) * (ext_point + 1)) ;

            for(int i = 0 ; i < ext_point; i++) {
                prog_name[i] = program[i]; 
            }
            prog_name[ext_point] = 0x0; 
            break; 
        }
    }
    return prog_name ; 
}

void make_gcov_file(char * program, int prog_length, char * arg) {
    char * prog_name = remove_the_extension(program, prog_length) ;

    // PATH
    int path_length = strlen(prog_name) + 3 ; 
    char * path = (char*)malloc(sizeof(char) * (path_length) ); 
    sprintf(path, "./%s", prog_name); 
    path[path_length] = 0x0 ; 

    if ( coverage_compile(program, prog_name) != 0 ) { 
        perror("Error: GCC compile failed!\n"); 
        exit(1) ; 
    }
    if ( execute_prog(path, arg) != 0 ) {
        perror("Error: program execution failed!\n"); 
        exit(1); 
    }
    if ( create_gcov(path) != 0 ) { 
        perror("Error: GCOV compile failed!\n"); 
        exit(1); 
    } 

#ifdef REMOVE_EXECFILE 
    if( remove(prog_name) != 0) {
        fprintf(stderr, "Error: unable to delete the file\n"); 
    }
#endif 
    free(prog_name); 
    free(path); 
}

void read_gcov_coverage(char * program, char * arg) {
    
    // executeable program name (remove the extension)
    // "Send+mail+to+me%40fuzzingbook.org"
    int ext_point = 0, prog_length = strlen(program);  
    make_gcov_file(program, prog_length, arg) ;

    int gcov_filename_length = prog_length + 6 ; 
    char * gcov_filename = (char *)malloc(sizeof(char) * (gcov_filename_length)); // .gcov
    sprintf(gcov_filename, "%s.gcov", program) ;
    gcov_filename[gcov_filename_length] = 0x0 ;

    char * token; 

    FILE * fp = fopen(gcov_filename, "rb"); 

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