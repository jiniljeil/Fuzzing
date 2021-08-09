#include "../include/randomFuzzer.h" 
#include "../include/programRunner.h"
#include <assert.h>

void random_fuzzer_test1() { 
    printf("======================TEST1======================\n");

    RANDOM_SETTING * setting = (RANDOM_SETTING*)malloc(sizeof(RANDOM_SETTING)); 
    random_fuzzer_initialize(setting, 20, 20, BASIC_CHAR_START, BASIC_CHAR_RANGE);
    for (int i = 0 ; i < 10; i++) {
        printf("%s\n", random_fuzz(setting));
    }
    free(setting); 

    printf("=================================================\n");
}

void random_fuzzer_test2() {
    printf("======================TEST2======================\n")
    RANDOM_SETTING * setting = (RANDOM_SETTING*)malloc(sizeof(RANDOM_SETTING)); 
    random_fuzzer_initialize(setting, BASIC_MIN_LENGTH, BASIC_MAX_LENGTH, BASIC_CHAR_START, BASIC_CHAR_RANGE);

    program_runner_initialize("cat"); 

    for(int i = 0 ; i < 10; i++) {
        char* input = random_fuzz(setting); 
        subprocess * program_runner_result = programRunner_run(input);
        assert(strcmp(program_runner_result->standard_out, input) == 0);
        assert(strcmp(program_runner_result->outcome, PASS) == 0); 

        printf("%s\n", input); 
    } 
    printf("=================================================\n");
}

int main(void) {
    random_fuzzer_test1(); 
    return 0 ;
}