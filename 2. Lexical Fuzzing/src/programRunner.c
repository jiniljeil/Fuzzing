#include "../include/programRunner.h"
#include <unistd.h>
#define BUFF_SIZE 1024
int pipes[2] ;
char* program; 

void program_runner_initialize(char* prog) { 
    program = (char*)malloc(sizeof(char) * (strlen(prog) + 1)); 
    strcpy(program, prog);
}

subprocess * run_process(char* input) {
    subprocess * subproc = NULL;

    if(pipe(pipes) < 0) {
        perror("pipe error!\n");
        exit(1); 
    }

    int pid = fork(); 

    if(pid < 0) {
        perror("fork failed!\n"); 
        exit(1) ;
    }else if (pid == 0) {
        /* child */
        dup2(pipes[0], 0); 
        close(pipes[0]);

        dup2(pipes[WRITE], 1);
        dup2(pipes[WRITE], 2); 

        execlp(program, program, input, NULL); 
        printf("Execute error!\n") ;
        exit(1); 
    }else {
        /* parent */
        wait(&(subproc->exit_code)); 
        close(pipes[WRITE]); 

        ssize_t s ; 
        int n = 1; 
        subproc = (subprocess*)malloc(sizeof(subprocess)); 
        subproc->output = (char*)malloc(sizeof(char) * BUFF_SIZE);

        while( (s = read(pipes[READ], subproc->output, BUFF_SIZE - 1)) > 0) {
            if (s == BUFF_SIZE) {
                subproc->output = (char*)realloc(subproc->output, (++n) * BUFF_SIZE); 
            }else{
                subproc->output[s] = '\0'; 
            }
        }
    }

    return subproc; 
}

char** programRunner_run(char* input) { 
    if (input == NULL) input = ""; 
    char** ret = (char**)malloc(sizeof(char) * 2); 
    ret[0] = (char*)malloc(sizeof(char) * (strlen(input) + 1)) ;

    strcpy(ret[0], input) ;

    subprocess * subprocess_result = run_process(input) ;

    if( subprocess_result->exit_code == 0 ) {
        ret[1] = (char*)malloc(sizeof(char) * (strlen(PASS) + 1)); 
        strcpy(ret[1], PASS) ;
    }else if( subprocess_result->exit_code < 0 ) {
        ret[1] = (char*)malloc(sizeof(char) * (strlen(FAIL) + 1)); 
        strcpy(ret[1], FAIL) ;
    }else {
        ret[1] = (char*)malloc(sizeof(char) * (strlen(UNRESOLVED) + 1)); 
        strcpy(ret[2], UNRESOLVED) ;
    }

    printf("RESULT: %s\n", subprocess_result->output); 

    return ret ;
}