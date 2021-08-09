#include "../include/runner.h"

RESULT * Runner_run(char* input) {
    RESULT * ret = (RESULT*)malloc(sizeof(RESULT)); 
    ret->input = (char*)malloc(sizeof(char) * (strlen(input) + 1)); 
    ret->outcome = (char*)malloc(sizeof(char) * (strlen(UNRESOLVED) + 1)); 

    strcpy(ret->input, input); 
    strcpy(ret->outcome, UNRESOLVED) ;

    return ret ;
}

RESULT * PrintRunner_run(char* input) {
    RESULT * ret = (RESULT*)malloc(sizeof(RESULT)); 
    ret->input = (char*)malloc(sizeof(char) * (strlen(input) + 1)); 
    ret->outcome = (char*)malloc(sizeof(char) * (strlen(UNRESOLVED) + 1)); 

    strcpy(ret->input, input); 
    strcpy(ret->outcome, UNRESOLVED) ;

    return ret ;
}