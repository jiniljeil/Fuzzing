#include <stdio.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h> 
#define true 1 
#define false 0 

void 
no_backslash_d(char input, int * no_backslash_d_flag, int * non_printable_flag) 
{
    if ( input == '\\' ) {
        *no_backslash_d_flag = true ; 
        return ;
    }
    if (*non_printable_flag) {
        if ((int)input >= 0 && (int)input <= 31) {
            perror("Error: The input sequence \\D (backslash + D) followed by a non-printable character\n"); 
            exit(1); 
        }else{
            *non_printable_flag = false; 
            *no_backslash_d_flag = false;
        }
    }


    if ( *no_backslash_d_flag) {
        if (input == 'D') {
            * non_printable_flag = true ;
            return ;
        }else{
            * no_backslash_d_flag = false; 
        }
    }
}

void 
no_8bit(char input, int * no_8bit_flag)
{
    if ( !((int)input >= 0 && (int)input <= 127)) {
        *no_8bit_flag = true; 
        return ;
    }

    if(*no_8bit_flag) {
        if(input == '\n') {
            perror("Error: A character in the ASCII range 128–255 (i.e., the 8th bit is set) followed by a newline character\n");
            exit(1); 
        }else{
            *no_8bit_flag = false; 
        }
    }
}

void
no_dot(char input, int * no_dot_flag)
{
    if ( input == '.' ) {
        *no_dot_flag = true; 
        return ;
    }
    
    if( *no_dot_flag) {
        if( input == '\n') {
            perror("Error: A single dot (.) followed by a newline character.\n"); 
            exit(1) ;
        }else{
            *no_dot_flag = false; 
        }
    }
}

int main(void) {
    char c ;
    int i = 0 ;  
    int no_backslash_d_flag = false, non_printable_flag = false; 
    int no_8bit_flag = false, no_dot_flag = false; 

    while( (c = getchar()) != EOF) {
        no_backslash_d(c, &no_backslash_d_flag, &non_printable_flag) ; 
        no_8bit(c, &no_8bit_flag); 
        no_dot(c, &no_dot_flag); 
    }
    
    return 0; 
}