#include "../include/programRunner.h"
#include "../include/runner.h"

void print_runner_test() {
    RESULT * print_runner_result = PrintRunner_run("Some input"); 

    printf("%s\n", print_runner_result->input); 
    printf("%s\n", print_runner_result->outcome); 

    free(print_runner_result->input); 
    free(print_runner_result->outcome);
    free(print_runner_result); 
}

void program_runner_test() { 
    program_runner_initialize("cat"); 
    subprocess * program_runner_result = programRunner_run("apple"); 
    printf("%s\n", program_runner_result->outcome); 
    
    free(program_runner_result->outcome);
    free(program_runner_result); 
}

int main(void) {
    print_runner_test() ;
    program_runner_test() ;
    return 0 ;
}