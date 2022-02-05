#include "../include/whitebox.h"
#include <stdlib.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <string.h> 
#include <stdio.h>
#define REMOVE_EXECFILE
#define PATH_MAX 4096
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
        char * args[] = {"/usr/bin/gcov", "-b", "-c", path, 0x0} ;
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

unsigned short sdbm_hashing(char *str) {
    unsigned short hash = 0;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

int read_gcov_coverage(char * gcov_filename, coverset_t * coverset, int trial, unsigned short * path_id) {
    
    // executeable program name (remove the extension)
    int num_of_lines = 0; 
    int ext_point = 0; 
    // int prog_length = strlen(program); 
    char tmp_branch_coverage_set[10000] ; 
    memset(tmp_branch_coverage_set, '0', sizeof(tmp_branch_coverage_set)); 
    
    char * token; 
    char * branch_token; 
    FILE * fp = fopen(gcov_filename, "rb"); 

    if ( fp == NULL ) {
        perror("File open failed!\n");
        exit(1) ;  
    }else{
        char * buf = NULL; 
        ssize_t s ; 
        size_t size = 0; 
        int num_of_branch_cover = 1 ; 

        while(!feof(fp)){
            if((s = getline(&buf, &size, fp)) > 0) {
                // buf[s] = 0x0 ; 
                if (!strncmp("branch", buf, 6)) {
                    if (strstr(buf, "taken") != NULL) {
                        branch_token = strtok(buf, " "); 
                        for (int k = 0 ; k < 3; k++) branch_token = strtok(NULL, " ");
                        int branch_num = 0 ; 
                        if (branch_token != NULL) branch_num = atoi(branch_token); 

                        if ( branch_num > 0 ) {
                            tmp_branch_coverage_set[num_of_branch_cover] = '1'; 
                            if (coverset->union_branch_coverage_set[num_of_branch_cover] != '1') {
                                coverset->union_branch_coverage_set[num_of_branch_cover] = '1'; 
                            }
                        }
                    }
                    num_of_branch_cover++;
                }else{
                    token = strtok(buf, ":") ;
                    
                    int executed_count = atoi(token); 
                    
                    if ( executed_count > 0) {
                        token = strtok(NULL, ":") ; 
                        int executed_statment;
                        if (token != NULL) executed_statment = atoi(token); 
                        // coverage
                        
                        if (coverset->union_coverage_set[executed_statment] != '1'){
                            coverset->union_coverage_set[executed_statment] = '1'; 
                        }
                        num_of_lines++;
                    }
                }
            }
        }
        free(buf) ;
        fclose(fp); 
        
        *path_id = sdbm_hashing(tmp_branch_coverage_set);  
    }
    // coverage
    
    coverset->coverage_set[trial] = num_of_lines ; 
    
    return num_of_lines ;
}

char * remove_slash(char * source_file, int length) { 
    char * c_file = NULL; 

    int no_slash = 1 ; 
    for(int i = length ; i >= 0 ;i--) {
        if (source_file[i] == '/') {  
            c_file = (char *) malloc(sizeof(char) * (length - i + 1)); 
            for(int j = 0 ; j < length - i; j++) {
                c_file[j] =  source_file[i + j + 1] ;
            }
            c_file[length - i] = 0x0 ; 
            no_slash = 0;
            break; 
        }
    }

    if( no_slash ) {
        c_file = (char *)malloc(sizeof(char) * (strlen(source_file) + 1)); 
        strcpy(c_file, source_file); 
    } 
    c_file[strlen(source_file)] = 0x0; 
    return c_file; 
}


void remove_the_gcda_file(char * c_file) {
    int length = strlen(c_file); 

    char * gcda_file = (char *)malloc(sizeof(char) * (length + 4)) ; 
    char * gcno_file = (char *)malloc(sizeof(char) * (length + 4)) ; 

    strncpy(gcda_file, c_file, length -1);
    gcda_file[length - 1] = 0x0 ;
    strcat(gcda_file, "gcda"); 

    if( access(gcda_file, F_OK) != -1 ) {
        if (remove(gcda_file) != 0) {
            free(gcda_file) ; 
            perror("Error: gcda file remove failed!\n"); 
            return ;
        }
    }
    
    free(gcda_file); 
}


int num_of_total_lines(char * program) {

    FILE * fp = fopen(program, "rb"); 

    int num = 0 ; 
    char *line = NULL; 
    size_t size = 0; 
    ssize_t len = 0; 

    if( fp == NULL) {
        perror("Error: file open failed!\n"); 
        return -1; 
    }

    while(!feof(fp)) {
        if ((len = getline(&line, &size, fp)) != -1) { 
            num++;
        }
    }
    free(line); 
    fclose(fp); 
    return num; 
}

int num_of_uncovered_lines(char * program) {
    FILE * fp = fopen(program, "rb") ;

    if (fp == NULL) {
        perror("Error: file open failed!\n"); 
        return -1; 
    }
    int num = 0 ; 
    char *line = NULL; 
    size_t size = 0; 
    ssize_t len = 0; 
    char * token ; 

    while(!feof(fp)) {
        if ((len = getline(&line, &size, fp)) != -1) { 
            line[len] = 0x0; 
            token = strtok(line, ":"); 
            if (strstr(token, "#####") != NULL) {
                num++;
            }
        }
    }
    free(line); 
    fclose(fp); 
    
    return num ;
}

int num_of_uncovered_branch_lines(char * program) {
    FILE * fp = fopen(program, "rb"); 
    if (fp == NULL) {
        perror("Error: file open failed!\n"); 
        return -1; 
    }
    int num = 0 ; 
    char *line = NULL; 
    size_t size = 0; 
    ssize_t len = 0; 
    char * token ; 

    while(!feof(fp)) {
        if ((len = getline(&line, &size, fp)) != -1) { 
            line[len] = 0x0; 
            if(!strncmp("branch", line, 6)) {
                num++; 
            }
        }
    }
    free(line); 
    fclose(fp); 
    
    return num ;
}