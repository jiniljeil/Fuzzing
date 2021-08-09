#include "../include/simpleFuzzer.h" 

// Basic parameter (BASIC_LENGTH, BASIC_START, BASIC_RANGE) 
char * fuzzer(int max_length, int char_start, int char_range) {
    // 수정 필요 
    // srand(clock());
    int string_length = rand() % (max_length) + 1 ; // '\0'
    char * out = (char*)malloc(sizeof(char) * (string_length + 1)) ; 

    for(int i = 0 ; i < string_length; i++) {
        out[i] = (char) (char_start + rand() % char_range); 
    }

    out[string_length] = '\0';
    return out; 
}