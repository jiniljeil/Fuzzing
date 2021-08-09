#include "../include/programRunner.h"
#include <unistd.h>
#define BUFF_SIZE 1024

int stdin_pipes[2]; 
int stdout_pipes[2];
int stderr_pipes[2]; 
char* program; 

void program_runner_initialize(char* prog) { 
    program = (char*)malloc(sizeof(char) * (strlen(prog) + 1)); 
    strcpy(program, prog);
}

subprocess * run_process(char* input) {
    subprocess * subproc = NULL;

    if(pipe(stdin_pipes) < 0) {
        perror("pipe error!\n");
        exit(1); 
    }   

    if(pipe(stdout_pipes) < 0) {
        perror("pipe error!\n");
        exit(1); 
    }  

    if(pipe(stderr_pipes) < 0) {
        perror("pipe error!\n");
        exit(1); 
    }  

    int pid = fork(); 

    if(pid < 0) {
        perror("fork failed!\n"); 
        exit(1) ;
    }else if (pid == 0) {
        /* child */
        close(stdout_pipes[READ]); 
        close(stderr_pipes[READ]); 

        write(stdin_pipes[WRITE], input, strlen(input)); 
        dup2(stdin_pipes[READ], 0);

        close(stdin_pipes[READ]); 
        close(stdin_pipes[WRITE]); 
        
        dup2(stdout_pipes[WRITE], 1);
        dup2(stderr_pipes[WRITE], 2); 

        execlp(program, program, NULL); 
        printf("Execute error!\n") ;
        exit(1); 
    }else {
        /* parent */
        close(stdin_pipes[READ]); 
        close(stdin_pipes[WRITE]); 
        close(stdout_pipes[WRITE]); 
        close(stderr_pipes[WRITE]); 

        wait(&(subproc->exit_code)); 

        ssize_t s ; 
        int n = 1; 
        subproc = (subprocess*)malloc(sizeof(subprocess)); 
        subproc->standard_out = (char*)malloc(sizeof(char) * BUFF_SIZE);
        subproc->standard_err = (char*)malloc(sizeof(char) * BUFF_SIZE);

        while( (s = read(stdout_pipes[READ], subproc->standard_out, BUFF_SIZE - 1)) > 0) {
            if (s == BUFF_SIZE) {
                subproc->standard_out = (char*)realloc(subproc->standard_out, (++n) * BUFF_SIZE); 
            }else{
                subproc->standard_out[s] = '\0'; 
            }
        }
        
        n = 1; 
        while( (s = read(stderr_pipes[READ],  subproc->standard_err, BUFF_SIZE - 1)) > 0) {
            if (s == BUFF_SIZE) {
                subproc->standard_err = (char*)realloc(subproc->standard_err, (++n) * BUFF_SIZE); 
            }else{
                subproc->standard_err[s] = '\0'; 
            }
        }
        close(stdout_pipes[READ]); 
        close(stderr_pipes[READ]); 
    }

    return subproc; 
}

RESULT * programRunner_run(char* input) { 
    if (input == NULL) input = ""; 
    RESULT * ret = (RESULT*)malloc(sizeof(RESULT));  
    ret->input = (char*)malloc(sizeof(char) * (strlen(input) + 1)) ;

    strcpy(ret->input, input) ;

    subprocess * subprocess_result = run_process(input) ;

    if( subprocess_result->exit_code == 0 ) {
        ret->outcome = (char*)malloc(sizeof(char) * (strlen(PASS) + 1)); 
        strcpy(ret->outcome, PASS) ;
    }else if( subprocess_result->exit_code < 0 ) {
        ret->outcome = (char*)malloc(sizeof(char) * (strlen(FAIL) + 1)); 
        strcpy(ret->outcome, FAIL) ;
    }else {
        ret->outcome = (char*)malloc(sizeof(char) * (strlen(UNRESOLVED) + 1)); 
        strcpy(ret->outcome, UNRESOLVED) ;
    }

    printf("RESULT: %s\n", subprocess_result->standard_out); 
    printf("ERROR: %s\n", (strlen(subprocess_result->standard_err) == 0) ? "NOTHING" : subprocess_result->standard_err);

    return ret ;
}