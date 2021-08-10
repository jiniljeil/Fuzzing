#include "../include/randomFuzzer.h" 
#include <assert.h>

void random_fuzzer_test1() { 
    printf("======================TEST1======================\n");

    RANDOM_SETTING * setting = (RANDOM_SETTING*)malloc(sizeof(RANDOM_SETTING)); 
    random_fuzzer_initialize(setting, 20, 20, BASIC_CHAR_START, BASIC_CHAR_RANGE);
    for (int i = 0 ; i < 10; i++) {
        printf("%s\n", random_fuzz(setting));
    }
    free(setting); 

    printf("=================================================\n\n");
}

void random_fuzzer_test2() {
    printf("======================TEST2======================\n");

    RANDOM_SETTING * setting = (RANDOM_SETTING*)malloc(sizeof(RANDOM_SETTING)); 
    random_fuzzer_initialize(setting, 20, 20, BASIC_CHAR_START, BASIC_CHAR_RANGE);
    program_runner_initialize("cat"); 

    for(int i = 0 ; i < 10; i++) {
        char* input = random_fuzz(setting); 
        subprocess * program_runner_result = programRunner_run(input);
        
        printf("INPUT: %s\n", input); 
        printf("(CompletedProcess(args=\'%s\', returncode=%d, stdout=\'%s\', stderr=\'%s\'), %s)\n",
            getProgramName(), program_runner_result->exit_code, program_runner_result->standard_out, 
            (strlen(program_runner_result->standard_err) == 0) ? "NOTHING" : program_runner_result->standard_err,
            program_runner_result->outcome);

        assert(strcmp(program_runner_result->standard_out, input) == 0);
        assert(strcmp(program_runner_result->outcome, PASS) == 0); 
        // free  
        subproc_result_free(program_runner_result) ;
    } 
    free(setting); 
    printf("=================================================\n\n");
}

void random_fuzzer_test3() {
    printf("======================TEST3======================\n");

    RANDOM_SETTING * setting = (RANDOM_SETTING*)malloc(sizeof(RANDOM_SETTING)); 
    random_fuzzer_initialize(setting, 20, 20, BASIC_CHAR_START, BASIC_CHAR_RANGE);
    program_runner_initialize("cat"); 

    subprocess * program_runner_result = random_fuzzer_run(setting, programRunner_run); 

    printf("(CompletedProcess(args=\'%s\', returncode=%d, stdout=\'%s\', stderr=\'%s\'), %s)\n",
            getProgramName(), program_runner_result->exit_code, program_runner_result->standard_out, 
            (strlen(program_runner_result->standard_err) == 0) ? "NOTHING" : program_runner_result->standard_err,
            program_runner_result->outcome); 

    subproc_result_free(program_runner_result);   
    free(setting);       
    printf("=================================================\n\n");

    

}

void random_fuzzer_test4() {
    const int trials = 10; 

    printf("======================TEST4======================\n");

    RANDOM_SETTING * setting = (RANDOM_SETTING*)malloc(sizeof(RANDOM_SETTING)); 
    random_fuzzer_initialize(setting, 20, 20, BASIC_CHAR_START, BASIC_CHAR_RANGE);
    program_runner_initialize("cat"); 

    subprocess ** program_runner_result = random_fuzzer_runs(setting, programRunner_run, trials); 

    for(int i = 0 ; i < trials; i++) {
        printf("(CompletedProcess(args=\'%s\', returncode=%d, stdout=\'%s\', stderr=\'%s\'), %s)\n",
            getProgramName(), program_runner_result[i]->exit_code, program_runner_result[i]->standard_out, 
            (strlen(program_runner_result[i]->standard_err) == 0) ? "NOTHING" : program_runner_result[i]->standard_err,
            program_runner_result[i]->outcome); 
    }

    // free 
    for(int i = 0 ; i < trials; i++) {
        subproc_result_free(program_runner_result[i]) ;
    }
    
    free(setting); 

    printf("=================================================\n\n");
}

int main(void) {
    srand(time(0));
    random_fuzzer_test1(); 
    random_fuzzer_test2();
    random_fuzzer_test3(); 
    random_fuzzer_test4();
    return 0 ;
}