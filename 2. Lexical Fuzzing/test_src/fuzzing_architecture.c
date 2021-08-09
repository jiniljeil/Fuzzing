#include "../include/runner.h" 
#include "../include/programRunner.h"


void print_runner_test() {
    char** print_runner_result = PrintRunner_run("Some input"); 

    printf("%s\n", print_runner_result[0]); 
    printf("%s\n", print_runner_result[1]); 

    for(int i = 0 ; i < 2 ; i++) {
        free(print_runner_result[i]); 
    }
    free(print_runner_result); 
}

void program_runner_test() { 
    program_runner_initialize("cat"); 
    char ** program_runner_result = programRunner_run("hello"); 
    printf("%s\n", program_runner_result[1]); 
    
    for(int i = 0 ; i < 2 ;i++) {
        free(program_runner_result[i]) ;
    }
    free(program_runner_result); 
}

int main(void) {
    print_runner_test() ;
    program_runner_test() ;
    return 0 ;
}