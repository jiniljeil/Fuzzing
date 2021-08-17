#include "../include/coverage.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 

int 
hex_values(char c) 
{
    if ( c >= '0' && c <= '9') return c - '0' ; 
    else if ( c >= 'A' && c <= 'F') return c - 'A' + 10 ;
    else if ( c >= 'a' && c <= 'f') return c - 'a' + 10 ; 

    return -1 ; 
}

char * 
cgi_decode(char * s) 
{   
    char c ; 
    int idx = 0 ; 
    int length = strlen(s) ; 
    char * text = (char *)malloc(sizeof(char) * length) ;

    for(int i = 0 ; i < length ; i++) {
        c = s[i] ;

        if ( c == '+') {
            text[idx++] = ' '; 
        }else if ( c == '%') {
            char digit_high = s[i + 1] ; 
            char digit_low = s[i + 2] ; 
            i += 2 ; 

            if (hex_values(digit_high) != -1 && hex_values(digit_low) != -1) {
                int value = hex_values(digit_high) * 16 +  hex_values(digit_low) ;
                text[idx++] = (char) value ;
            }else {
                fprintf(stderr, "Invalid encoding\n") ;
                return NULL ; 
            }
        }else{
            text[idx++] = c ; 
        }
    }   
    return text ; 
}


