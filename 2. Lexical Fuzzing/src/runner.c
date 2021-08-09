#include "../include/runner.h"

char** Runner_run(char* input) {
    char** ret = (char**)malloc(sizeof(char*) * 2) ;
    ret[0] = (char*)malloc(sizeof(char) * (strlen(input) + 1)); 
    ret[1] = (char*)malloc(sizeof(char) * (strlen(UNRESOLVED) + 1)); 

    strcpy(ret[0], input); 
    strcpy(ret[1], UNRESOLVED) ;

    return ret ;
}

char** PrintRunner_run(char* input) {
    char** ret = (char**)malloc(sizeof(char*) * 2) ;
    ret[0] = (char*)malloc(sizeof(char) * (strlen(input) + 1)); 
    ret[1] = (char*)malloc(sizeof(char) * (strlen(UNRESOLVED) + 1)); 

    printf("%s\n", input); 
    strcpy(ret[0], input); 
    strcpy(ret[1], UNRESOLVED) ;

    return ret ;
}