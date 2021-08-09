#include "../include/randomFuzzer.h" 
#include <assert.h>

void random_fuzzer_test1() { 
    RANDOM_SETTING * setting = (RANDOM_SETTING*)malloc(sizeof(RANDOM_SETTING)); 
    random_fuzzer_initialize(setting, 20, 20, BASIC_CHAR_START, BASIC_CHAR_RANGE);
    for (int i = 0 ; i < 10; i++) {
        printf("%s\n", random_fuzz(setting));
    }
    free(setting); 
}

// void random_fuzzer_test2() {
//     RANDOM_SETTING * setting = (RANDOM_SETTING*)malloc(sizeof(RANDOM_SETTING)); 
//     random_fuzzer_initialize(setting, BASIC_MIN_LENGTH, BASIC_MAX_LENGTH, BASIC_CHAR_START, BASIC_CHAR_RANGE);

//     program_runner_initialize("cat"); 

//     for(int i = 0 ; i < 10; i++) {
//         char* input = random_fuzz(setting); 
//         RESULT * program_runner_result = programRunner_run(input);
//         // assert();
//         // assert();
//     } 
// }
int main(void) {
    random_fuzzer_test1(); 
    return 0 ;
}