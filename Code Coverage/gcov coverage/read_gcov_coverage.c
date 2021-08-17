#include <stdio.h> 
#include <stdlib.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 
// #define PRINT_GCOV

int coverage_compile(char * program, char * executable_prog) {
    int status ;
    int pid = fork(); 

    if ( pid < 0 ) {
        perror("fork failed!\n"); 
        exit(1); 
    }else if( pid == 0 ) {
        char * args[] = {"/usr/bin/gcc","-fprofile-arcs", "-ftest-coverage", "-o", executable_prog, program, 0x0}; 
        execv("/usr/bin/gcc", args); 

        fprintf(stderr, "Execute failed!\n"); 
        exit(1) ;
    }else{
        wait(&status); 
    }
    return status ;
}

int execute_prog(char * executable_prog) { 
    int status ; 

    int pid = fork(); 

    if ( pid < 0 ) {
        perror("fork failed!\n"); 
        exit(1); 
    }else if( pid == 0 ) {
        char * args[] = {executable_prog, 0x0} ;
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
        char * args[] = {"/usr/bin/gcov",path, 0x0} ;
        execv("/usr/bin/gcov", args) ;

        fprintf(stderr, "Execute failed!\n"); 
        exit(1) ;
    }else {
        wait(&status); 
    }
    return status ;
}

void read_gcov_coverage(char * program) {
    char * prog_name = NULL; 
    int ext_point = 0, prog_length = strlen(program); 
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

    char * exec_prog_name = (char *)malloc(sizeof(char) * ext_point) ; 
    sprintf(exec_prog_name, "%s", prog_name); 

    // PATH
    int path_length = strlen(prog_name) + 3 ; 
    char * path = (char*)malloc(sizeof(char) * (path_length) ); 
    sprintf(path, "./%s", prog_name); 
    path[path_length] = 0x0 ; 

    coverage_compile(program, exec_prog_name); 
    execute_prog(path); 
    create_gcov(path) ;

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
        char * buf; 
        ssize_t s ; 
        size_t size = 256; 
        while((s = getline(&buf, &size, fp))) {
            buf[s] = 0x0 ; 
            // printf("%s\n", buf) ;
            token = strtok(buf, ":") ;

            if (token == NULL) break; 
            printf("%s\n", token); // 출력 
        }
    }
    fclose(fp); 

    free(prog_name); 
    free(exec_prog_name); 
    free(path); 
}

int main(void) {
    read_gcov_coverage("cgi_decode.c") ;
}