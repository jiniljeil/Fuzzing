#include "../include/troff.h"

int no_backslash_d(char * input) {
    char * pattern = "\\D";  
    int index = strstr(input, pattern); 

    if ( index < 0 || index + strlen(pattern) >= strlen(input)) return TRUE; 

    char c = input[ index + strlen(pattern) ]; 
    int ascii_num = (int) c ;

    assert(ascii_num > 31 && ascii_num < 128);
}