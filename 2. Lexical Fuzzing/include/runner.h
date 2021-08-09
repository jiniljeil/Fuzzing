// #ifndef RUNNER
// #define RUNNER 
#include <stdlib.h> 
#include <string.h> 
#define PASS "PASS"
#define FAIL "FAIL"
#define UNRESOLVED "UNRESOLVED" 

typedef struct result {
    char* input ; 
    char* outcome; 
} RESULT; 

RESULT * Runner_run(char* input);
RESULT * PrintRunner_run(char* input); 

// #endif